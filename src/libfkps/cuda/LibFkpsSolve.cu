#include <LibFkps.h>
#include <libfkpsconfig.h>

#include "../LibFkps.hh"

#include <cuda.h>
#include <cuda_runtime.h>

#include <thread>
#include <vector>


void cudaSolve(FKPS _lib, FKPSBatch _batch)
{
	cudaError_t resCode;
	LibFkpsBatch_t* batch = (LibFkpsBatch_t*)_batch;
	LibFkps_t* lib = (LibFkps_t*)_lib;

	CUfunction* function = (CUfunction*)lib->function;

	int devBatchSize = batch->batchSize;
	CUdeviceptr devStateV, devNOutRes, devOutResV;

	cuMemAlloc(&devStateV, sizeof(int) * batch->N);
	cuMemAlloc(&devNOutRes, sizeof(int));
	cuMemAlloc(&devOutResV, sizeof(int) * batch->batchSize);

	cuMemcpyHtoD(devStateV, batch->v, sizeof(int) * batch->N);

	void* args[] = { &devBatchSize, &devStateV, &devNOutRes, &devOutResV };
	cuLaunchKernel(*function, 1, 1, 1, 1, 1, 1, 0, NULL, args, 0);

	cuCtxSynchronize();

	int* hostNOutRes = new int;
	int* hostOutResV;

	cuMemcpyDtoH(&hostNOutRes, devNOutRes, sizeof(int));
	hostOutResV = new int[*hostNOutRes];
	cuMemcpyDtoH(&hostOutResV, devOutResV, sizeof(int));

	cuMemFree(devStateV);
	cuMemFree(devNOutRes);
	cuMemFree(devOutResV);
	
	delete hostNOutRes;
	delete[] hostOutResV;
}


LibFkpsErr_t LibFkpsSolve(FKPS lib, bool verbose)
{
	LibFkpsErr_t errCode;

	errCode = LibFkpsGenerate(lib);
	if (errCode != LIBFKPS_ERR_SUCCESS)
		return errCode;

	errCode = LibFkpsCompile(lib);
	if (errCode != LIBFKPS_ERR_SUCCESS)
		return errCode;

	errCode = LibFkpsLoad(lib);
	if (errCode != LIBFKPS_ERR_SUCCESS)
		return errCode;


	FKPSBatch state;
	std::vector<FKPSBatch> batchV;
	std::vector<std::thread*> threadV;

	errCode = LibFkpsBatchInit(lib, &state);
	if (errCode != LIBFKPS_ERR_SUCCESS)
		return errCode;
	
	while (true)
	{
		FKPSBatch batch;
		if (LibFkpsBatchNew(state, &batch) == LIBFKPS_ERR_PARTITION_END)
			break;
		cudaSolve(lib, batch);
		batchV.push_back(batch);
	}

	for (FKPSBatch batch : batchV)
		LibFkpsBatchFree(batch);
	
	LibFkpsBatchFree(state);
	return LIBFKPS_ERR_SUCCESS;
}