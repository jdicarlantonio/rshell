#include "../header/pipe.h"

#include <unistd.h>

Pipe::Pipe()
{}

Pipe::Pipe(Command* lhs, Command* rhs)
    : Connector(lhs, rhs)
{}

Pipe::~Pipe()
{}

bool Pipe::execute(int fdin, int fdout)
{
    int fds[2];

    if(pipe(fds) == -1)
    {
        perror("error piping");
        return false;
    }

    if(!lhs->execute(fdin, fds[1]))
    {
        return false;
    }

    close(fds[1]);

    if(!rhs->execute(fds[0], fdout))
    {
        return false;
    }

    close(fds[0]);
    return true; 
}
