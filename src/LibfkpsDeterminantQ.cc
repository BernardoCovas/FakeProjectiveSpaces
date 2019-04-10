#include "LibFkps.h"
#include "LibFkpsDeterminantQ.hh"

#include "LibFkpsLogging.hh"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include <filesystem>
#include <array>
#include <mutex>


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

