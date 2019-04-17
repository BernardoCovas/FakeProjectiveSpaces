#include <LibFkps.h>

#include "../LibFkps.hh"

#include <dlfcn.h>

LibFkpsErr_t LibFkpsLoad(FKPS _lib)
{
	LibFkps_t* lib = (LibFkps_t*)_lib;

	lib->libHandle = dlopen(lib->libFileName->c_str(), RTLD_NOW);
	if (!lib->libHandle)
		return LIBFKPS_ERR_LIB_NOT_FOUND;

	void *func = dlsym(lib->libHandle, "determinantQ");

	if (!func)
	{
		dlclose(lib->libHandle);
		lib->libHandle = nullptr;
		return LIBFKPS_ERR_LIB_NOT_FOUND;
	}

	lib->function = func;

	return LIBFKPS_ERR_SUCCESS;
}
