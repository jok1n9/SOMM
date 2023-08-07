/*
 *  \author ...
 */

#ifndef __SOMM22__MODULE__MEM__GROUP__
#define __SOMM22__MODULE__MEM__GROUP__

#include "somm22.h"
#include <list>

namespace somm22
{
    
    namespace group 
    {

        namespace mem
        {
            struct Block
            {
                uint32_t pid;
                void* start;
                uint32_t size;
            };

            extern std::list<Block> freeList;
            extern std::list<Block> busyList;
            extern AllocationPolicy policy;
            extern uint32_t chunkSize;
            extern uint32_t memorySize;
            extern uint32_t osSize;
            extern void* lastStart;         //points to the start address of the last allocated hole 

        } // end of namespace mem

    } // end of namespace group

} // end of namespace somm22

#endif /* __SOMM22__MODULE__MEM__GROUP__ */


