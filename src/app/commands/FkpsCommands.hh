#ifndef _FKPSCOMMANDS_H
#define _FKPSCOMMANDS_H

#include <vector>
#include <filesystem>

#include "LibFkps.h"
#include "LibFkpsUtils.hh"

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