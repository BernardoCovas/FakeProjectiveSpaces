#include <LibFkps.h>

#include <stdio.h>
#include <thread>
#include <future>
#include <string>
#include <vector>
#include <fstream>


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Args: Parsed_Det_File.txt\n");
		return 1;
	}

	std::ifstream infile(argv[1]);
	std::vector<FKPS> fkpsV;

	std::string line;
	int currline = 0;
	while (std::getline(infile, line))
	{
		++currline;
	
		FKPS fkps = nullptr;
		LibFkpsErr_t err_code = LIBFKPS_ERR_LIB_NOT_FOUND;
		int libinfoN;
		int libinfoK;
		
		char* express = new char[line.size()];
		int n = std::sscanf(line.c_str(), "%d,%d,%[^\t\n]", &libinfoN, &libinfoK, express);
		if (n < 3) goto LIBLOAD_FAILED;
		
		err_code = LibFkpsInit(&fkps, libinfoN, libinfoK, express);
		delete[] express;
		if (err_code != LIBFKPS_ERR_SUCCESS)
			goto LIBLOAD_FAILED;

		err_code = LibFkpsSolve(fkps, true);
		if (err_code != LIBFKPS_ERR_SUCCESS)
			goto LIBLOAD_FAILED;

		printf("[ APP ] Completed: %d with: %s\n", currline, LibFkpsErrToChar(err_code));
		continue;

	LIBLOAD_FAILED:
		
		printf("[ APP ] Failed: %d with code: %s\n", currline, LibFkpsErrToChar(err_code));
		LibFkpsDeinit(fkps);
	}

	infile.close();
}