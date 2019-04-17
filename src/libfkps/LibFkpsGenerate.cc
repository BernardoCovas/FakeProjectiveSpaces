#include <LibFkpsConfig.h>
#include <LibFkps.h>

#include "LibFkps.hh"

#include <stdio.h>

#ifdef LIBFKPS_USE_CUDA

const char* FILE_FORMAT =
"#ifdef __cplusplus\n"
"extern \"C\" {\n"
"#endif\n\n"

"#define libinfo_N %d\n"
"#define libinfo_K %d\n\n"

"__device__\n"
"int determinantQ(int* x)\n"
"{\n"
"	return %s;\n"
"}\n\n"

"__global__\n"
"void cudaAllSolve(int* stateV, int* nOutRes, int* outResV)\n"
"{\n"
"	int cap = libinfo_K - libinfo_N - 1;\n"
"	(*nOutRes) = 0;\n"
"	int partCount = 0;\n\n"

"	while (stateV[libinfo_N - 1] != cap)\n"
"	{\n"
"		int i = libinfo_N;\n\n"

"		while (stateV[--i] == 1);\n\n"

"		if (i != libinfo_N - 1)\n"
"		{\n"
"			--stateV[i];\n"
"			stateV[i + 1] = 2;\n"
"		}\n"
"		else\n"
"		{\n"
"			while (stateV[--i] == 1);\n"
"			--stateV[i];\n"
"			int s = stateV[libinfo_N - 1];\n"
"			stateV[libinfo_N - 1] = 1;\n"
"			stateV[i + 1] = s + 1;\n"
"		}\n\n"

"		int outRes = determinantQ(stateV);\n\n"

"		if (outRes == 0)\n"
"		{\n"
"			outResV[(*nOutRes)] = partCount;\n"
"			++(*nOutRes);\n"
"		}\n"
"		partCount++;\n"
"	}\n"
"}\n\n"

"#ifdef __cplusplus\n"
"}\n"
"#endif\n\n";

#else

const char* FILE_FORMAT =
"#ifdef __cplusplus\n"
"extern \"C\" {\n"
"#endif\n\n"

"const int libinfo_N = %d;\n"
"const int libinfo_K = %d;\n\n"

"void determinantQ(int *x, int *outRes)\n"
"{\n"
"	(*outRes) = %s;\n"
"}\n\n"
"#ifdef __cplusplus\n"
"}\n"
"#endif\n";

#endif

LibFkpsErr_t LibFkpsGenerate(FKPS lib)
{
	LibFkps_t* _lib = (LibFkps_t*)lib;

	FILE* cFile = fopen(_lib->cFileName->c_str(), "w");
	if (!cFile) return LIBFKPS_ERR_SRC_NOT_FOUND;

	fprintf(cFile, FILE_FORMAT, _lib->libinfoN, _lib->libinfoK, _lib->detExprs->c_str());
	fclose(cFile);

	return LIBFKPS_ERR_SUCCESS;
}