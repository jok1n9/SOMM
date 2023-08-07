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

        void peqInsert(EventType type, uint32_t time, uint32_t pid)
        {
            soProbe(304, "%s(%s, %u, %u)\n", __func__, peqEventTypeAsString(type), time, pid);

            require(pid > 0, "process ID must be non-zero");

            somm22::Event event;     //new event
            event.eventType = type;
            event.eventTime = time;
            event.pid = pid;

            if (peq::eventList.empty())
            {     
                peq::eventList.insert(peq::eventList.begin(),event);
                return;
            }

            for (auto it = peq::eventList.begin(); it != peq::eventList.end(); it++)
            {  //iterate through process list

                //inserted in sorted by eventTime position
                if (event.eventTime < it->eventTime)
                {
                    peq::eventList.insert((it),event);
                    return;
                }
                else if (it->pid == event.pid)
                    throw Exception(EINVAL,"peqInsert");
            }
            // list has been iterated with no insertion so insert at the end
            peq::eventList.insert(peq::eventList.end(),event);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
