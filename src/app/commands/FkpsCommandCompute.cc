#include <stdio.h>
#include <filesystem>
#include <atomic>
#include <thread>

#include "FkpsCommands.hh"
#include "LibFkpsDeterminantQ.h"
#include "LibFkpsUtils.hh"


int FkpsCommandCompute(

    FSPATHV &libPathV,
    FSPATH   logDir

)
{    
    printf("Using directory: %s\n", logDir.string().c_str());
    printf("Using %d library files.\n", (int) libPathV.size());

    FKPSLIBV loadedLibV;
    
    for (int i=0; i < (int) libPathV.size(); i++)
    {
        FSPATH libPath(libPathV[i]);
        FSPATH logFile(logDir);

        logFile /= libPath.filename();
        logFile.replace_extension("csv");

        printf(
            "Using library: %s, writing to %s\n",
            libPath.string().c_str(),
            logFile.string().c_str()
            );

         FKPSLIB *lib = (LibfkpsDeterminantQ_t *) LibfkpsDeterminantQInitLoad(
            logFile.string().c_str(),
            libPath.string().c_str()
            );

        if (lib == NULL)
        {
            printf(
                "Could not load: %s\n",
                libPath.string().c_str()
                );

            for (int j=0; j<i-1; j++)
                LibfkpsDeterminantQDeInitUnload(
                    &loadedLibV[j]
                    );
            
            return -1;
        }
 
        loadedLibV.push_back(*lib);
    }
    
    LibFkpsParallelCompute(&loadedLibV, FKPS_COMPUTE_PARALELL);

    return 0;
}