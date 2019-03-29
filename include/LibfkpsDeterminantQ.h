#ifndef _LIBFKPSDETERMINANTQ_H
#define _LIBFKPSDETERMINANTQ_H

#include <stdio.h>

#include "libfkpsconfig.h"


typedef struct
{
    int libinfo_N;
    int libinfo_K;
    int (*determinantQ)(int *x);

    FILE *file;
    void *handle;
    
    int *_partitions[FKPS_STACKSIZE];
    int _stackcounter;
    int _batchcounter;
    /* data */
} LibfkpsDeterminantQ_t;


/**
 *  Loads the shared library and
 *  allocates the needed memmory.
 */
LibfkpsDeterminantQ_t *LibfkpsDeterminantQInitLoad(

    const char *fname,
    const char *libfname

);


/**
 *  Unloads the shared library and
 *  frees the allocated memmory.
 */
void LibfkpsDeterminantQDeInitUnload(
    
    LibfkpsDeterminantQ_t *lib

);

/**
 * Computes one partiton.
 * Might save to file if the
 * stack is full.
 */
void LibfkpsDeterminantQCompute(
    
    LibfkpsDeterminantQ_t *lib,
    int *x

);

/**
 * Computes all partitons.and
 * saves them to the file.
 * Returns when done.
 */
void LibfkpsDeterminantQComputeAll(
    
    LibfkpsDeterminantQ_t *lib

);

#endif // _LIBFKPSDETERMINANTQ_H

