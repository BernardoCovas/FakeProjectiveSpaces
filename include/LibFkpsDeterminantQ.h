#ifndef _LIBFKPSDETERMINANTQ_H
#define _LIBFKPSDETERMINANTQ_H

#include <stdio.h>

#include "libfkpsconfig.h"


typedef void *FKPS;


/**
 *  Loads the shared library and
 *  allocates the needed memmory.
 */
FKPS LibfkpsDeterminantQInitLoad(

    const char *fname,
    const char *libfname

);


/**
 *  Unloads the shared library and
 *  frees the allocated memmory.
 */
void LibfkpsDeterminantQDeInitUnload(
    
    FKPS lib

);


/**
 * Computes one partiton.
 * Might save to file if the
 * stack is full.
 */
void LibfkpsDeterminantQCompute(
    
    FKPS lib,
    int *x

);


/**
 * Computes all partitons.and
 * saves them to the file.
 * Returns when done.
 */
void LibfkpsDeterminantQComputeAll(
    
    FKPS lib

);


/**
 * Flushes the stack to the file.
 */
void LibfkpsDeterminantQDump(
    
    FKPS lib

);


#endif // _LIBFKPSDETERMINANTQ_H
