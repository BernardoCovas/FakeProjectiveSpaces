#ifndef  _LIBFKPSUTILS_H
#define _LIBFKPSUTILS_H

#include "LibFkps.h"
#include "LibFkpsDeterminantQ.hh"

#include <vector>
#include <filesystem>

typedef std::filesystem::path FSPATH;
typedef std::vector<FSPATH> FSPATHV;

typedef LibfkpsDeterminantQ_t* FKPSLIB;
typedef std::vector<FKPSLIB>  FKPSLIBV;


/**
 * 
 * */
typedef struct
{
    int batchSize;
    int N;
    int *v;
    int _cap;
    std::mutex *_mutex;
} LibFkpsBatch_t;


/**
 * Initializes a batch struct from lib.
 * */
LibFkpsBatch_t*
LibFkpsBatchInit(
    
    LibfkpsDeterminantQ_t *lib

);


/*
 * Copy a batch. Allocates memory.
 */
LibFkpsBatch_t* LibFkpsBatchCopy(

	LibFkpsBatch_t* state

);


/**
 * Gets the state and generates
 * a new batch of integer partitions
 * for processing.
 * Changes `state`.
 * */
LibFkpsBatch_t *
LibFkpsBatchNew(

	LibFkpsBatch_t *state

);


/*
 * Increments the batch state by one,
 * returns false if there are no
 * more partitions.
 */
inline bool FkpsBatchIncrement(

	LibFkpsBatch_t* state

);


/**
 * Releases the resources allocated to the minibatch.
 * */
void
LibFkpsBatchFree(
    
	LibFkpsBatch_t *state
    
);


/**
 * Computes all determinant
 * partition sequences,
 * with `parallelJobs` Parallel jobs.
 * The implementation of this function
 * depends on the `FKPS_COMPUTE_PARALELL`
 * options in `libfkpsconfig.h`.
 * */
void LibFkpsParallelCompute(

    FKPSLIBV *libV,
    int parallelJobs
    
);

#endif // _LIBFKPSUTILS_H
