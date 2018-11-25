#ifndef EXECUTABLE_H
#define EXECUTABLE_H

// user includes
#include "command.h"

// std lib
#include <vector>
#include <string>

using StringVec = std::vector<std::string>;

class Executable
    : public Command
{
public:
    Executable(StringVec args);
    ~Executable();

    bool execute() override;

protected:
    StringVec argList; // this may end up being a char array
                       // is actually a char* vector now
                       // and its back to a string vector

private:
    bool executeSuccess;
};

#endif
