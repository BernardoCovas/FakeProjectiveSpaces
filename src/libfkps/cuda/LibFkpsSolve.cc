#include <LibFkps.h>
#include <libfkpsconfig.h>

#include "../LibFkps.hh"

#include <thread>
#include <future>


void threadSolve(FKPS lib, FKPSBatch state)
{
	std::future<LibFkpsErr_t> nextErrCode;
	FKPSBatch batch;
	FKPSBatch nextBatch;

	nextErrCode = std::async(LibFkpsBatchNew, state, &nextBatch);

	while (true)
	{
		LibFkpsErr_t errCode = nextErrCode.get();
		batch = nextBatch;

		if (errCode != LIBFKPS_ERR_PARTITION_END)
			nextErrCode = std::async(LibFkpsBatchNew, state, &nextBatch);

		while (LibFkpsBatchCompute(batch, lib) == LIBFKPS_ERR_PARTITION_FULL)
			LibFkpsBatchFlush(batch, lib);

		LibFkpsBatchFlush(batch, lib);
		LibFkpsBatchFree(batch);

		if (errCode == LIBFKPS_ERR_PARTITION_END)
			break;
	}
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
	errCode = LibFkpsBatchInit(lib, &state);
	if (errCode != LIBFKPS_ERR_SUCCESS)
		return errCode;
	
	std::thread* threadV = new std::thread[LIBFKPS_PARALLEL];

	for (int i = 0; i < LIBFKPS_PARALLEL; i++)
		threadV[i] = std::thread(&threadSolve, lib, state);
	for (int i = 0; i < LIBFKPS_PARALLEL; i++)
		threadV[i].join();

	LibFkpsBatchFree(state);
	return LIBFKPS_ERR_SUCCESS;
}