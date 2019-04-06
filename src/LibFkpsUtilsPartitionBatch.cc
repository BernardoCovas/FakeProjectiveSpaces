#include "LibFkpsUtils.hh"
#include "LibFkpsDeterminantQ.hh"

#include <string.h>
#include <mutex>

LibFkpsPartitionBatchState_t *LibFkpsUtilsStateInit(
    
    LibfkpsDeterminantQ_t *lib

)
{
    LibFkpsPartitionBatchState_t *outState = new LibFkpsPartitionBatchState_t;

    outState->K = lib->libinfo_K;
    outState->N = lib->libinfo_N;
    outState->_cap = outState->K - outState->N + 1;
    outState->batchSize = FKPS_MINIBATCH_SIZE;

    outState->v = (int *) malloc(sizeof(int) * lib->libinfo_N);
    outState->v[0] = outState->_cap;
    for (int i=1; i<lib->libinfo_N; i++)
        outState->v[i] = 1;

    outState->_mutex = new std::mutex;
    return outState;
}

LibFkpsUtilsPartitionBatch_t *LibFkpsUtilsBatchInit(

    LibFkpsPartitionBatchState_t *batchSate

)
{
    LibFkpsUtilsPartitionBatch_t *batch = new LibFkpsUtilsPartitionBatch_t;
    batch->batch = (int *) malloc(sizeof(int) * batchSate->batchSize * batchSate->N);
    batch->batchSize = 0;
    batch->N = batchSate->N;
    
    return batch;
}

LibFkpsUtilsPartitionBatch_t *
LibFkpsUtilsNewBatch(

    LibFkpsPartitionBatchState_t *state

)
{
    LibFkpsUtilsPartitionBatch_t *outBatch = LibFkpsUtilsBatchInit(state);

    if (state->v[0] == state->_cap)
        LibFkpsUtilsBatchAdd(outBatch, state->v, 0);

    for (int i=outBatch->batchSize; i<state->batchSize; i++)
    {
        if (state->v[(state->N)-1] == state->_cap)
            return outBatch;

        state->_i = state->N;
        while (state->v[--(state->_i)] == 1);

        if (state->_i != state->N-1)
        {
            --state->v[state->_i];
            state->v[state->_i+1] = 2;
        } else
        {
            while (state->v[--state->_i] == 1);
            --state->v[state->_i];
            int s = state->v[(state->N)-1];
            state->v[(state->N)-1] = 1;
            state->v[state->_i+1] = s+1;
        }

        LibFkpsUtilsBatchAdd(outBatch, state->v, i);

    }

    return outBatch;

}


void
LibFkpsUtilsFreeBatch(
    
    LibFkpsUtilsPartitionBatch_t *batch
    
)
{
    free(batch->batch);
    free(batch);
}


void
LibFkpsUtilsFreeState(
    
    LibFkpsPartitionBatchState_t *state
    
)
{
    delete state->_mutex;
    free(state->v);
    free(state);
}


int *
LibFkpsUtilsBatchGet(
    
    LibFkpsUtilsPartitionBatch_t *batch,
    int index

)
{
    return batch->batch + (index * batch->N);
}

void
LibFkpsUtilsBatchAdd(

    LibFkpsUtilsPartitionBatch_t *batch,
    int *newBatch,
    int index

)
{
    memcpy(
        batch->batch + (index * batch->N),
        newBatch,
        batch->N * sizeof(int)
        );

    batch->batchSize++;
}