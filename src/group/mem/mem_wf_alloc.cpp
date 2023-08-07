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

        void *memWorstFitAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(407, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");

            if (mem::freeList.empty())
                return NULL;

            // initialized with first element of list
            mem::Block max = *mem::freeList.begin();

            // loop to find wortstFitAlloc start address
            for (auto it = std::next(mem::freeList.begin(),1); it != mem::freeList.end(); it++)
            {
                mem::Block b = *(it);
                if (b.size > max.size)
                    max = b;
            }

            // didn't find a valid address
            if(max.size < size)
                return NULL;

            // loop to the address and alloc 
            for (auto it = mem::freeList.begin(); it != mem::freeList.end(); it++)
            {
                mem::Block b = (*it);
                if (b.start == max.start)
                {
                    // new block in the busy list
                    mem::Block busy;
                    busy.pid = pid;
                    busy.start = (*it).start;
                    busy.size = size;
                    mem::busyList.push_back(busy);
                    
                    // if the process needs the entire block just delete it from free list
                    if (b.size == size)
                        mem::freeList.erase(it);
                    // update the block memory will be allocated from
                    else
                    {
                        (*it).start = (char*)(*it).start + size;
                        (*it).size -= size;
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
