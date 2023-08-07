/*
 *  \author ...
 */

#include "somm22.h"
#include "sim_module.h"

namespace somm22
{

    namespace group
    {

// ================================================================================== //

        void simStep()
        {
            Event current;
            current = peqFetchNext(simGetCurrentSimMask());
            uint32_t time = pctGetProcessDuration(current.pid);
            uint32_t size = pctGetProcessAddressSpaceSize(current.pid);

            switch (current.eventType)
            {
            case TERMINATE:
                // Process is done so free its memory
                memFree(pctGetProcessMemAddress(current.pid));
                pctSetProcessState(current.pid, FINISHED);
                sim::sim_struct.currentSimTime = current.eventTime;
                break;

            case POSTPONED:
                // There is a big enough hole so alocate and run the process
                pctSetProcessMemAddress(current.pid, memAlloc(current.pid, size));
                pctSetProcessState(current.pid, RUNNING);
                pctSetProcessStartTime(current.pid, sim::sim_struct.currentSimTime);
                peqInsert(TERMINATE, time + simGetCurrentSimTime(), current.pid);
                break;

            case ARRIVAL:
                sim::sim_struct.currentSimTime = current.eventTime;
                // First come first served
                if (peqGetFirstPostponedProcess() != 0)
                {
                    peqInsert(POSTPONED, simGetCurrentSimTime(), current.pid);
                    pctSetProcessState(current.pid,SWAPPED);
                    break;
                }

                if (size > memGetMaxAllowableSize())
                // Process requires more that the total existing memory, so discard it
                {
                    pctSetProcessState(current.pid, DISCARDED);
                    break;
                }

                if (size <= memGetBiggestHole())
                // There is a big enough hole so alocate and run the process
                {
                    pctSetProcessMemAddress(current.pid, memAlloc(current.pid, size));
                    pctSetProcessState(current.pid, RUNNING);
                    pctSetProcessStartTime(current.pid, sim::sim_struct.currentSimTime);
                    peqInsert(TERMINATE, time + simGetCurrentSimTime(), current.pid);
                }
                // Process needs more space than the available but total memory is enough
                else
                {
                    peqInsert(POSTPONED, simGetCurrentSimTime(), current.pid);
                    pctSetProcessState(current.pid,SWAPPED);
                }
            break;
            }
            // Calculate next event mask
            if(peqGetFirstPostponedProcess() != 0)
            {
                if(pctGetProcessAddressSpaceSize(peqGetFirstPostponedProcess()) > memGetBiggestHole())
                    sim::sim_struct.eventMask = 0b101;
                else
                    sim::sim_struct.eventMask = 0b010;
            }
            else
                sim::sim_struct.eventMask = 0b101;
                
            sim::sim_struct.nSteps += 1;
        }

// ================================================================================== //
        
        void simRun(uint32_t cnt)
        {
            soProbe(503, "%s(cnt: %u)\n", __func__, cnt);
            
            if (cnt == 0)
                while(!peqIsEmpty())
                    simStep();
            else
                while (cnt != 0 && !peqIsEmpty())
                {
                    simStep();
                    cnt--;
                }
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
