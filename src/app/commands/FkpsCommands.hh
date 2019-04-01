#ifndef _FKPSCOMMANDS_H
#define _FKPSCOMMANDS_H

#include <filesystem>
#include "LibFkpsDeterminantQ.h"

typedef std::filesystem::path FSPATH;
typedef std::vector<FSPATH> FSPATHV;

typedef LibfkpsDeterminantQ_t FKPSLIB;
typedef std::vector<FKPSLIB> FKPSLIBV;

int FkpsCommandGenerate(
    
    FSPATH  genPath,
    FSPATH  cParsedFile,
    FSPATHV &outPathv

);

int FkpsCommandCompile(
    
    FSPATHV     &cFilePathV,
    FSPATHV     &outLibPathV,
    std::string compileCommand

);

int FkpsCommandCompute(

    FSPATHV &libPathV,
    FSPATH   logDir

);


#endif // _FKPSCOMMANDS_H