#ifndef COMMAND_H
#define COMMAND_H

// user includes
#include "input.h"

class Command 
    : public Input
{
public:
    Command() { }
    ~Command() { }

    virtual void execute() = 0;
};

#endif
