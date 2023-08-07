/*
 *  \author ...
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{
    namespace group 
    {
        namespace mem
        {
            std::list<Block> freeList;
            std::list<Block> busyList;
            AllocationPolicy policy;
            uint32_t chunkSize;
            uint32_t memorySize;
            uint32_t osSize;
            void* lastStart;
            
        } // end of namespace mem

    } // end of namespace group

} // end of namespace somm22

