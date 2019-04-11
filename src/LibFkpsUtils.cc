#include "LibFkps.h"
#include "libfkpsconfig.h"

#include "LibFkpsDeterminantQ.hh"
#include "LibFkpsUtils.hh"

#include "LibFkpsLogging.hh"

#include <thread>
#include <atomic>


#ifdef FKPS_COMPUTE_PARALELL_SINGLELIB

void PartitionConsumeBatch(

    LibfkpsDeterminantQ_t *lib,
	LibFkpsBatch_t *state

)
{
    LibFkpsBatch_t *batch;

    while(true)
    {
        state->_mutex->lock();
        batch = LibFkpsBatchNew(state);
        state->_mutex->unlock();

        int bs = batch->batchSize;
        
        for (int i=0; i<batch->batchSize; i++)
        {
			FkpsBatchIncrement(batch);
            LibfkpsDeterminantQCompute(lib, batch->v);
        }

        LibFkpsBatchFree(batch);

        if (bs == 0) break;
    }

}


void LibFkpsParallelCompute(

    FKPSLIBV *libV,
    int parallelJobs

)
{
    std::thread *ts = new std::thread[parallelJobs];

    for (FKPSLIB lib : (*libV))
    {
		if (!LibfkpsDeterminantQLoad(lib))
			continue;

        __fkps_log_started(lib);
        
		LibFkpsBatch_t *state = LibFkpsBatchInit(lib);

        for (int i=0; i<parallelJobs; i++)
            ts[i] = std::thread(&PartitionConsumeBatch, lib, state);
        for (int i=0; i<parallelJobs; i++)
            ts[i].join();

        if (lib->_stackcounter > 0)
            LibfkpsDeterminantQDump(lib);

        LibFkpsBatchFree(state);
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

	if (!LibfkpsDeterminantQLoad(lib))
		continue;

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


#ifdef FKPS_COMPUTE_CUDA_SINGLELIB

void LibFkpsParallelCompute(

	FKPSLIBV* lib,
	int parallelJobs

)
{

}

#endif // FKPS_COMPUTE_CUDA_SINGLELIB