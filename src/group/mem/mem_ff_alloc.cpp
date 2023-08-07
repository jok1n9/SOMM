/*
 *  \author ...
 */

#include "somm22.h"
#include "mem_module.h"
#include <iostream>

namespace somm22
{
    namespace group 
    {

// ================================================================================== //

        void *memFirstFitAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(404, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");

            // loop until an address with enough space is found and alloc
            for (auto it = mem::freeList.begin(); it != mem::freeList.end(); it++)
            {
                if (it->size >= size)
                {      
                    // new block in the busy list
                    mem::Block busy;
                    busy.pid = pid;
                    busy.start = it->start;
                    busy.size = size;
                    mem::busyList.push_back(busy);
                    
                    // if the process needs the entire block just delete it from free list
                    if (it->size == size)
                        mem::freeList.erase(it);
                    // update the block memory will be allocated from
                    else
                    {
                        it->start = (char*)it->start + size;
                        it->size -= size;
                    }
                    // update lastStart
                    mem::lastStart = it->start;
                    return busy.start;
                }
            }
            return NULL;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
