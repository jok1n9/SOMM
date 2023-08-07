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

        const char *memAllocationPolicyAsString(AllocationPolicy policy)
        {
            soProbe(490, "%s(\"%u\")\n", __func__, policy);

            const char* names [] = {"FirstFit","NextFit","BestFit","WorstFit"};
            return names[policy];
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

