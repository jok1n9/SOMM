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

        uint32_t memGetBiggestHole()
        {
            soProbe(409, "%s()\n", __func__);
            if (mem::freeList.empty())
                return 0;
            uint32_t max = (*mem::freeList.begin()).size;   // initalized with first element
            for (auto it = std::next(mem::freeList.begin()); it != mem::freeList.end(); it++)
            {
                if(it->size > max)
                    max = it->size;
            }
            return max;
        }

// ================================================================================== //

        uint32_t memGetMaxAllowableSize()
        {
            soProbe(409, "%s()\n", __func__);
            
            return mem::memorySize - mem::osSize;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
