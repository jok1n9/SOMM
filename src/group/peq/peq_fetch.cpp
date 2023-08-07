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

        Event peqFetchNext(uint32_t mask)
        {
            const char *maskStr = (mask == 0) ? "ANY" : ((mask == POSTPONED) ? "POSTPONED" : "ARRIVAL | TERMINATE");
            soProbe(305, "%s(%s)\n", __func__, maskStr);

            if (mask == 0)  mask = 7;   //0b111
            
            for (auto it = peq::eventList.begin(); it != peq::eventList.end(); it++)
            {
                if ((mask & it->eventType) != 0)
                { 
                    // tmp Event to save value to be returned
                    Event tmp;
                    tmp.eventTime = it->eventTime;
                    tmp.eventType = it->eventType;
                    tmp.pid = it->pid;
                    
                    peq::eventList.erase(it);
                    return tmp;
                }
            }
            // In case there is no match
            throw Exception(EINVAL,"peqFetchNext"); 
        }

// ================================================================================== //

        Event peqPeekNext(uint32_t mask)
        {
            const char *maskStr = (mask == 0) ? "ANY" : ((mask == POSTPONED) ? "POSTPONED" : "ARRIVAL | TERMINATE");
            soProbe(305, "%s(%s)\n", __func__, maskStr);
            
            if (mask == 0)  mask = 7;   //0b111

            for (auto it = peq::eventList.begin(); it != peq::eventList.end(); it++)
            {
                if ((mask & it->eventType) != 0)
                    return *it;
            }
            // In case there is no match
            throw Exception(EINVAL,"peqPeekNext");
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
