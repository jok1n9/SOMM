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

        bool compare(const mem::Block b1, const mem::Block b2)
        {
            return b1.start < b2.start;
        }  

// ================================================================================== //           

        void memFree(void *addr)
        {
            soProbe(408, "%s(addr: %p)\n", __func__, addr);

            require(addr != NULL, "addr must be non-null");
            
            int32_t block_size = -1;

            // iterates busylist, removes block starting at addr and saves the size of the block
            for (auto it = mem::busyList.begin(); it != mem::busyList.end(); it++)
            {
                if(it->start == addr)
                {
                    block_size = it->size;
                    mem::busyList.erase(it);
                    break;
                }
            }

            // no space was erased
            if(block_size == -1)
                throw Exception(EINVAL, "memFree");

            // add new free block and sort the list
            mem::Block n;
            n.start = addr;
            n.size = block_size;
            mem::freeList.push_back(n);
            mem::freeList.sort(compare);
            
            // iterates free list to find coincident blocks that can be merged 
            for (auto it = mem::freeList.begin(); it != mem::freeList.end(); it++)
            {                
                if(addr == it->start)
                {
                    // check next free block if it exists
                    if ((char*)addr + it->size == std::next(it)->start)
                    {
                        it->size += std::next(it)->size;
                        //update lastStart if necessary
                        if (mem::lastStart == std::next(it)->start)
                            mem::lastStart = it->start;
                        mem::freeList.erase(std::next(it));
                    }
                    // check previous free block if it exists
                    if ((char*)std::next(it,-1)->start + std::next(it,-1)->size == addr)
                    {
                        it->start = std::next(it,-1)->start;
                        it->size += std::next(it,-1)->size;
                        //update lastStart if necessary
                        if(mem::lastStart == std::next(it,-1)->start)
                            mem::lastStart = it->start;
                        mem::freeList.erase(std::next(it,-1));
                    }
                    return;
                }
            }
            throw Exception(EINVAL, "memFree");
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

