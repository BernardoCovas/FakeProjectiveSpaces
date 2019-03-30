#include <stdio.h>
#include <string.h>
#include <fstream>
#include <thread>
#include <atomic>
#include <filesystem>

#include "LibfkpsDeterminantQ.h"
#include "libfkpsconfig.h"

#define COMMAND_COMPUTE  "compute"
#define COMMAND_COMPILE  "compile"
#define COMMAND_GENERATE "generate"


std::string pathGenerator(const char *logdir, const char *libfname);

int commandGenerate(int argc, const char *argv[]);
int commandCompile (int argc, const char *argv[]);
int commandCompute (int argc, const char *argv[]);


int main(int argc, char const *argv[])
{

  if (argc < 2)
  {
    printf("Args: 'command' [Args ...]. Commands: generate, compile, compute\n");
    return 1;
  }

  const char *command = argv[1];

  if(strcmp(command, COMMAND_GENERATE) == 0)
    return commandGenerate(argc, argv);
  if(strcmp(command, COMMAND_COMPILE) == 0)
    return commandCompile(argc, argv);
  if(strcmp(command, COMMAND_COMPUTE) == 0)
    return commandCompute(argc, argv);

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
    printf("Args: 'compileCommandWithFormat' '/path/to/cfiles_dir/01.c', ['/path/to/cfiles_dir/02.c' ... ]\n");
    return 1;
  }

  const char *_compileCommand = argv[2];
  int nCFiles = argc - 3;

  argv += 3;
  for (int i=0; i<nCFiles; i++)
  {
    const char *fname = argv[i];

    char *command = new char[512];
    if (!snprintf(command, 511, _compileCommand, fname, (std::string(fname) + ".so").c_str()))
    {
      printf("Bad command: %s. Should have two 's' placeholders.\n", command);
      continue;
    }

    printf("Result: %d for '%s'\n", system(command), command);
  }

  return 0;
}

void _commandComputeConsume(LibfkpsDeterminantQ_t **lib_v, int lib_c)
{
  static std::atomic_int threadID = 0;

  while(true)
  {
    int t_id = threadID++;
    if (t_id >= lib_c)
    {
      printf("Thread exited.\n");
      return;
    }
    LibfkpsDeterminantQ_t *lib = lib_v[t_id];
    printf("Starting %s.\n", lib->libname);

    LibfkpsDeterminantQComputeAll(lib);
    LibfkpsDeterminantQDeInitUnload(lib);

    printf("Finished %s.\n", lib->libname);
  }

}

int commandCompute(int argc, const char *argv[])
{

  if (argc < 4)
  {
    printf("Args: '/path/to/logdir' '/path/to/dir/compiled.c.so' ['/path/to/dir/compiled2.c.so' ... ]\n");
    return 1;
  }

  const char *logdir = argv[2];
  const char *compiledObjDir = argv[3];
  int nLibs = argc - 3;

  printf("Using directory: %s\n", logdir);
  printf("Found %d matching files.\n", nLibs);

  LibfkpsDeterminantQ_t **libs = (LibfkpsDeterminantQ_t **) malloc(sizeof(LibfkpsDeterminantQ_t *) * nLibs);
  std::thread *ts = new std::thread[nLibs];

  argv += 3;
  for (int i=0; i<nLibs; i++)
  {
    const char *libfname = argv[i];
    std::string solFile = pathGenerator(logdir, libfname);

    printf("Using library: %s, writing to %s\n", libfname, solFile.c_str());

    libs[i] = LibfkpsDeterminantQInitLoad(solFile.c_str(), libfname);
    if (libs[i] == NULL)
    {
      printf("Could not load: %s\n", libfname);
      return -1;
    }

  }

  for (int i=0; i<FKPS_PARALELL; i++)
  {
    ts[i] = std::thread(_commandComputeConsume, libs, nLibs);
  }

  for (int i=0; i<nLibs; i++)
  {
    ts[i].join();
  }

  delete(ts);
  return 0;
}

int commandGenerate(int argc, const char *argv[])
{
  const char *CFILE_FORMAT = 
    "int libinfo_N = %d;\n"
    "int libinfo_K = %d;\n\n"
    "int determinantQ(int *x)\n"
    "{\n"
    "    return %s;\n"
    "}\n";

  if (argc != 4)
  {
    printf("Args: '/path/to/gendir' '/path/to/parsedFile.txt'\n");
    return 1;
  }

  std::string dirname(argv[2]);
  std::string fname(argv[3]);

  std::filesystem::path dirpath(dirname);  
  std::ifstream infile(fname);

  if (!infile.is_open()) { printf("Could not open: %s", fname); return -1; }

  std::string line;
  while (std::getline(infile, line))
  {
    static int currfile = 0;
    char cfname[5];
    sprintf(cfname, "%02d.c", ++currfile);
  
    std::filesystem::path cfpath(cfname);
    cfpath = dirpath / cfpath;
  
    FILE  *file = fopen(cfpath.string().c_str(), "w");
    if (!file) { printf("Could not open: %s", fname); return -1; }

    fprintf(file, CFILE_FORMAT, 13, 48, line.c_str());
    fclose(file);
    printf("Wrote: %s\n", cfpath.string().c_str());
  }  

  return 0;
}