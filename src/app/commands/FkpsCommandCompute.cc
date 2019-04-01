#include <stdio.h>
#include <filesystem>
#include <atomic>
#include <thread>

#include "FkpsCommands.hh"
#include "LibFkpsDeterminantQ.h"

void FkpsCommandExecute(
    
    FKPSLIBV *fkpsLibV

)
{
  static std::atomic_int threadID = 0;

  while(true)
  {
    int t_id = threadID++;
    if (t_id >= (int) fkpsLibV->size())
    {
      printf("Thread exited.\n");
      return;
    }
    FKPSLIB lib = fkpsLibV->operator[](t_id);
    printf("Starting %s.\n", lib.libname);

    LibfkpsDeterminantQComputeAll(&lib);
    LibfkpsDeterminantQDeInitUnload(&lib);

    printf("Finished %s.\n", lib.libname);
  }

}


int FkpsCommandCompute(

    FSPATHV &libPathV,
    FSPATH   logDir
)
{    
    printf("Using directory: %s\n", logDir.string().c_str());
    printf("Using %d library files.\n", (int) libPathV.size());

    std::thread *ts = new std::thread[FKPS_PARALELL];
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

         FKPSLIB *lib = LibfkpsDeterminantQInitLoad(
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
            
            delete[] ts;
            return -1;
        }
 
        loadedLibV.push_back(*lib);
    }
    
    for (int i=0; i<FKPS_PARALELL; i++)
    {
        ts[i] = std::thread(&FkpsCommandExecute, &loadedLibV);
    }

    for (int i=0; i<FKPS_PARALELL; i++)
        ts[i].join();

    delete[] ts;
    return 0;
}