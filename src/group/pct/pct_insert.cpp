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

        void pctInsert(uint32_t pid, uint32_t arrivalTime, uint32_t duration, uint32_t addrSpaceSize)
        {
            soProbe(203, "%s(%d, %u, %u, 0x%x)\n", __func__, pid, arrivalTime, duration, addrSpaceSize);

            pct::Process proc;     //new process
            proc.pid = pid;
            proc.arrivalTime = arrivalTime;
            proc.duration = duration;
            proc.addrSpaceSize = addrSpaceSize;
            proc.memAddr = NULL;
            proc.state = TO_COME;
            proc.startTime = 0xFFFFFFFF;

            // if list is empty just insert
            if (pct::processList.empty())
            {
                pct::processList.insert(pct::processList.begin(),proc);
                return;
            }

            for (auto it = pct::processList.begin(); it != pct::processList.end(); it++)
            {   // iterate through process list

                // inserted in sorted by pid position
                if (proc.pid < it->pid)
                {
                    pct::processList.insert((it),proc);
                    return;
                }
                else if (it->pid == proc.pid)
                    throw Exception(EINVAL,"pctInsert");
            }
            // list has been iterated with no insertion so insert at the end
            pct::processList.insert(pct::processList.end(),proc);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
