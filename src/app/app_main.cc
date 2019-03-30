#include <stdio.h>
#include <string.h>
#include <thread>
#include <filesystem>

#include "LibfkpsDeterminantQ.h"
#include "libfkpsconfig.h"


#define COMMAND_COMPUTE "compute"
#define COMMAND_COMPILE "compile"

std::string pathGenerator(const char *logdir, const char *libfname);

int commandCompile(int argc, const char *argv[]);
int commandCompute(int argc, const char *argv[]);


int main(int argc, char const *argv[])
{

  if (argc < 2)
  {
    printf("Args: 'command' [Args ...]. Commands: compute, compile\n");
    return 1;
  }

  const char *command = argv[1];

  if(memcmp(command, COMMAND_COMPUTE, strlen(COMMAND_COMPUTE)) == 0)
    return commandCompute(argc, argv);

  if(memcmp(command, COMMAND_COMPILE, strlen(COMMAND_COMPILE)) == 0)
    return commandCompile(argc, argv);

}


std::string pathGenerator(const char *logdir, const char *libfname)
{
  std::filesystem::path _logdir(logdir);
  std::filesystem::path _libfname(libfname);

  _libfname = _libfname.replace_extension("csv").filename();
  return (_logdir / _libfname).string();
}

int commandCompile(int argc, const char *argv[])
{

  if (argc < 4)
  {
    printf("Args: 'compileCommandWithFormat' '/path/to/cfiles_dir/01.c', ...\n");
    return 1;
  }

  const char *_compileCommand = argv[2];
  int nCFiles = argc - 3;

  argv += 3;
  for (int i=0; i<nCFiles; i++)
  {
    const char *fname = argv[i];

    char *command;
    if (!asprintf(&command, _compileCommand, fname, (std::string(fname) + ".so").c_str()))
    {
      printf("Bad command: %s. Should have two 's' placeholders.\n", command);
      continue;
    }

    printf("Result: %d for '%s'\n", system(command), command);
  }

  return 0;
}

int commandCompute(int argc, const char *argv[])
{
  if (argc < 4)
  {
    printf("Args: '/path/to/logdir' '/path/to/dir/\\*.so'.\n");
    return 1;
  }

  const char *logdir = argv[2];
  const char *compiledObjDir = argv[3];
  int nLibs = argc - 3;

  printf("Using directory: %s\n", logdir);
  printf("Found %d matching files.\n", nLibs);

  LibfkpsDeterminantQ_t **libs = (LibfkpsDeterminantQ_t **) malloc(sizeof(LibfkpsDeterminantQ_t *) * nLibs);
  std::thread ts[nLibs];

  argv += 3;
  for (int i=0; i<nLibs; i++)
  {
    const char *libfname = argv[i];
    std::string solFile = pathGenerator(logdir, libfname);

    printf("Using library: %s\n", libfname);
    printf("Using file: %s\n", solFile.c_str());

    libs[i] = LibfkpsDeterminantQInitLoad(solFile.c_str(), libfname);
    if (libs[i] == NULL)
    {
      printf("Could not load: %s\n", libfname);
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