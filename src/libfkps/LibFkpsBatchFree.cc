#include <LibFkps.h>

#include "LibFkps.hh"


LibFkpsErr_t LibFkpsBatchFree(FKPSBatch _batch)
{
	if (!_batch) return LIBFKPS_ERR_SUCCESS;

	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;

	delete batch->mutex;
	delete[] batch->v;
	delete[] batch->vPart;
	delete batch;

	return LIBFKPS_ERR_SUCCESS;
}