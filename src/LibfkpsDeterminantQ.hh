#ifndef _FKPSDETERMINANTQ_HH
#define _FKPSDETERMINANTQ_HH

#include <stdio.h>

#include <vector>
#include <mutex>

typedef struct
{
    int        libinfo_N;
    int        libinfo_K;
    int     (* determinantQ )(int *x);

    FILE     * file;
    void     * handle;
    char     * filename;
    char     * libname;
    
    int      * _partitions;

    int        _stackcounter;
    int        _batchcounter;

    std::mutex * _mutex; // std::mutex is non-copiable or moovable
} LibfkpsDeterminantQ_t;


#endif // _FKPSDETERMINANTQ_HH
