#ifndef EXECUTABLE_H
#define EXECUTABLE_H

// user includes
#include "command.h"

// std lib
#include <vector>

using StringVec = std::vector<char*>;

class Executable
    : public Command
{
public:
    Executable(StringVec args);
    ~Executable();

    bool execute() override;

private:
    StringVec argList; // this may end up being a char array
                       // is actually a char* vector now
};

#endif
