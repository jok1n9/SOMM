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

        void memInit(uint32_t mSize, uint32_t osSize, uint32_t cSize, AllocationPolicy allocPolicy)
        {
            soProbe(401, "%s(0x%x, 0x%x, 0x%x, %s)\n", __func__, mSize, osSize, cSize, memAllocationPolicyAsString(allocPolicy));

            require(mSize > osSize, "memory must be bigger than the one use by OS");
            require((mSize % cSize) == 0, "memory size must be a multiple of chunck size");
            require((osSize % cSize) == 0, "memory size for OS must be a multiple of chunck size");

            // Make sure lists are empty before init
            if (!mem::freeList.empty() || !mem::busyList.empty())
                throw Exception(EINVAL,"memInit");
            
            mem::policy = allocPolicy;
            mem::chunkSize = cSize;
            mem::memorySize = mSize;
            mem::osSize = osSize;

            mem::Block init;
            init.start = 0;
            init.start = (char*)init.start + (osSize);
            init.size = mSize - osSize;

            mem::lastStart = init.start;
            mem::freeList.push_back(init);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

