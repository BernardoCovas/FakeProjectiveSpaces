#include <LibFkps.h>

#include "LibFkps.hh"

LibFkpsErr_t LibFkpsBatchCompute(FKPSBatch _batch, FKPS _lib)
{
	LibFkpsErr_t errCode;
	LibFkps_t* lib = (LibFkps_t*)_lib;
	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;

	while (true)
	{
		batch->v;
		// TODO (bcovas)
		// IF (DET == 0):
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