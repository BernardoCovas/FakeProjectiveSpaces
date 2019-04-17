#include <LibFkps.h>
#include <LibFkpsConfig.h>

#include "LibFkps.hh"

#include <string>
#include <sstream>
#include <filesystem>

#ifdef LIBFKPS_USE_CUDA
#include <cuda.h>
#endif


typedef std::filesystem::path FSPATH;


LibFkpsErr_t LibFkpsInit(FKPS* _lib, int N, int K, const char* detExprs)
{
	static int libindex = 0;
	++libindex;
	(*_lib) = nullptr;

	FILE* solFile = nullptr;
	LibFkps_t* lib = nullptr;

	std::ostringstream cFileName;
	std::ostringstream libFileName;
	std::ostringstream solFileName;

#ifdef LIBFKPS_USE_CUDA
	cFileName	<< libindex << ".cu";
	libFileName << libindex << ".ptx";
#else
	cFileName   << libindex << ".c";
	libFileName << libindex << ".so";
#endif

	solFileName << libindex << ".csv";

	FSPATH cFilePath  (LIBFKPS_FOLDER_INTERNAL);
	FSPATH libFilePath(LIBFKPS_FOLDER_INTERNAL);
	FSPATH solFilePath(LIBFKPS_SOLVED_FOLDER);

	std::filesystem::create_directories(cFilePath);
	std::filesystem::create_directories(libFilePath);
	std::filesystem::create_directories(solFilePath);

	if (
			!std::filesystem::exists(cFilePath)
		||	!std::filesystem::exists(libFilePath)
		||	!std::filesystem::exists(solFilePath)
		) 
		return LIBFKPS_ERR_CREATE_DIRS;

	cFilePath	/= cFileName.str();
	libFilePath /= libFileName.str();
	solFilePath /= solFileName.str();

	solFile = fopen(solFilePath.string().c_str(), "w");
	if (!solFile) { return LIBFKPS_ERR_SOL_NOT_FOUND; }

	lib = (LibFkps_t *)calloc(1, sizeof(LibFkps_t));
	if (!lib) { fclose(solFile); return LIBFKPS_ERR_MEMORY; }

	lib->detExprs = new std::string(detExprs);
	lib->libinfoK = K;
	lib->libinfoN = N;
	lib->solFile = solFile;

	lib->mutex = new std::mutex;
	lib->libIndex = libindex;


	lib->cFileName = new std::string(cFilePath.string());
	lib->libFileName = new std::string(libFilePath.string());

	(*_lib) = lib;

#ifdef LIBFKPS_USE_CUDA
	CUcontext cntxt;
	cuInit(0);
	cuCtxCreate(&cntxt, 0, 0);
	lib->libHandle = (void*)cntxt;
#endif

	return LIBFKPS_ERR_SUCCESS;
}