#include <filesystem>
#include <fstream>
#include <sstream>

#include "FkpsCommands.hh"

const char *CFILE_FORMAT = 
"int libinfo_N = %d;\n"
"int libinfo_K = %d;\n\n"
"int determinantQ(int *x)\n"
"{\n"
"    return %s;\n"
"}\n";

int FkpsCommandGenerate(
    
    FSPATH  genPath,
    FSPATH  cParsedFile,
    FSPATHV &outPathv
)
{

  std::ifstream infile(cParsedFile);
  if (!infile.is_open()) { printf("Could not open: %s", cParsedFile.string().c_str()); return -1; }

  std::filesystem::create_directories(genPath);

  std::string line;
  while (std::getline(infile, line))
  {
    static int currfile = 0;
    std::ostringstream cFile;

    cFile << currfile++ << ".c";
    FSPATH cFilePath(cFile.str());
    cFilePath = genPath / cFile.str();

    int libN, libK;
    char *expression = new char[line.size()];

    std::sscanf(line.c_str(), "%d,%d,%[^\t\n]", &libN, &libK, expression);

    FILE *file = fopen(cFilePath.string().c_str(), "w");
    if (!file) { printf("Could not open: %s\n", cFilePath.string().c_str()); return -1; }

    fprintf(file, CFILE_FORMAT, libN, libK, expression);
    fclose(file);

    printf("Wrote: %s\n", cFilePath.string().c_str());
    outPathv.push_back(cFilePath.string());
  }  

    return 0;
}