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

        void pctTableFormat(FILE* fp)
        {
            // Build Table
            fprintf(fp,"+====================================================================================+\n");
            fprintf(fp,"|                               Process Control Table                                |\n");
            fprintf(fp,"+-------+-------------+----------+---------------+-----------+-----------------------+\n");
            fprintf(fp,"|  PID  | arrivalTime | duration | addrSpaceSize |   state   | startTime |  memAddr  |\n");
            fprintf(fp,"+-------+-------------+----------+---------------+-----------+-----------------------+\n");

            // Table content
            for (auto it = pct::processList.begin(); it != pct::processList.end(); it++)
            {
                fprintf(
                    fp,
                    it->memAddr != NULL
                        ?
                            "| %5u | %11u | %8u | %#13x | %-9s | %9u | %9p |\n"
                        :
                            "| %5u | %11u | %8u | %#13x | %-9s |   (nil)   |   (nil)   |\n"
                        ,
                    it->pid,it->arrivalTime,it->duration,it->addrSpaceSize,pctStateAsString(it->state),it->startTime,it->memAddr
                );
            }
            // Table end
            fprintf(fp,"+====================================================================================+\n\n");
        }

        void pctPrint(const char *fname, PrintMode mode)
        {
            soProbe(202, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");

            FILE *fp;
            mode == NEW ? fp = fopen(fname, "w") : fp = fopen(fname, "a");
            // file doesn't exist
            if (fp == NULL)
                throw Exception(ENOENT,"pctPrint");
            pctTableFormat(fp);
            fclose(fp);
        }

        // ================================================================================== //

        void pctLog()
        {
            soProbe(202, "%s()\n", __func__);

            FILE* fp = logGetStream();
            pctTableFormat(fp);
        }

        // ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
