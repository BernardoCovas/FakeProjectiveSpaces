#include <LibFkps.h>

#include "LibFkps.hh"


LibFkpsErr_t LibFkpsDeinit(FKPS lib)
{
	/* NOTE (bcovas): If init fails, (FKPS) lib is NULL. */
	if (!lib) return LIBFKPS_ERR_SUCCESS;

	LibFkps_t* _lib = (LibFkps_t*)lib;
	
	delete _lib->cFileName;
	delete _lib->libFileName;
	delete _lib->detExprs;
	delete _lib->mutex;
	fclose(_lib->solFile);
	free(lib);

	return LIBFKPS_ERR_SUCCESS;
}
