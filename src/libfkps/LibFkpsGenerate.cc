#include <LibFkpsConfig.h>
#include <LibFkps.h>

#include "LibFkps.hh"

#include <stdio.h>


const char* FILE_FORMAT = 
"const int libinfo_N = %d;\n"
"const int libinfo_K = %d;\n\n"

#ifdef LIBFKPS_USE_CUDA
"__global__\n"
#endif

"void determinantQ(int *x, int *outRes)\n"
"{\n"
"	(*outRes) = %s;\n"
"}\n"
;


LibFkpsErr_t LibFkpsGenerate(FKPS lib)
{
	LibFkps_t* _lib = (LibFkps_t*)lib;

	FILE* cFile = fopen(_lib->cFileName->c_str(), "w");
	if (!cFile) return LIBFKPS_ERR_SRC_NOT_FOUND;

	fprintf(cFile, FILE_FORMAT, _lib->libinfoN, _lib->libinfoK, _lib->detExprs->c_str());
	fclose(cFile);

	return LIBFKPS_ERR_SUCCESS;
}