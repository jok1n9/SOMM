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

        void peqTableFormat(FILE* fp)
        {
            // Build Table
            fprintf(fp,"+===============================+\n");
            fprintf(fp,"|      Process Event Queue      |\n");
            fprintf(fp,"+-----------+-----------+-------+\n");
            fprintf(fp,"| eventTime | eventType |  PID  |\n");
            fprintf(fp,"+-----------+-----------+-------+\n");

            // Table content
            for (auto it = peq::eventList.begin(); it != peq::eventList.end(); it++)
            {
                fprintf(
                        fp,
                        "| %9u | %-9s | %5u |\n",
                        it->eventTime,peqEventTypeAsString(it->eventType),it->pid
                );
            }
            // Table end
            fprintf(fp,"+===============================+\n\n");
        }

// ================================================================================== //

        void peqLog()
        {
            soProbe(302, "%s()\n", __func__);

            FILE* fp = logGetStream();
            peqTableFormat(fp);
        }

// ================================================================================== //

        void peqLogEvent(Event *e, const char *msg)
        {
            soProbe(302, "%s(...)\n", __func__);
            
            FILE* fp = logGetStream();
            fprintf(fp,"%s", msg);
            fprintf(fp,": (%s, %u, %u)\n",peqEventTypeAsString(e->eventType), e->eventTime, e->pid);
        }

// ================================================================================== //

        void peqPrint(const char *fname, PrintMode mode)
        {
            soProbe(302, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");

            FILE *fp;
            mode == NEW ? fp = fopen(fname, "w") : fp = fopen(fname, "a");
            // file doesn't exist
            if (fp == NULL)
                throw Exception(ENOENT,"peqPrint");
            peqTableFormat(fp);
            fclose(fp);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

