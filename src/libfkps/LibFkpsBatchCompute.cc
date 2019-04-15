#include <LibFkps.h>

#include "LibFkps.hh"

typedef void (*FkpsFunction_t)(int *x, int *outRes);

LibFkpsErr_t LibFkpsBatchCompute(FKPSBatch _batch, FKPS _lib)
{
	LibFkpsErr_t errCode;
	LibFkps_t* lib = (LibFkps_t*)_lib;
	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;
	
	if (!lib->function) return LIBFKPS_ERR_LIB_NOT_FOUND;

	FkpsFunction_t function = (FkpsFunction_t)lib->function;

	while (true)
	{
		int outRes;
		function(batch->v, &outRes);

		if (outRes == 0)
		{
			errCode = LibFkpsBatchAdd(batch, batch->v);
			if (errCode == LIBFKPS_ERR_PARTITION_FULL)
				return errCode;
		}

		errCode = LibFkpsBatchIncrement(_batch);
		if (errCode == LIBFKPS_ERR_PARTITION_END)
			break;
	}

	return LIBFKPS_ERR_SUCCESS;
}