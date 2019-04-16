#include <LibFkpsConfig.h>
#include <LibFkps.h>

#include "../LibFkps.hh"


LibFkpsErr_t LibFkpsCompile(FKPS lib)
{
	LibFkps_t* _lib = (LibFkps_t*)lib;
	std::string compileCommand(LIBFKPS_COMPILE_COMMAND);
	
	size_t inPos = compileCommand.find("%i");
	if (inPos < 0)
		return LIBFKPS_ERR_COMPILE;
	compileCommand.replace(inPos, 2, _lib->cFileName->c_str());
	size_t ouPos = compileCommand.find("%o");
	if (ouPos < 0)
		return LIBFKPS_ERR_COMPILE;
	compileCommand.replace(ouPos, 2, _lib->libFileName->c_str());
	
	if (system(compileCommand.c_str()) != 0)
		return LIBFKPS_ERR_COMPILE;

	return LIBFKPS_ERR_SUCCESS;
}

