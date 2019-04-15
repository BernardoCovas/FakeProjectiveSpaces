#include <LibFkps.h>

#include "LibFkps.hh"


LibFkpsErr_t LibFkpsBatchGet(FKPSBatch _batch, int index, int** outV)
{
	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;
	
	if (!batch->vPart)
		return LIBFKPS_ERR_PARTITION_INIT;

	if (index > batch->stackSize)
		return LIBFKPS_ERR_PARTITION_INDEX_RANGE;

	(*outV) = batch->vPart + ((size_t) index * batch->N);

	return LIBFKPS_ERR_SUCCESS;
}