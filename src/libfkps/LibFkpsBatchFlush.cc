#include <LibFkps.h>

#include "LibFkps.hh"

LibFkpsErr_t LibFkpsBatchFlush(FKPSBatch _batch, FKPS _lib)
{
	LibFkps_t* lib = (LibFkps_t*)_lib;
	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;

	if (!lib->solFile) return LIBFKPS_ERR_SOL_NOT_FOUND;
	if (!batch->vPart) return LIBFKPS_ERR_PARTITION_INIT;

	lib->mutex->lock();
		for (int i = 0; i < batch->stackSize; i++)
		{
			int* v;
			LibFkpsBatchGet(batch, i, &v);
			for (int j = 0; j < batch->N; j++)
				fprintf(lib->solFile, j<(batch->N - 1)?"%d,":"%d\n", v[j]);
		}
		batch->stackSize = 0;
	lib->mutex->unlock();
}