/*
 * Source code for all built in functions 
 */

#include "../header/builtin.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//=========================================
// Test functions                         =
//=========================================

bool Test::execute()
{
    // split command into argument and pathname
    std::string pathname;
    char arg = 'e';
    
    if(cmd[0] == '-')
    {
        // if parsing went well, the argument should be at index [1]
        arg = cmd[1];
        
        // find first index of pathname, so we can ignore whitespace
        int index = 3;
        while(cmd[index] == ' ')
        {
            ++index;
        }

        pathname = cmd.substr(index, string::npos);
    }
    else
    {
        pathname = cmd;
    }

    struct stat buf;
    const char* c_pathname = pathname.cstr();

    switch(arg)
    {
        case 'e':
        {
            if(stat(c_pathname, &buf) == 0)
            {
                std::cout << "(true)\n";
                return true;
            }
            else
            {
                std::cout << "(false)\n";
                return false;
            }
        }
        case 'f':
        {
            if(stat(c_pathname, &buf) == 0)
            {
                if(S_ISREG(buf.st_mode)) 
                {
                    std::cout << "(true)\n";
                    return true;
                }
                else
                {
                    std::cout << "(false)\n";
                    return false;
                }
            }
            else
            {
                std::cout << "(false)\n";
                return false;
            }
        }
        case 'd':
        {
            if(stat(c_pathname, &buf) == 0)
            {
                if(S_ISDIR(buf.st_mode)) 
                {
                    std::cout << "(true)\n";
                    return true;
                }
                else
                {
                    std::cout << "(false)\n";
                    return false;
                }
            }
            else
            {
                std::cout << "(false)\n";
                return false;
            }
        }
        default: 
        {
            std::cout << "invalid argument\n";
            return false;
        }
    }
}
