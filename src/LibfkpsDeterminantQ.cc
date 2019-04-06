#include "LibFkpsDeterminantQ.h"
#include "LibFkpsDeterminantQ.hh"

#include "LibFkpsLogging.hh"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include <filesystem>
#include <array>
#include <mutex>


FKPS LibfkpsDeterminantQInitLoad(

    const char *fname,
    const char *libfname

)
{

    LibfkpsDeterminantQ_t *lib = (LibfkpsDeterminantQ_t *) malloc(sizeof(LibfkpsDeterminantQ_t));
    if (!lib) { __log_err_malloc(); return NULL;}

    lib->filename    = new std::string(fname);
    lib->libname     = new std::string(libfname);
    lib->_mutex      = new std::mutex;
    lib->file        = fopen(fname, "w");
    lib->handle      = dlopen(libfname, RTLD_NOW);
    lib->_partitions = NULL;

    const char  *whatFailed;

    if (!lib->file)   { whatFailed = lib->filename->c_str(); goto LOAD_FAILED; }
    if (!lib->handle) { whatFailed = lib->libname ->c_str(); goto LOAD_FAILED; }

    lib->_stackcounter = 0;
    lib->_batchcounter = 0;
    lib->libinfo_N     = *(int *)         dlsym(lib->handle, "libinfo_N");
    lib->libinfo_K     = *(int *)         dlsym(lib->handle, "libinfo_K");
    lib->determinantQ  =  (int (*)(int *)) dlsym(lib->handle, "determinantQ");
    lib->_partitions   =  (int *) malloc(lib->libinfo_N * sizeof(int) * FKPS_STACKSIZE);

    if (!(lib->libinfo_N) || !(lib->libinfo_K) || !(lib->determinantQ))
    { 
        __log_err_malloc();
        whatFailed = lib->libname->c_str();
        goto LOAD_FAILED;
    }

    if (!lib->_partitions) {
        __log_err_malloc();
        whatFailed = lib->libname->c_str();
        goto LOAD_FAILED;
    }

    return (FKPS) lib;


LOAD_FAILED:

    __log_err_fopen(whatFailed);
    LibfkpsDeterminantQDeInitUnload((FKPS) lib);
    return NULL;

}

void LibfkpsDeterminantQDeInitUnload(
    
    FKPS lib

)
{
    LibfkpsDeterminantQ_t *_lib = (LibfkpsDeterminantQ_t *) lib;

    __log_dbg_unloading(_lib->libname->c_str());

    free(_lib->_partitions);
    if(_lib->file   )    fclose(_lib->file);
    if(_lib->handle )    dlclose(_lib->handle);
    
    delete _lib->_mutex;
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

    if (_lib->determinantQ(x) != 0)
        return;

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

