#ifndef EXECUTABLE_H
#define EXECUTABLE_H

// user includes
#include "command.h"

class Executable
    : public Command
{
public:
    Executable();
    ~Executable();

    void execute() override;

private:
    std::string argList; // this may end up being a char array
    std::string filename; // this might actually just go into argList 
};

#endif
