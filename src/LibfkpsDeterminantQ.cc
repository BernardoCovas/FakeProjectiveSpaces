#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>


#include "LibfkpsDeterminantQ.h"

void __log_err_malloc(void);
void __log_err_fopen(const char *fname);
void __log_dbg_flush(int batch, const char *fname);
void __log_dbg_unloading(const char *fname);


LibfkpsDeterminantQ_t * LibfkpsDeterminantQInitLoad(

    const char *fname,
    const char *libfname

)
{

    LibfkpsDeterminantQ_t *lib = (LibfkpsDeterminantQ_t *) malloc(sizeof(LibfkpsDeterminantQ_t));

    lib->filename = (char *) calloc(512, sizeof(char));
    lib->libname  = (char *) calloc(512, sizeof(char));
    strncpy(lib->filename, fname, 511);
    strncpy(lib->libname , libfname, 511);

    lib->file = fopen(fname, "w");
    if (!lib->file) { __log_err_fopen(fname); return NULL; }

    lib->handle = dlopen(libfname, RTLD_NOW);
    if (!lib->handle) { __log_err_fopen(libfname); return NULL; };

    lib->libinfo_N     = *(int *) dlsym(lib->handle, "libinfo_N");
    lib->libinfo_K     = *(int *) dlsym(lib->handle, "libinfo_K");
    lib->determinantQ  = (int (*)(int *)) dlsym(lib->handle, "determinantQ");
    lib->_stackcounter = 0;
    lib->_batchcounter = 0;

    if (!(lib->libinfo_N) || !(lib->libinfo_K) || !(lib->determinantQ))
    { 
        LibfkpsDeterminantQDeInitUnload(lib);
        __log_err_malloc();
        return NULL;
    }

    for (int i=0; i<FKPS_STACKSIZE; i++)
    {
        lib->_partitions[i] = (int *) malloc(lib->libinfo_N * sizeof(int));
        if (! lib->_partitions[i]) {
            LibfkpsDeterminantQDeInitUnload(lib);
            __log_err_malloc();
            return NULL;
        }
    }

    return lib;
}

void LibfkpsDeterminantQDeInitUnload(
    
    LibfkpsDeterminantQ_t *lib

)
{
    __log_dbg_unloading(lib->filename);

    for (int i=0; i<FKPS_STACKSIZE; i++)
        free(lib->_partitions[i]);

    dlclose(lib->handle);
    fclose(lib->file);
    free(lib->filename);
    free(lib->libname);
    free(lib);
}

void LibfkpsDeterminantQDump(
    
    LibfkpsDeterminantQ_t *lib

)
{
    __log_dbg_flush(lib->_batchcounter, lib->filename);

    FILE *f   = lib->file;
    int  n    = lib->libinfo_N;
    int  *_sc = &(lib->_stackcounter);

    for (int i = 0; i < *_sc; ++i)
        for (int j = 0; j < n; ++j)
            fprintf(f, j==(n-1) ?"%d\n":"%d,", (int) lib->_partitions[i][j]);

    lib->_batchcounter++;
}

void LibfkpsDeterminantQComputeAll(
    
    LibfkpsDeterminantQ_t *lib

)
{
    int n = lib->libinfo_N;
    int k = lib->libinfo_K;

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

    if(lib->_stackcounter > 0)
        LibfkpsDeterminantQDump(lib);

    free(v);
}

void LibfkpsDeterminantQCompute(
    
    LibfkpsDeterminantQ_t *lib,
    int *x

)
{
    int *sc = &(lib->_stackcounter);

    if (lib->determinantQ(x) == 0)
    {
        memcpy(lib->_partitions[*sc], x, lib->libinfo_N * sizeof(int));
        (*sc)++;

        if (*sc == FKPS_STACKSIZE)
        {
            LibfkpsDeterminantQDump(lib);
            (*sc) = 0;
        }
    }
}

void __log_err_malloc()
{
    printf("ERR: Could not allocate enough resources.\n");
}

void __log_err_fopen(const char *fname)
{
    printf("ERR: Could not open: %s.\n", fname);
}

void __log_dbg_flush(int batch, const char *fname)
{
    printf("DBG: Flushing batch %d to: %s\n", batch, fname);
}

void __log_dbg_unloading(const char *fname)
{
    printf("DBG: Unloading: %s.\n", fname);
}
