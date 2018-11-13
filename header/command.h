#ifndef COMMAND_H
#define COMMAND_H

class Command 
//    : public Input
{
public:
    Command() { }
    ~Command() { }

    virtual bool execute() = 0;
};

#endif
