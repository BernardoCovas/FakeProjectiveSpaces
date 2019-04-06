#include <sstream>

#include "FkpsCommands.hh"

#include "LibFkpsLogging.hh"

int FkpsCommandCompile(
    
    FSPATHV     &cFilePathV,
    FSPATHV     &outLibPathV,
    std::string compileCommand

)
{
  int rescode = 0;

  int posInf = (int) compileCommand.find("%i");
  int posOuf = (int) compileCommand.find("%o", posInf+2);

  if (posInf < 0 || posOuf < 0)
  {
    __fkps_err_compile_cmd(compileCommand.c_str());
    return -1;
  }

  for (FSPATH fname : cFilePathV)
  {
      FSPATH libname(fname.string() + ".so");
      std::string sysCommand(compileCommand);

      int _posInf = (int) sysCommand.find("%i");
      sysCommand = sysCommand.replace(_posInf, 2, fname.string());
      int _posOuf = (int) sysCommand.find("%o");
      sysCommand = sysCommand.replace(_posOuf, 2, libname.string());

      int crescode = system(sysCommand.c_str());
      __fkps_log_compile_res(crescode, sysCommand.c_str());
      rescode += crescode;
      outLibPathV.push_back(libname);
  }

  return rescode;
}