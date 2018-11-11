#ifndef EXECUTABLE_H
#define EXECUTABLE_H

// user includes
#include "command.h"

using StringVec = std::vector<char*>;

class Executable
    : public Command
{
public:
    Executable(StringVec args);
    ~Executable();

    void execute() override;

private:
    StringVec argList; // this may end up being a char array
    std::string cmd;
};

#endif
