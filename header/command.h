#ifndef COMMAND_H
#define COMMAND_H

#include <string>

// base class
class Command 
{
public:
    Command() { }
    ~Command() { }
    
    // fdin is the file descriptor coming from left command
    // fdout is the file descriptor of the current command
    virtual bool execute(int fdin, int fdout) = 0;
    virtual bool getFilePath(std::string& filepath) = 0;
};

#endif
