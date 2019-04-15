#include "LibFkpsUtils.hh"
#include "LibFkpsDeterminantQ.hh"

#include <string.h>
#include <mutex>

LibFkpsBatch_t * LibFkpsBatchInit(
    
    LibfkpsDeterminantQ_t *lib

)
{
	LibFkpsBatch_t *outState = new LibFkpsBatch_t;

    outState->N = lib->libinfo_N;
    outState->_cap = lib->libinfo_K - outState->N + 1;
    outState->batchSize = FKPS_MINIBATCH_SIZE;

    outState->v = (int *) malloc(sizeof(int) * lib->libinfo_N);
    outState->v[0] = outState->_cap;

	for (int i=1; i<lib->libinfo_N; i++)
        outState->v[i] = 1;

    outState->_mutex = new std::mutex;
    return outState;
}

LibFkpsBatch_t* LibFkpsBatchCopy(

	LibFkpsBatch_t* state

)
{
	LibFkpsBatch_t* outState = new LibFkpsBatch_t;

	outState->N = state->N;
	outState->_cap = state->_cap;
	outState->batchSize = state->batchSize;

	outState->v = (int*)malloc(sizeof(int) * state->N);
	memcpy(outState->v, state->v, sizeof(int) * state->N);

	outState->_mutex = new std::mutex;
	return outState;
}

inline bool FkpsBatchIncrement(

	LibFkpsBatch_t* state

)
{
	if (state->v[(state->N) - 1] == state->_cap)
	{
		return false;
	}

	int j = state->N;
	while (state->v[--j] == 1);

	if (j != state->N - 1)
	{
		--state->v[j];
		state->v[j + 1] = 2;
	}
	else
	{
		while (state->v[--j] == 1);
		--state->v[j];
		int s = state->v[(state->N) - 1];
		state->v[(state->N) - 1] = 1;
		state->v[j + 1] = s + 1;
	}

	return true;
}

LibFkpsBatch_t *LibFkpsBatchNew(

	LibFkpsBatch_t *state

)
{
    LibFkpsBatch_t *outBatch = LibFkpsBatchCopy(state);

    for (int i=0; i<state->batchSize; i++)
    {
		if (!FkpsBatchIncrement(state))
		{
			outBatch->batchSize = i;
            return outBatch;
		}
    }

    return outBatch;
}


void
LibFkpsBatchFree(
    
    LibFkpsBatch_t *batch
    
)
{
	delete batch->_mutex;
    free(batch->v);
    free(batch);
}
