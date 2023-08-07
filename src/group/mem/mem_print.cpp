/*
 *  \author ...
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void memTableFormat(FILE* fp)
        {
            // Busy list Table
            fprintf(fp,"+==============================+\n");
            fprintf(fp,"|  Memory Management busy list |\n");
            fprintf(fp,"+-------+-----------+----------+\n");
            fprintf(fp,"|  PID  |   start   |   size   |\n");
            fprintf(fp,"+-------+-----------+----------+\n");
            // Table content
            for (auto it = mem::busyList.begin(); it != mem::busyList.end(); it++)
            {
                fprintf(
                    fp,
                    "| %5u | %9p | %#8x |\n",
                    it->pid,it->start,it->size
                );
            }
            // Table end
            fprintf(fp,"+==============================+\n\n");

            // ======================================================================//

            // Free list Table
            fprintf(fp,"+==============================+\n");
            fprintf(fp,"|  Memory Management free list |\n");
            fprintf(fp,"+-------+-----------+----------+\n");
            fprintf(fp,"|  PID  |   start   |   size   |\n");
            fprintf(fp,"+-------+-----------+----------+\n");
            // Table content
            for (auto it = mem::freeList.begin(); it != mem::freeList.end(); it++)
            {
                fprintf(
                    fp,
                    "|  ---  | %9p | %#8x |\n",
                    it->start,it->size
                );
            }
            // Table end
            fprintf(fp,"+==============================+\n\n");
        }

// ================================================================================== //

        void memLog()
        {
            soProbe(402, "%s()\n", __func__);

            FILE* fp = logGetStream();
            memTableFormat(fp);
        }

// ================================================================================== //

        void memPrint(const char *fname, PrintMode mode)
        {
            soProbe(402, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");

            FILE *fp;
            mode == NEW ? fp = fopen(fname, "w") : fp = fopen(fname, "a");
            // file doesn't exist
            if (fp == NULL)
                throw Exception(ENOENT,"memPrint");
            memTableFormat(fp);
            fclose(fp);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
