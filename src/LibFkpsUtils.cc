#include "LibFkpsDeterminantQ.h"
#include "libfkpsconfig.h"

#include "LibFkpsDeterminantQ.hh"
#include "LibFkpsUtils.hh"

#include <thread>
#include <atomic>


void __fkps_log_started(LibfkpsDeterminantQ_t *lib);


#ifdef FKPS_COMPUTE_PARALELL_SINGLELIB

void PartitionConsumeBatch(

    LibfkpsDeterminantQ_t *lib,
    LibFkpsPartitionBatchState_t *state

)
{
    LibFkpsUtilsPartitionBatch_t *batch;

    while(true)
    {
        state->_mutex->lock();
        batch = LibFkpsUtilsNewBatch(state);
        state->_mutex->unlock();

        int bs = batch->batchSize;
        
        for (int i=0; i<batch->batchSize; i++)
        {
            int *batchV = LibFkpsUtilsBatchGet(batch, i);
            LibfkpsDeterminantQCompute(lib, batchV);
        }

        LibFkpsUtilsFreeBatch(batch);

        if (bs == 0) break;
    }

}


void LibFkpsParallelCompute(

    FKPSLIBV *libV,
    int parallelJobs

)
{
    std::thread *ts = new std::thread[parallelJobs];

    for (auto _lib : (*libV))
    {
        LibfkpsDeterminantQ_t *lib = (LibfkpsDeterminantQ_t *) _lib;
        __fkps_log_started(lib);

        LibFkpsPartitionBatchState_t *state = LibFkpsUtilsStateInit(lib);

        for (int i=0; i<parallelJobs; i++)
            ts[i] = std::thread(&PartitionConsumeBatch, lib, state);
        for (int i=0; i<parallelJobs; i++)
            ts[i].join();

        if (lib->_stackcounter > 0)
            LibfkpsDeterminantQDump(lib);

        LibFkpsUtilsFreeState(state);
        LibfkpsDeterminantQDeInitUnload(lib);
    }

    delete[] ts;
}

#endif // FKPS_COMPUTE_PARALELL_SINGLELIB

#ifdef FKPS_COMPUTE_PARALELL_MULTILIB

void FkpsCommandExecute(
    
    FKPSLIBV *fkpsLibV

)
{
  static std::atomic_int threadID = 0;

  while(true)
  {
    int t_id = threadID++;
    if (t_id >= (int) fkpsLibV->size())
      return;

    FKPSLIB lib = fkpsLibV->operator[](t_id);
    __fkps_log_started(lib);

    LibfkpsDeterminantQComputeAll(lib);
    LibfkpsDeterminantQDeInitUnload(lib);

  }

}

void LibFkpsParallelCompute(

    FKPSLIBV *lib,
    int parallelJobs
    
)
{
    std::thread *ts = new std::thread[parallelJobs];

    for (int i=0; i<parallelJobs; i++)
    {
        ts[i] = std::thread(&FkpsCommandExecute, lib);
    }

    for (int i=0; i<parallelJobs; i++)
        ts[i].join();

    delete[] ts;
}

#endif // FKPS_COMPUTE_PARALELL_MULTILIB

void __fkps_log_started(LibfkpsDeterminantQ_t *lib)
{
    printf("Starting computing: %s\n", lib->libname);
}