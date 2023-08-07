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

        uint32_t pctGetProcessDuration(uint32_t pid)
        {
            soProbe(204, "%s(%d)\n", __func__, pid);

            require(pid > 0, "process ID must be non-zero");

            // get element from list with pid equal to pid
            for (auto pos = pct::processList.begin(); pos != pct::processList.end(); pos++)
            {
                if (pos->pid == pid)
                {
                    return pos->duration;
                }
            }
            throw Exception(EINVAL,"pctGetProcessDuration");
        }

// ================================================================================== //

        uint32_t pctGetProcessAddressSpaceSize(uint32_t pid)
        {
            soProbe(205, "%s(%d)\n", __func__, pid);

            require(pid > 0, "process ID must be non-zero");
            for (auto pos = pct::processList.begin(); pos != pct::processList.end(); pos++)
            {
                if (pos->pid == pid)
                {
                    return pos->addrSpaceSize;
                }
            }
            throw Exception(EINVAL,"pctGetProcessAddressSpaceSize");
        }

// ================================================================================== //

        void *pctGetProcessMemAddress(uint32_t pid)
        {
            soProbe(206, "%s(%d)\n", __func__, pid);

            require(pid > 0, "process ID must be non-zero");

            for (auto pos = pct::processList.begin(); pos != pct::processList.end(); pos++)
            {
                if (pos->pid == pid)
                {
                    return pos->memAddr;
                }
            }
            throw Exception(EINVAL,"pctGetProcessMemAddress");
        }

// ================================================================================== //

        const char *pctGetStateName(uint32_t pid)
        {
            soProbe(210, "%s(\"%u\")\n", __func__, pid);

            for (auto pos = pct::processList.begin(); pos != pct::processList.end(); pos++)
            {
                if (pos->pid == pid)
                {
                    return pctStateAsString(pos->state);
                }
            }
           throw Exception(EINVAL,"pctGetStateName");
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
