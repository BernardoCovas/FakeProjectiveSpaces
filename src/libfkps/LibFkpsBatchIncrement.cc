#include <LibFkps.h>

#include "LibFkps.hh"

LibFkpsErr_t LibFkpsBatchIncrement(FKPSBatch _batch)
{
	
	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;

	if (batch->v[(batch->N) - 1] == batch->cap)
		return LIBFKPS_ERR_PARTITION_END;

	int i = batch->N;
	while (batch->v[--i] == 1);

	if (i != batch->N - 1)
	{
		--batch->v[i];
		batch->v[i + 1] = 2;
	}
	else
	{
		while (batch->v[--i] == 1);
		--batch->v[i];
		int s = batch->v[(batch->N) - 1];
		batch->v[(batch->N) - 1] = 1;
		batch->v[i + 1] = s + 1;
	}

	return LIBFKPS_ERR_SUCCESS;
}