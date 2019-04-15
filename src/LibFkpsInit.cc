#include "libfkpsconfig.h"
#include "LibFkps.h"
#include "LibFkpsDeterminantQ.hh"
#include "LibFkpsLogging.hh"

#include <dlfcn.h>


FKPS LibfkpsDeterminantQInit(

	const char* fname,
	const char* libfname

)
{
	LibfkpsDeterminantQ_t* lib = (LibfkpsDeterminantQ_t*)calloc(1, sizeof(LibfkpsDeterminantQ_t));
	if (!lib) { __log_err_malloc(); return NULL; }

	lib->filename = new std::string(fname);
	lib->libname = new std::string(libfname);
	lib->_mutex = new std::mutex;
	lib->handle = dlopen(lib->libname->c_str(), RTLD_NOW);

	if (!lib->handle)
	{
		__fkps_err_libloaded(lib->libname->c_str());
		LibfkpsDeterminantQDeInitUnload((FKPS)lib);
		return NULL;
	}

	return (FKPS)lib;
}


bool LibfkpsDeterminantQLoad(

	FKPS lib

)
{
	LibfkpsDeterminantQ_t* _lib = (LibfkpsDeterminantQ_t*)lib;

	_lib->file = fopen(_lib->filename->c_str(), "w");

	if (!_lib->file) goto LOAD_FAILED;

	_lib->libinfo_N = *(int*)dlsym(_lib->handle, "libinfo_N");
	_lib->libinfo_K = *(int*)dlsym(_lib->handle, "libinfo_K");
	_lib->determinantQ = (int (*)(int*)) dlsym(_lib->handle, "determinantQ");
	_lib->_partitions = (int*)malloc(_lib->libinfo_N * sizeof(int) * FKPS_STACKSIZE);

	if (!(_lib->libinfo_N) || !(_lib->libinfo_K) || !(_lib->determinantQ))
		goto LOAD_FAILED;

	if (!_lib->_partitions) {
		__log_err_malloc();
		goto LOAD_FAILED;
	}

	return true;

LOAD_FAILED:

	__fkps_err_libloaded(_lib->libname->c_str());
	LibfkpsDeterminantQDeInitUnload((FKPS)lib);
	return false;

}

void LibfkpsDeterminantQDeInitUnload(

	FKPS lib

)
{
	LibfkpsDeterminantQ_t* _lib = (LibfkpsDeterminantQ_t*)lib;

	__log_dbg_unloading(_lib->libname->c_str());

	free(_lib->_partitions);
	if (_lib->file)    fclose(_lib->file);
	if (_lib->handle)    dlclose(_lib->handle);

	delete _lib->_mutex;
	delete _lib->filename;
	delete _lib->libname;

	free(_lib);
}