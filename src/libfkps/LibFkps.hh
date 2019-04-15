#ifndef _LIBFKPS_HH
#define _LIBFKPS_HH

#include <stdio.h>
#include <mutex>
#include <string>

typedef struct
{
	int libIndex;
	FILE* solFile;
	std::string* libFileName;
	std::string* cFileName;

	int libinfoN;
	int libinfoK;
	std::string* detExprs;

	void* CUfunction;
	void* function;

	std::mutex* mutex;
} LibFkps_t;

typedef struct
{
	int N;
	int K;
	int cap;
	int batchSize;
	int stackSize;
	int* v;
	int* vPart;

	std::mutex* mutex;
} LibFkpsBatch_t;


#endif /* _LIBFKPS_HH */