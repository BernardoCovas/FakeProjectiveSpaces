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

    for (FKPSLIB lib : (*libV))
    {
		if (!LibfkpsDeterminantQLoad(lib))
			continue;

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


void LibfkpsPartitionGenerate(

	FKPS _lib,
	void (*callback)(FKPS lib, int *x)

)
{
	LibfkpsDeterminantQ_t* lib = (LibfkpsDeterminantQ_t*)_lib;

	int n = lib->libinfo_N;
	int k = lib->libinfo_K;
	int* v = (int*)malloc(sizeof(int) * n);

	for (int j = 0; j < n; ++j) {
		v[j] = 1;
	}

	int cap = k - n + 1;
	int i, s;
	v[0] = cap;

	callback(lib, v);

	while (v[n - 1] != cap) {

		i = n;
		while (v[--i] == 1);

		if (i != n - 1) {
			--v[i];
			v[i + 1] = 2;
		}
		else {
			while (v[--i] == 1);
			--v[i];
			s = v[n - 1];
			v[n - 1] = 1;
			v[i + 1] = s + 1;
		}

		callback(lib, v);

	}

	free(v);
}