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

        const char *peqEventTypeAsString(EventType type)
        {
            soProbe(397, "%s(\"0x%x\")\n", __func__, type);

            const char* names [] = {
                NULL,           // 0 ; 0b000 - not relevant
                "ARRIVAL",      // 1 ; 0b001
                "POSTPONED",    // 2 ; 0b010
                NULL,           // 3 ; 0b011 - not relevant
                "TERMINATE"     // 4 ; 0b100
            };
            
            return names[type];
        }

// ================================================================================== //

        const char *peqEventMaskAsString(uint32_t mask)
        {
            soProbe(397, "%s(\"0x%x\")\n", __func__, mask);

            require((mask | 0b111) == 0b111, "wrong event mask");

            const char* names [] = {
                "ARRIVAL | POSTPONED | TERMINATE",  // 0 ; 0b000
                "ARRIVAL",                          // 1 ; 0b001
                "POSTPONED",                        // 2 ; 0b010
                "ARRIVAL | POSTPONED",              // 3 ; 0b011
                "TERMINATE",                        // 4 ; 0b100
                "ARRIVAL | TERMINATE",              // 5 ; 0b101
                "POSTPONED | TERMINATE",            // 6 ; 0b110
                "ARRIVAL | POSTPONED | TERMINATE"   // 7 ; 0b111
            };

            return names[mask];
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

