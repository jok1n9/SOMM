/*
 *  \author ...
 */

#ifndef __SOMM22__MODULE__SIM__GROUP__
#define __SOMM22__MODULE__SIM__GROUP__

#include <stdint.h>
#include <list>
#include <stdio.h>

namespace somm22 
{
    namespace group
    {
        namespace sim
        {
            struct sim_module
            {
                uint32_t nSteps;
                uint32_t currentSimTime;
                uint32_t eventMask;
            };
            extern sim::sim_module sim_struct;
        
        } // end of namespace sim

    } // end of namespace group

} // end of namespace somm22

#endif /* __SOMM22__MODULE__SIM__GROUP__ */

