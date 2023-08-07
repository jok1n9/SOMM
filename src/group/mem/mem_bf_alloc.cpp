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

        void *memBestFitAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(406, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");

            if (mem::freeList.empty())
                return NULL;
                
            // initialized with first element of list
            mem::Block min = *mem::freeList.begin();

            // loop to find bestFitAlloc start address
            for (auto it = std::next(mem::freeList.begin(),1); it != mem::freeList.end(); it++)
            {
                if (it->size < min.size && it->size >= size)
                    min = *it;
            }

            // didn't find a valid address
            if(min.size < size)
                return NULL;
            
            // loop to the address and
            for (auto it = mem::freeList.begin(); it != mem::freeList.end(); it++)
            {
                if (it->start == min.start)
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
