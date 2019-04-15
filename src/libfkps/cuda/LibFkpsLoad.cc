#include <LibFkps.h>

#include "../LibFkps.hh"

#include <dlfcn.h>

LibFkpsErr_t LibFkpsLoad(FKPS _lib)
{
	LibFkps_t* lib = (LibFkps_t*)_lib;

	lib->libHandle = dlopen(lib->libFileName->c_str(), RTLD_NOW);
	if (!lib->libHandle)
		return LIBFKPS_ERR_LIB_NOT_FOUND;

	int *N = (int*)dlsym(lib->libHandle, "libinfo_N");
	int *K = (int*)dlsym(lib->libHandle, "libinfo_K");
	void *func = dlsym(lib->libHandle, "determinantQ");

	if (!K || !N || !func)
	{
		dlclose(lib->libHandle);
		lib->libHandle = nullptr;
		return LIBFKPS_ERR_LIB_NOT_FOUND;
	}

	lib->libinfoN = *N;
	lib->libinfoK = *K;
	lib->function = func;

	return LIBFKPS_ERR_SUCCESS;
}
