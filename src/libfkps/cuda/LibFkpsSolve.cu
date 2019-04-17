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

	CUdeviceptr* xV		 = new CUdeviceptr[batch->batchSize];
	CUdeviceptr* outResV = new CUdeviceptr[batch->batchSize];

	size_t cudaParamIntVSize = sizeof(int) * batch->N;
	size_t cudaParamIntSize  = sizeof(int);

	for (int i = 0; i < batch->batchSize; i++)
	{
		LibFkpsBatchIncrement(batch);

		CUdeviceptr* devX		= xV + i;
		CUdeviceptr* devOutRes = outResV + i;

		cuMemAlloc(devX, cudaParamIntVSize);
		cuMemAlloc(devOutRes, cudaParamIntSize);

		cuMemcpyHtoD(*devX, batch->v, cudaParamIntVSize);

		void* args[] = {devX, devOutRes};
		resCode = cudaLaunchKernel(function, 1, 1, args);
	}

	cuCtxSynchronize();

	int* inX = new int[batch->N];
	for (int i = 0; i < batch->batchSize; i++)
	{
		int outRes;
		cuMemcpyDtoH(&outRes, outResV[i], cudaParamIntSize);

		if (outRes == 0)
		{
			cuMemcpyDtoH(inX, xV[i], cudaParamIntVSize);
			if (LibFkpsBatchAdd(batch, inX) == LIBFKPS_ERR_PARTITION_FULL)
				LibFkpsBatchFlush(batch, _lib);
		}
	}
	delete[] inX;
	LibFkpsBatchFlush(batch, _lib);
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

	errCode = LibFkpsBatchInit(lib, &state);
	if (errCode != LIBFKPS_ERR_SUCCESS)
		return errCode;
	
	while (true)
	{
		FKPSBatch batch;
		if (LibFkpsBatchNew(state, &batch) == LIBFKPS_ERR_PARTITION_END)
			break;
		batchV.push_back(batch);
		cudaSolve(lib, batch);
	}

	LibFkpsBatchFree(state);
	return LIBFKPS_ERR_SUCCESS;
}