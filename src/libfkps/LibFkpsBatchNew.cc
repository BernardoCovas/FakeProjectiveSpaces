#include <LibFkps.h>
#include <libfkpsconfig.h>

#include "LibFkps.hh"

LibFkpsErr_t LibFkpsBatchNew(FKPSBatch _state, FKPSBatch* _outBatch)
{
	LibFkpsErr_t errCode = LIBFKPS_ERR_SUCCESS;
	LibFkpsBatch_t* state = (LibFkpsBatch_t*)_state;
	LibFkpsBatch_t* newBatch = new(std::nothrow) LibFkpsBatch_t;

	if (!newBatch) goto MALLOC_FAILED;
	(*newBatch) = (*state);

	newBatch->mutex = new std::mutex;
	newBatch->v = new(std::nothrow) int[state->N];
	newBatch->vPart = new(std::nothrow) int[(size_t) state->N * LIBFKPS_STACKSIZE];

	if (!newBatch->v || !newBatch->vPart) goto MALLOC_FAILED;

	state->mutex->lock();
		memcpy(newBatch->v, state->v, sizeof(int) * state->N);
		for (int i = 0; i < state->batchSize; i++)
		{
			errCode = LibFkpsBatchIncrement(state);
			if (errCode == LIBFKPS_ERR_PARTITION_END)
			{
				newBatch->batchSize = i;
				break;
			}
		}
	state->mutex->unlock();

	(*_outBatch) = (FKPSBatch)newBatch;
	return errCode;

MALLOC_FAILED:
	LibFkpsBatchFree(newBatch);
	return LIBFKPS_ERR_MEMORY;
}