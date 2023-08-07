/*
 *  \author ...
 */

#include "somm22.h"
#include "pct_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        const char *pctStateAsString(ProcessState state)
        {
            soProbe(291, "%s(\"%u\")\n", __func__, state);

            const char* names [] = {"TO_COME","RUNNING","SWAPPED","FINISHED","DISCARDED"};            
            return names[state];
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

