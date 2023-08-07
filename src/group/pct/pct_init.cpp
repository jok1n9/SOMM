/*
 *  \author ...
 */

#include "somm22.h"
#include "pct_module.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void pctInit(const char *fname) 
        {
            soProbe(201, "%s(\"%s\")\n", __func__, fname);
            
            uint32_t pid, arrivalTime, duration, addrSpaceSize;

            std::ifstream fin(fname);
            std::string line;
            while(getline(fin,line))
            {
                // ignore line if it has a comment or is empty
                if (line.empty() or line.find_first_not_of(" \t\n\r\f\v") == std::string::npos or line.find('#') != std::string::npos)
                    continue;

                // split lines by delimiter ';'
                std::vector<std::string> words;
                std::string word;
                std::istringstream stream(line);
                while(std::getline(stream,word,';'))
                    words.push_back(word);
                
                // ignore lines that don't have the correct format
                if (words.size() != 4)
                    continue;

                // remove all whitespaces
                for(int i = 0; i < 4; i++)
                    words[i].erase(remove(words[i].begin(), words[i].end(), ' '), words[i].end());
                
                pid = std::stoi(words[0]);
                arrivalTime = std::stoi(words[1]);
                duration = std::stoi(words[2]);
                addrSpaceSize = std::stoi(words[3],0,16);
                
                pctInsert(pid,arrivalTime,duration,addrSpaceSize);
            }
            fin.close();
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

