#include <LibFkps.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc < 2)
		printf("Args: Parsed_Det_File.txt\n");

	std::ifstream infile(argv[1]);
	std::vector<FKPS> fkpsV;

	std::string line;
	int currline = 0;
	while (std::getline(infile, line))
	{
		++currline;
	
		FKPS fkps;
		LibFkpsErr_t err_code;
		int libinfoN;
		int libinfoK;
		
		char* express = new char[line.size()];
		int n = std::sscanf(line.c_str(), "%d,%d,%[^\t\n]", &libinfoN, &libinfoK, express);
		if (n < 3) { delete[] express; continue; }

		err_code = LibFkpsInit(&fkps, libinfoN, libinfoK, express);
		if (err_code != LIBFKPS_ERR_SUCCESS)
			goto LIBLOAD_FAILED;
		
		err_code = LibFkpsGenerate(fkps);
		if (err_code != LIBFKPS_ERR_SUCCESS)
			goto LIBLOAD_FAILED;

		err_code = LibFkpsCompile(fkps);
		if (err_code != LIBFKPS_ERR_SUCCESS)
			goto LIBLOAD_FAILED;


		fkpsV.push_back(fkps);
		printf("Completed: %d with: %s\n", currline, LibFkpsErrToChar(err_code));
		continue;

	LIBLOAD_FAILED:
		
		printf("Failed: %d with code: %s\n", currline, LibFkpsErrToChar(err_code));
		LibFkpsDeinit(fkps);

		delete[] express;
	}

	for (FKPS lib : fkpsV)
	{
		// TODO (bcovas)
	}



	return 0;
}