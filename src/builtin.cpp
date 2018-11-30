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
// test functions                         =
//=========================================

bool test::execute()
{
    // get argument and pathname
    // if no argument specified, default to -e
    char argument = 'e';
    std::string pathname;

    // check if no file
    if(argList.size() < 2)
    {
        // should always be false blank input is nothing and will never exist
        std::cout << "(false)\n";
        return false;
    }
    
    if(argList[1][0] == '-')
    {
        // check if user entered in invalid stuff
        if(argList[1].length() > 2)
        {
            std::cout << "Parsing error: invalid argument\n";
            return false;
        }
      
        // check if no file again
        if(argList.size() < 3)
        {
            std::cout << "(false)\n";
            return false;
        }
 
        argument = argList[1][1];
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
