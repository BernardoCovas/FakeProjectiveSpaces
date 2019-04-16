#include <LibFkps.h>

#include <stdio.h>
#include <thread>
#include <future>
#include <string>
#include <vector>
#include <fstream>


void ComputeAll(FKPS lib, FKPSBatch state)
{
	static int currBatch = 0;
	printf("Thread started.\n");

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
		
		int currThreadBatch = ++currBatch;
		printf("Batch started.\n");
		
		while (LibFkpsBatchCompute(batch, lib) == LIBFKPS_ERR_PARTITION_FULL)
		{
			printf("Saving batch: %d\n", currThreadBatch);
			LibFkpsBatchFlush(batch, lib);
		}

		printf("Last flush of: %d\n", currThreadBatch);
		LibFkpsBatchFlush(batch, lib);
		LibFkpsBatchFree(batch);

		if (errCode == LIBFKPS_ERR_PARTITION_END)
			break;
	}

	printf("Thread exited.\n");
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Args: Parsed_Det_File.txt\n");
		return 1;
	}

	std::ifstream infile(argv[1]);
	std::vector<FKPS> fkpsV;

	std::string line;
	int currline = 0;
	while (std::getline(infile, line))
	{
		++currline;
	
		FKPS fkps = nullptr;
		LibFkpsErr_t err_code = LIBFKPS_ERR_LIB_NOT_FOUND;
		int libinfoN;
		int libinfoK;
		
		char* express = new char[line.size()];
		int n = std::sscanf(line.c_str(), "%d,%d,%[^\t\n]", &libinfoN, &libinfoK, express);
		if (n < 3) goto LIBLOAD_FAILED;
		
		err_code = LibFkpsInit(&fkps, libinfoN, libinfoK, express);
		delete[] express;
		if (err_code != LIBFKPS_ERR_SUCCESS)
			goto LIBLOAD_FAILED;
		
		err_code = LibFkpsGenerate(fkps);
		if (err_code != LIBFKPS_ERR_SUCCESS)
			goto LIBLOAD_FAILED;

		err_code = LibFkpsCompile(fkps);
		if (err_code != LIBFKPS_ERR_SUCCESS)
			goto LIBLOAD_FAILED;

		err_code = LibFkpsLoad(fkps);
		if (err_code != LIBFKPS_ERR_SUCCESS)
			goto LIBLOAD_FAILED;


		fkpsV.push_back(fkps);
		printf("Completed: %d with: %s\n", currline, LibFkpsErrToChar(err_code));
		continue;

	LIBLOAD_FAILED:
		
		printf("Failed: %d with code: %s\n", currline, LibFkpsErrToChar(err_code));
		LibFkpsDeinit(fkps);
	}

	infile.close();


	std::thread *threadV = new std::thread[16];
	for (FKPS lib : fkpsV)
	{
		FKPSBatch state;
		LibFkpsBatchInit(lib, &state);

		for (int i = 0; i < 16; i++)
			threadV[i] = std::thread(&ComputeAll, lib, state);
		for (int i = 0; i < 16; i++)
			threadV[i].join();

		LibFkpsDeinit(lib);
		LibFkpsBatchFree(state);
	}
	
	delete[] threadV;
}