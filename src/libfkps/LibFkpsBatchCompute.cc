#include <LibFkps.h>

#include "LibFkps.hh"


LibFkpsErr_t LibFkpsBatchCompute(FKPSBatch _batch, FKPS _lib)
{
	LibFkpsErr_t errCode;
	LibFkps_t* lib = (LibFkps_t*)_lib;
	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;
	
	if (!lib->function) return LIBFKPS_ERR_LIB_NOT_FOUND;
	FkpsFunction_t function = (FkpsFunction_t)lib->function;

	for (int i = 0; i<batch->batchSize; i++)
	{
		int outRes;
		function(batch->v, &outRes);

		if (outRes == 0)
			if (LibFkpsBatchAdd(batch, batch->v) == LIBFKPS_ERR_PARTITION_FULL)
				return LIBFKPS_ERR_PARTITION_FULL;

		LibFkpsBatchIncrement(_batch);
	}

	return LIBFKPS_ERR_SUCCESS;
}