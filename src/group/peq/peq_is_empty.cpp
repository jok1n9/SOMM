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

        bool peqIsEmpty(uint32_t mask) 
        {
            const char *maskStr = (mask == 0) ? "ANY" : ((mask == POSTPONED) ? "POSTPONED" : "ARRIVAL | TERMINATE");
            soProbe(303, "%s(%s)\n", __func__, maskStr);

            if (mask == 0)  mask = 7;   //0b111

            for (auto it = peq::eventList.begin(); it != peq::eventList.end(); it++)
            {
                if((mask & it->eventType) != 0)
                    return false;
            }
            return true;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

