#include "../header/outputredir.h"

#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

OutputRedir::OutputRedir(Command* lhs, Command* rhs)
    : Connector(lhs, rhs)
{
}

OutputRedir::OutputRedir()
{}

OutputRedir::~OutputRedir()
{}

bool OutputRedir::execute(int fdin, int fdout)
{
    std::string filepath;
    if(!rhs->getFilePath(filepath))
    {
        std::cout << "expected file\n";
        return false;
    }

    fdout = open(
        filepath.c_str(), 
        O_WRONLY | O_TRUNC | O_CREAT,
        S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR
    );

    return lhs->execute(0, fdout);
}
