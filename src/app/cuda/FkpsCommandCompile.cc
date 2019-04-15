#include "FkpsCommands.hh"
#include "LibFkpsLogging.hh"

#include <nvrtc.h>
#include <sstream>


int FkpsCudaCommandCompile(
    
    FSPATHV     &cFilePathV,
    FSPATHV     &outLibPathV

)
{
  int rescode = 0;

  for (FSPATH fname : cFilePathV)
  {
      FSPATH libname(fname.string() + ".ptx");
	  
      outLibPathV.push_back(libname);
  }

  return rescode;
}