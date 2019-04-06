#include "LibFkpsDeterminantQ.h"
#include "LibFkpsDeterminantQ.hh"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include <filesystem>
#include <sstream>
#include <atomic>
#include <array>
#include <mutex>


void __log_err_malloc(void);
void __log_err_fopen(const char * fname);
void __log_dbg_flush(int batch, const char * fname);
void __log_dbg_unloading(const char * fname);


FKPS LibfkpsDeterminantQInitLoad(

    const char *fname,
    const char *libfname

)
{

    LibfkpsDeterminantQ_t *lib = (LibfkpsDeterminantQ_t *) malloc(sizeof(LibfkpsDeterminantQ_t));

    lib->filename = new std::string(fname);
    lib->libname  = new std::string(libfname);

    lib->file = fopen(fname, "w");
    if (!lib->file) { __log_err_fopen(lib->filename->c_str()); return NULL; }

    lib->handle = dlopen(libfname, RTLD_NOW);
    if (!lib->handle) { __log_err_fopen(lib->libname->c_str()); return NULL; };

    lib->libinfo_N     = *(int *) dlsym(lib->handle, "libinfo_N");
    lib->libinfo_K     = *(int *) dlsym(lib->handle, "libinfo_K");
    lib->determinantQ  = (int (*)(int *)) dlsym(lib->handle, "determinantQ");
    lib->_stackcounter = 0;
    lib->_batchcounter = 0;

    if (!(lib->libinfo_N) || !(lib->libinfo_K) || !(lib->determinantQ))
    { 
        LibfkpsDeterminantQDeInitUnload((FKPS) lib);
        __log_err_malloc();
        return NULL;
    }

    lib->_partitions = (int *) malloc(lib->libinfo_N * sizeof(int) * FKPS_STACKSIZE);

    if (!lib->_partitions) {
        LibfkpsDeterminantQDeInitUnload((FKPS) lib);
        __log_err_malloc();
        return NULL;
    }

    lib->_mutex = new std::mutex;
    return (FKPS) lib;
}

void LibfkpsDeterminantQDeInitUnload(
    
    FKPS lib

)
{
    LibfkpsDeterminantQ_t *_lib = (LibfkpsDeterminantQ_t *) lib;

    __log_dbg_unloading(_lib->filename->c_str());

    delete _lib->_mutex;
    free(_lib->_partitions);

    dlclose(_lib->handle);
    fclose(_lib->file);
    delete _lib->filename;
    delete _lib->libname;
    free(_lib);
}

void LibfkpsDeterminantQDump(
    
    FKPS lib

)
{
    LibfkpsDeterminantQ_t *_lib = (LibfkpsDeterminantQ_t *) lib;

	std::filesystem::path fpath(_lib->filename->c_str());
    __log_dbg_flush(_lib->_batchcounter, fpath.filename().string().c_str());

    FILE *f   = _lib->file;
    int  n    = _lib->libinfo_N;
    int  sc   = _lib->_stackcounter;

    for (int i = 0; i < sc; i++)
        for (int j = 0; j < n; ++j)
            fprintf(f, j==(n-1) ?"%d\n":"%d,", (int) _lib->_partitions[j + (i * _lib->libinfo_N)]);
    _lib->_batchcounter++;

}

void LibfkpsDeterminantQComputeAll(
    
    FKPS lib

)
{
    LibfkpsDeterminantQ_t *_lib = (LibfkpsDeterminantQ_t *) lib;

    int n = _lib->libinfo_N;
    int k = _lib->libinfo_K;

    int *v = (int *) malloc(sizeof(int) * n);

    for (int j = 0; j < n; ++j) {
        v[j] = 1;
    }

    int cap = k - n + 1;
    int i, s;
    v[0] = cap;
    
    LibfkpsDeterminantQCompute(lib, v);

    while (v[n-1] != cap) {

        i = n;
        while (v[--i] == 1);

        if (i != n-1) {
            --v[i];
            v[i+1] = 2;
        } else {
            while (v[--i] == 1);
            --v[i];
            s = v[n-1];
            v[n-1] = 1;
            v[i+1] = s+1;
        }

        LibfkpsDeterminantQCompute(lib, v);

    }

    if(_lib->_stackcounter > 0)
        LibfkpsDeterminantQDump(lib);

    free(v);
}

void LibfkpsDeterminantQCompute(
    
    FKPS lib,
    int *x

)
{
    LibfkpsDeterminantQ_t *_lib = (LibfkpsDeterminantQ_t *) lib;

    if (_lib->determinantQ(x) == 0)
    {
        _lib->_mutex->lock();

        if (_lib->_stackcounter == (FKPS_STACKSIZE-1))
        {
            LibfkpsDeterminantQDump(_lib);
            _lib->_stackcounter = 0;
        }

        int sc = _lib->_stackcounter;
        memcpy(_lib->_partitions + (sc * _lib->libinfo_N), x, _lib->libinfo_N * sizeof(int));
        _lib->_stackcounter++;

        _lib->_mutex->unlock();
    }
}

void __fkps_dbg(const char *str)
{
    static std::atomic_int currLog = 0;
    printf("DBG: [ %d ][ %s ]\n", currLog++, str);
}

void __fkps_err(const char *str)
{
    static std::atomic_int currLog = 0;
    printf("ERR: [ %d ][ %s ]\n", currLog++, str);
}

void __log_err_malloc()
{
    __fkps_err("Could not allocate enough resources.");
}

void __log_err_fopen(const char * fname)
{
    std::stringstream log;
    log << "Could not open: " << fname;
    __fkps_err(log.str().c_str());
}

void __log_dbg_flush(int batch, const char * fname)
{
    std::stringstream log;
    log << "Flushing batch " << batch << " to " << fname;
    __fkps_dbg(log.str().c_str());
}

void __log_dbg_unloading(const char * fname)
{
    std::stringstream log;
    log << "Unloading: " << fname;
    __fkps_dbg(log.str().c_str());
}

void __fkps_log_libloaded(LibfkpsDeterminantQ_t *lib)
{
    std::stringstream log;
    log << "Using library: " << lib->libname->c_str() << ", Writing to: " << lib->filename->c_str();
    __fkps_dbg(log.str().c_str());
}

void __fkps_err_libloaded(const char * fname)
{
    std::stringstream log;
    log << "Failed loading: " << fname;
    __fkps_dbg(log.str().c_str());
}


void __fkps_log_started(LibfkpsDeterminantQ_t *lib)
{
    std::stringstream log;
    log << "Started: " << lib->libname->c_str();
    __fkps_dbg(log.str().c_str());
}

void __fkps_log_compile_res(int res, const char *command)
{
    std::stringstream log;
    log << "Compile result: " << res << " for command: " << command;
    __fkps_dbg(log.str().c_str());
}