#include <LibFkps.h>

#include "LibFkps.hh"

LibFkpsErr_t LibFkpsBatchFlush(FKPSBatch _batch, FKPS _lib)
{
	LibFkps_t* lib = (LibFkps_t*)_lib;
	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;

	if (!lib->solFile) return LIBFKPS_ERR_SOL_NOT_FOUND;

	lib->mutex->lock();
	for (int i = 0; i < batch->stackSize; i++)
	{
		int* v;
		LibFkpsBatchGet(batch, i, &v); //TODO (bcovas): Error check
		for (int j = 0; j < batch->N; j++)
		{
			fprintf(lib->solFile, j<(batch->N - 1)?"%d,":"%d\n", v[j]);
		}
	}
	batch->stackSize = 0;
	lib->mutex->unlock();
}