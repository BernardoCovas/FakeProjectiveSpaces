#include <stdio.h>
#include <thread>
#include <filesystem>

#include "LibfkpsDeterminantQ.h"
#include "libfkpsconfig.h"

std::string pathGenerator(const char *logdir, const char *libfname);


int main(int argc, char const *argv[])
{

  if (argc < 3)
  {
    printf("Args: '/path/to/logdir' '/path/to/compiled/determinant_01.so' ('02.so', '03.so', ...).\n");
    return 1;
  }

  const char *logdir = argv[1];
  int nLibs = argc - 2;

  printf("Using directory: %s\n", logdir);

  LibfkpsDeterminantQ_t **libs = (LibfkpsDeterminantQ_t **) malloc(sizeof(LibfkpsDeterminantQ_t *) * nLibs);
  std::thread ts[nLibs];

  for (int i=0; i<nLibs; i++)
  {
    int argv_i = i+2;
    const char *libfname = argv[argv_i];
    std::string solFile = pathGenerator(logdir, libfname);

    printf("Using library: %s\n", libfname);
    printf("Using file: %s\n", solFile.c_str());

    libs[i] = LibfkpsDeterminantQInitLoad(solFile.c_str(), libfname);
    if (libs[i] == NULL)
    {
      printf("Could not load: %s", argv[i]);
      return -1;
    }

    ts[i] = std::thread(LibfkpsDeterminantQComputeAll, libs[i]);
  }

  for (int i=0; i<nLibs; i++)
  {
    ts[i].join();
    LibfkpsDeterminantQDeInitUnload(libs[i]);
  }
  
  return 0;
}


std::string pathGenerator(const char *logdir, const char *libfname)
{
  std::filesystem::path _logdir(logdir);
  std::filesystem::path _libfname(libfname);

  _libfname = _libfname.replace_extension("csv").filename();
  return (_logdir / _libfname).string();
}