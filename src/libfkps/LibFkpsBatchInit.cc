#include <LibFkps.h>
#include <LibFkpsConfig.h>

#include "LibFkps.hh"

#include <mutex>


LibFkpsErr_t LibFkpsBatchInit(FKPS _lib, FKPSBatch* _batch)
{
	LibFkps_t* lib = (LibFkps_t*)_lib;
	LibFkpsBatch_t* batch = new(std::nothrow) LibFkpsBatch_t;
	if(!batch) goto MALLOC_FAILED;

	batch->mutex = new std::mutex;
	
	batch->batchSize = LIBFKPS_THREAD_BATCHSIZE;
	batch->stackSize = 0;

	batch->K = lib->libinfoK;
	batch->N = lib->libinfoN;
	batch->cap = lib->libinfoK - lib->libinfoN + 1;
	batch->vPart = nullptr;

	int* v = new(std::nothrow) int[lib->libinfoN];
	if (!v) goto MALLOC_FAILED;
	batch->v = v;

	v[0] = batch->cap;
	for (int i = 1; i < lib->libinfoN; i++)
		v[i] = 1;

	(*_batch) = batch;
	
	return LIBFKPS_ERR_SUCCESS;

MALLOC_FAILED:
	if (!batch) return LIBFKPS_ERR_MEMORY;
	LibFkpsBatchFree(batch);
	return LIBFKPS_ERR_MEMORY;
}