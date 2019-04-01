#include <sstream>

#include "FkpsCommands.hh"

int FkpsCommandCompile(
    
    FSPATHV     &cFilePathV,
    FSPATHV     &outLibPathV,
    std::string compileCommand

)
{
    for (FSPATH fname : cFilePathV)
    {
        FSPATH libname(fname.string() + ".so");
        std::string sysCommand(compileCommand);


        int posInf = (int) sysCommand.find("%s");
        sysCommand = sysCommand.replace(posInf, 2, fname.string());
        int posOuf = (int) sysCommand.find("%s", posInf+2);
        sysCommand = sysCommand.replace(posOuf, 2, libname.string());

        printf("Compile result: %d for '%s'\n", system(sysCommand.c_str()), sysCommand.c_str());
        outLibPathV.push_back(libname);
    }

  return 0;
}