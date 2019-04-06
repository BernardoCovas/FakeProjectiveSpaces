#ifndef  _LIBFKPSUTILS_H
#define _LIBFKPSUTILS_H

#include "LibFkpsDeterminantQ.h"
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
    int *batch;
    int  batchSize;
    int  N;
} LibFkpsUtilsPartitionBatch_t;

/**
 * 
 * */
typedef struct
{
    int batchSize;
    int N;
    int K;
    int *v;
    int _cap, _i;
    std::mutex *_mutex;
} LibFkpsPartitionBatchState_t;


/**
 * 
 * */
LibFkpsPartitionBatchState_t *
LibFkpsUtilsStateInit(
    
    LibfkpsDeterminantQ_t *lib

);


/**
 * New `Minibatch` / `BatchState` allocation.
 * */
LibFkpsUtilsPartitionBatch_t *LibFkpsUtilsBatchInit(

    LibFkpsPartitionBatchState_t *batchSate

);


/**
 * Gets the state and generates
 * a new batch of integer partitions
 * for processing.
 * */
LibFkpsUtilsPartitionBatch_t *LibFkpsUtilsNewBatch(

    LibFkpsPartitionBatchState_t *state,
    int batchSize

);


/**
 * 
 * */
LibFkpsUtilsPartitionBatch_t *
LibFkpsUtilsNewBatch(

    LibFkpsPartitionBatchState_t *state

);


/**
 * Gets a batch by index.
 * Index must be smaller than MINIBATCH_SIZE 
 * of course.
 * */
int *LibFkpsUtilsBatchGet(
    
    LibFkpsUtilsPartitionBatch_t *batch,
    int index

);


/**
 * Adds a batch to the data storage.
 * Convenient function.
 * Equivalent to setting the pointer
 * `index` (`N` * `index`) to `newBatch`.
 * 
 * `index` must be smaller than
 * MINIBATCH_SIZE of course.
 * */
void LibFkpsUtilsBatchAdd(

    LibFkpsUtilsPartitionBatch_t *batch,
    int *newBatch,
    int index

);


/**
 * Releases the resources allocated to the minibatch.
 * */
void LibFkpsUtilsFreeBatch(
    
    LibFkpsUtilsPartitionBatch_t *batch
    
);


/**
 * 
 * */
void
LibFkpsUtilsFreeState(
    
    LibFkpsPartitionBatchState_t *state
    
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
