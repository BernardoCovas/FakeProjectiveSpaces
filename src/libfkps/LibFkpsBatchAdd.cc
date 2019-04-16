#include <LibFkps.h>
#include <libfkpsconfig.h>

#include "LibFkps.hh"


LibFkpsErr_t LibFkpsBatchAdd(FKPSBatch _batch, int* v)
{
	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;
	
	if (!batch->vPart)
		return LIBFKPS_ERR_PARTITION_INIT;
	
	if (batch->stackSize > LIBFKPS_STACKSIZE - 1)
		return LIBFKPS_ERR_PARTITION_FULL;

	memcpy(batch->vPart + ((size_t) batch->N * batch->stackSize), v, (size_t) sizeof(int) * batch->N);
	++(batch->stackSize);

	if (batch->stackSize > LIBFKPS_STACKSIZE - 1)
		return LIBFKPS_ERR_PARTITION_FULL;

	return LIBFKPS_ERR_SUCCESS;
}