#ifndef COMMAND_H
#define COMMAND_H

// base class
class Command 
{
public:
    Command() { }
    ~Command() { }

    virtual bool execute() = 0;
};

#endif
