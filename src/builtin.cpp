/*
 * Source code for all built in functions 
 */

// user includes
#include "../header/builtin.h"

// std library
#include <iostream>

// system
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//=========================================
// Test functions                         =
//=========================================

bool Test::execute()
{
    // get argument and pathname
    // if no argument specified, default to -e
    char argument = 'e';
    std::string pathname;

    if(argList[1][0] == '-')
    {
        if(argList[1].length() > 2)
        {
            std::cout << "Parsing error: invalid argument";
            return false;
        }
       
        if(argList[1][1] == 'e' || argList[1][1] == 'd' || argList[1][1] == 'f') 
        {
            argument = argList[1][1];
        }
        else
        {
            std::cout << "Parsing error: invalid argument";
            return false;
        }
        pathname = argList[2];
    }
    else
    {
        pathname = argList[1];
    }

    struct stat buf;
    const char* c_pathname = pathname.c_str();

    switch(argument)
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
