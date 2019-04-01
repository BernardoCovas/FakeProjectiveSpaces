#include <stdio.h>
#include <string.h>
#include <fstream>
#include <thread>
#include <atomic>
#include <filesystem>

#include "LibFkpsDeterminantQ.h"
#include "libfkpsconfig.h"
#include "commands/FkpsCommands.hh"

#define COMMAND_COMPUTE  "compute"
#define COMMAND_COMPILE  "compile"
#define COMMAND_GENERATE "generate"
#define COMMAND_ALL      "all"


int commandGenerate (int argc, const char *argv[]);
int commandCompile  (int argc, const char *argv[]);
int commandCompute  (int argc, const char *argv[]);
int commandAll      (int argc, const char *argv[]);


int main(int argc, char const *argv[])
{

  if (argc < 2)
  {
    printf("Args: 'command' [Args ...]. Commands: generate, compile, compute, all\n");
    return 1;
  }

  const char *command = argv[1];

  argv += 2;
  argc -= 2;

  if(strcmp(command, COMMAND_GENERATE) == 0)
    return commandGenerate(argc, argv);
  if(strcmp(command, COMMAND_COMPILE) == 0)
    return commandCompile(argc, argv);
  if(strcmp(command, COMMAND_COMPUTE) == 0)
    return commandCompute(argc, argv);
  if(strcmp(command, COMMAND_ALL) == 0)
    return commandAll(argc, argv);
}

int commandCompile(int argc, const char *argv[])
{
  if (argc < 2)
  {
    printf("Args: 'compileCommandFormat' '/path/to/c/file.c' ['/path/to/c/file2.c' ... ]\n");
    return 1;
  }

  FSPATHV inFilepathV;
  FSPATHV outLibpathV;
  std::string compileCommand(argv[0]);

  for (int i=1; i<argc; i++)
    inFilepathV.push_back(FSPATH(argv[i]));

  return FkpsCommandCompile(
    inFilepathV,
    outLibpathV,
    compileCommand
    );

}

int commandCompute(int argc, const char *argv[])
{

  if (argc < 2)
  {
    printf("Args: '/path/to/logdir' '/path/to/dir/compiled.c.so' ['/path/to/dir/compiled2.c.so' ... ]\n");
    return 1;
  }

  FSPATH logDir(argv[0]);
  FSPATHV libPathV;
  for (int i=1; i<argc; i++)
    libPathV.push_back(FSPATH(argv[i]));
  
  FkpsCommandCompute(
    libPathV,
    logDir
    );

  return 0;
}

int commandGenerate(int argc, const char *argv[])
{

  if (argc != 2)
  {
    printf("Args: '/path/to/parsedFile.txt' '/path/to/gendir'\n");
    return 1;
  }

  FSPATH fname  (argv[0]);
  FSPATH dirname(argv[1]);
  FSPATHV _outDir;

  return FkpsCommandGenerate(
    dirname,
    fname,
    _outDir
  );

}


int commandAll(int argc, const char *argv[])
{
  if (argc != 2)
  {
    printf("Args: '/path/to/expressionCFile.txt' 'compile_command'\n");
    return 1;
  }

  FSPATH detPath    ("det");
  FSPATH solvedPath ("solved");
  FSPATH cFilePath  (argv[0]);
  std::string       compileCommand(argv[1]);

  std::filesystem::create_directories(detPath);
  std::filesystem::create_directories(solvedPath);

  FSPATHV cFilePathV;
  FSPATHV libPathV;
  int resCode;

  resCode = FkpsCommandGenerate(
    detPath,
    cFilePath,
    cFilePathV
    );

  if(resCode != 0) return 1;


  resCode = FkpsCommandCompile(
    cFilePathV,
    libPathV,
    compileCommand
    );

  if(resCode != 0) return 2;


  resCode = FkpsCommandCompute(
    libPathV,
    solvedPath
  );

  if(resCode != 0) return 3;

  return 0;
}