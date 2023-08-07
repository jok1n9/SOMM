/*
 *  \author ...
 */

#ifndef __SOMM22__MODULE__PCT__GROUP__
#define __SOMM22__MODULE__PCT__GROUP__

#include "somm22.h"

#include <list>

namespace somm22
{
    
    namespace group 
    {

        namespace pct
        {

            struct Process
            {
                uint32_t pid;
                uint32_t arrivalTime;
                uint32_t duration;
                uint32_t addrSpaceSize;
                void *memAddr;
                ProcessState state;
                uint32_t startTime;
            };

            extern std::list<Process> processList;

        } // end of namespace pct

    } // end of namespace group

} // end of namespace somm22

#endif /* __SOMM22__MODULE__PCT__GROUP__ */

