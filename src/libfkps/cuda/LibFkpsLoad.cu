#include <LibFkps.h>

#include "../LibFkps.hh"

#include <dlfcn.h>
#include <cuda.h>

LibFkpsErr_t LibFkpsLoad(FKPS _lib)
{
	CUresult resCode;
	LibFkps_t* lib = (LibFkps_t*)_lib;

	CUcontext cntxt = (CUcontext)lib->libHandle;
	cuCtxAttach(&cntxt, 0);

	CUmodule cuModule;
	resCode = cuModuleLoad(&cuModule, lib->libFileName->c_str());
	if (resCode != CUDA_SUCCESS)
		return LIBFKPS_ERR_LIB_NOT_FOUND;

	CUfunction  function;
	resCode = cuModuleGetFunction(&function, cuModule, "cudaAllSolve");
	if (resCode != CUDA_SUCCESS)
	{
		cuModuleUnload(cuModule);
		lib->function = nullptr;
		return LIBFKPS_ERR_LIB_NOT_FOUND;
	}

	CUfunction* functionP = new CUfunction;
	*functionP = function;
	lib->function = (void*)functionP;

	return LIBFKPS_ERR_SUCCESS;
}
