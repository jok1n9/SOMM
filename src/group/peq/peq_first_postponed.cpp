/*
 *  \author ...
 */

#include "somm22.h"
#include "peq_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        uint32_t peqGetFirstPostponedProcess() 
        {
            soProbe(306, "%s()\n", __func__);

            for (auto it = peq::eventList.begin(); it != peq::eventList.end(); it++)
            {
                if (it->eventType == POSTPONED)
                {
                    return it->pid;
                }
            }
            return 0;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm2
