/*
 *  \author ...
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        bool compareBystart(mem::Block b1, mem::Block b2)
        {
            return b1.start < b2.start;
        }

// ================================================================================== //

        void *memAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(403, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");

            uint32_t rounded_up = ((size + mem::chunkSize - 1) / mem::chunkSize) * mem::chunkSize;

            void* address;
            
            switch (mem::policy)
            {
            case FirstFit:
                address = memFirstFitAlloc(pid,rounded_up);
                break;
            case NextFit:
                address = memNextFitAlloc(pid,rounded_up);
                break;
            case BestFit:
                address = memBestFitAlloc(pid,rounded_up);
                break;
            case WorstFit:
                address = memWorstFitAlloc(pid,rounded_up);                
                break;
            default:
                throw Exception(EINVAL,"memAlloc");            
            }
            mem::busyList.sort(compareBystart);
            return address;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

