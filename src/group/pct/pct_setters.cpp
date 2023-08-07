/*
 *  \author ...
 */

#include "somm22.h"
#include "pct_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void pctSetProcessMemAddress(uint32_t pid, void *memAddr)
        {
            soProbe(207, "%s(%d, %p)\n", __func__, pid, memAddr);

            require(pid > 0, "process ID must be non-zero");

            // set process memory address based on its pid
            for (auto pos = pct::processList.begin(); pos != pct::processList.end(); pos++)
            {
                if (pos->pid == pid)
                {
                    pos->memAddr = memAddr;
                    return;
                }
            }
            throw Exception(EINVAL,"pctSetProcessMemAddress");
        }

// ================================================================================== //

        void pctSetProcessState(uint32_t pid, ProcessState state)
        {
            soProbe(208, "%s(%d, %s)\n", __func__, pid, pctStateAsString(state));

            require(pid > 0, "process ID must be non-zero");

            for (auto pos = pct::processList.begin(); pos != pct::processList.end(); pos++)
            {
                if (pos->pid == pid)
                {
                    pos->state = state;
                    return;
                }
            }
            throw Exception(EINVAL,"pctSetProcessState");
        }

// ================================================================================== //

        void pctSetProcessStartTime(uint32_t pid, uint32_t time)
        {
            soProbe(209, "%s(%d, %u)\n", __func__, pid, time);

            require(pid > 0, "process ID must be non-zero");

            for (auto pos = pct::processList.begin(); pos != pct::processList.end(); pos++)
            {
                if (pos->pid == pid)
                {
                    if (time < pos->arrivalTime)
                        Exception(EINVAL,"pctSetProcessStartTime");

                    pos->startTime = time;
                    return;
                }
            }
            throw Exception(EINVAL,"pctSetProcessStartTime");
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
