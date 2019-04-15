#include <LibFkps.h>

#include "LibFkps.hh"

LibFkpsErr_t LibFkpsBatchNew(FKPSBatch _state, FKPSBatch* _outBatch)
{
	LibFkpsBatch_t* state = (LibFkpsBatch_t*)_state;
	LibFkpsBatch_t* newBatch = new(std::nothrow) LibFkpsBatch_t;
	if (!newBatch) goto MALLOC_FAILED;

	(*newBatch) = (*state);
	newBatch->v = new(std::nothrow) int[state->N];
	newBatch->vPart = new(std::nothrow) int[(size_t) state->N * state->batchSize];

	if (!newBatch->v || !newBatch->vPart) goto MALLOC_FAILED;

	memcpy(newBatch->v, state->v, sizeof(int) * state->N);

	state->mutex->lock();
		for (int i = 0; i < state->batchSize; i++)
		{
			if (LibFkpsBatchIncrement(state) == LIBFKPS_ERR_PARTITION_END)
			{
				newBatch->batchSize = i;
				break;
			}
		}
	state->mutex->unlock();

	(*_outBatch) = (FKPSBatch)newBatch;
	return LIBFKPS_ERR_SUCCESS;

MALLOC_FAILED:
	LibFkpsBatchFree(newBatch);
	return LIBFKPS_ERR_MEMORY;
}