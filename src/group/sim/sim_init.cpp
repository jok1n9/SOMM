/*
 *  \author ...
 */

#include "somm22.h"
#include "sim_module.h"

namespace somm22 
{

    namespace group
    {

// ================================================================================== //

        /*
         * \brief Init the module's internal data structure
         */
        void simInit()
        {
            soProbe(501, "%s()\n", __func__);
            
            sim::sim_struct.nSteps = 0;
            sim::sim_struct.eventMask = 5;
            sim::sim_struct.currentSimTime = 0;
            
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
