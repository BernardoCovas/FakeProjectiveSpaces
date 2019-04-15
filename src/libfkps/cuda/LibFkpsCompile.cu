#include <LibFkpsConfig.h>
#include <LibFkps.h>

#include "../LibFkps.hh"

#include <cuda_runtime.h>
#include <nvrtc.h>

#include <fstream>
#include <string>
#include <sstream>


LibFkpsErr_t LibFkpsCompile(FKPS lib)
{
	LibFkps_t* _lib = (LibFkps_t*)lib;

	std::ifstream fileStream;
	std::string cFileContent;
	nvrtcProgram prog = nullptr;
	FILE* libFile = nullptr;
	char* ptx = nullptr;
	size_t ptxSize;


	libFile = fopen(_lib->libFileName->c_str(), "w");

	if (!libFile)
		goto LIB_FAILED;

	fileStream = std::ifstream(_lib->cFileName->c_str());

	if (!fileStream.is_open()) 
		goto LIB_FAILED;

	cFileContent = std::string((std::istreambuf_iterator<char>(fileStream)),
		(std::istreambuf_iterator<char>()));

	nvrtcCreateProgram(&prog, cFileContent.c_str(), _lib->libFileName->c_str(), 0, nullptr, nullptr);
	if (nvrtcCompileProgram(prog, 0, nullptr) != NVRTC_SUCCESS)
		goto LIB_FAILED;
	
	nvrtcGetPTXSize(prog, &ptxSize);

	ptx = new char[ptxSize];
	nvrtcGetPTX(prog, ptx);
	nvrtcDestroyProgram(&prog);

	fprintf(libFile, ptx);

	fclose(libFile);
	delete[] ptx;
	nvrtcDestroyProgram(&prog);
	fileStream.close();

	return LIBFKPS_ERR_SUCCESS;

LIB_FAILED:

	if (!libFile) return LIBFKPS_ERR_LIB_NOT_FOUND;
	fclose(libFile);
	
	if (fileStream.is_open()) fileStream.close();
	else return LIBFKPS_ERR_SRC_NOT_FOUND;

	if (prog) nvrtcDestroyProgram(&prog);
	if (ptx) delete[] ptx;

	return LIBFKPS_ERR_COMPILE;
}

