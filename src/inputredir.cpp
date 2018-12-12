#include "../header/inputredir.h"

#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

InputRedir::InputRedir(Command* lhs, Command* rhs)
    : Connector(lhs, rhs)
{}

InputRedir::InputRedir()
{}

InputRedir::~InputRedir()
{}

bool InputRedir::execute(int fdin, int fdout)
{
    std::string filepath;
    if(!rhs->getFilePath(filepath))     
    {
        std::cout << "expected file\n";
        return false;
    }

    fdin = open(filepath.c_str(), O_RDONLY);

    return lhs->execute(fdin, 1);
}
