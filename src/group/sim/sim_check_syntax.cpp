/*
 *  \author ...
 */

#include "somm22.h"
#include "sim_module.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

namespace somm22
{

    namespace group
    {

// ================================================================================== //

        bool simCheckInputFormat(const char *fname)
        {
            soProbe(502, "%s(\"%s\")\n", __func__, fname);

            FILE* fp = fopen(fname,"r");

            // file doesn't exist
            if (fp == NULL)
                throw Exception(ENOENT,"simCheckInputFormat");
            fclose(fp);
            
            std::vector<uint32_t> pids;     // keep track of processed PIDs
            uint32_t lineNumber = 0;        // keeps track of line number on the file
            
            // Read file line by line
            std::ifstream fin(fname);
            std::string line;
            while(getline(fin,line))
            {
                lineNumber++;

                // findes the 1st elem that is not a whitespace
                uint32_t index = line.find_first_not_of(" \t\n\r\f\v");

                //empty line
                if (line.empty() or index == std::string::npos)
                {
                    fprintf(stderr,"-- Syntax error at line %u : \"%s\"\n",lineNumber,line.c_str());
                    fin.close();
                    return false;
                }

                // if line starts with '#' it is a comment
                if (line[index] == '#')
                    continue;   //jump to next line
                
                // count every ';' in the line
                int count = 0;
                for (char c : line) if (c == ';') count ++;

                // line doesn't have 4 fields separated by delimiter ';'
                if (count != 3) {
                    fprintf(stderr,"-- Syntax error at line %u : \"%s\"\n",lineNumber,line.c_str());
                    fin.close();
                    return false;
                }  

                // split lines by delimiter ';'
                std::vector<std::string> fields;
                std::string field;
                std::istringstream stream(line);

                // store the fields
                while(std::getline(stream,field,';'))
                {
                    // if a field is empty e.g. "111;0;     ;0x200"
                    if (field.empty() or field.find_first_not_of(" \t\n\r\f\v") == std::string::npos)
                    {
                        fprintf(stderr,"-- Syntax error at line %u : \"%s\"\n",lineNumber,line.c_str());
                        fin.close();
                        return false;
                    }
                    fields.push_back(field);
                }

                // line doesnt have correct number of fields
                if (fields.size() != 4)
                {
                    fprintf(stderr,"-- Syntax error at line %u : \"%s\"\n",lineNumber,line.c_str());
                    fin.close();
                    return false;
                }

                // remove all whitespaces
                for(int i = 0; i < 4; i++)
                    fields[i].erase(remove(fields[i].begin(), fields[i].end(), ' '), fields[i].end());
                
                // try to convert every field to integer representation
                // if an error occurs syntax is wrong
                int32_t pid, arrivalTime, duration, addrSpaceSize;
                try
                {
                    pid = std::stoi(fields[0]);
                    arrivalTime = std::stoi(fields[1]);
                    duration = std::stoi(fields[2]);
                    addrSpaceSize = std::stoi(fields[3],0,16);
                }
                catch (const std::exception& e)
                {
                    fprintf(stderr,"-- Syntax error at line %u : \"%s\"\n",lineNumber,line.c_str());
                    fin.close();
                    return false;
                }
                
                // check if pid has already been processed
                if (std::find(pids.begin(), pids.end(), pid) != pids.end())
                {
                    fprintf(stderr,"-- Semantic error at line %u (pid %d is repeated): \"%s\"\n",lineNumber,pid,line.c_str());
                    fin.close();
                    return false;
                }
                if (pid <= 0)
                {
                    fprintf(stderr,"-- Semantic error at line %u (pid is %d): \"%s\"\n",lineNumber,pid,line.c_str());
                    fin.close();
                    return false;
                }
                if (arrivalTime < 0)
                {
                    fprintf(stderr,"-- Semantic error at line %u (arrival time is %d): \"%s\"\n",lineNumber,arrivalTime,line.c_str());
                    fin.close();
                    return false;
                }
                if (duration <= 0)
                {
                    fprintf(stderr,"-- Semantic error at line %u (duration is %d): \"%s\"\n",lineNumber,duration,line.c_str());
                    fin.close();
                    return false;
                }
                if (addrSpaceSize <= 0)
                {
                    fprintf(stderr,"-- Semantic error at line %u (address space size %d): \"%s\"\n",lineNumber,duration,line.c_str());
                    fin.close();
                    return false;
                }

                // add to list of processed pids
                pids.push_back(pid);
            }
            fin.close();
            return true;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
