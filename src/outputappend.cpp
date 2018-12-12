#include "../header/outputappend.h"

#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

OutputAppend::OutputAppend(Command* lhs, Command* rhs)
    : Connector(lhs, rhs)
{}

OutputAppend::OutputAppend()
{}

OutputAppend::~OutputAppend()
{}

bool OutputAppend::execute(int fdin, int fdout)
{
    std::string filepath;
    if(!rhs->getFilePath(filepath))
    {
        std::cout << "expected file\n";
        return false;
    }

    fdout = open(
        filepath.c_str(), 
        O_WRONLY | O_APPEND | O_CREAT,
        S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR
    );

    return lhs->execute(0, fdout);
}
