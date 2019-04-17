#include <LibFkps.h>

#include "LibFkps.hh"

#include <dlfcn.h>

#ifdef LIBFKPS_USE_CUDA
#include <cuda.h>
#endif

LibFkpsErr_t LibFkpsDeinit(FKPS lib)
{
	/* NOTE (bcovas): If init fails, (FKPS) lib is NULL. */
	if (!lib) return LIBFKPS_ERR_SUCCESS;

	LibFkps_t* _lib = (LibFkps_t*)lib;

	if (_lib->libHandle)
#ifdef LIBFKPS_USE_CUDA
		cuCtxDestroy((CUcontext)_lib->libHandle);
#else
		dlclose(_lib->libHandle);
#endif
	delete _lib->cFileName;
	delete _lib->libFileName;
	delete _lib->detExprs;
	delete _lib->mutex;
	fclose(_lib->solFile);
	free(lib);

	return LIBFKPS_ERR_SUCCESS;
}
