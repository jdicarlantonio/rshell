#ifndef BUILTIN_H
#define BUILTIN_H

#include "executable.h"

#include <string>

/*
 * Base BuiltIn class for all built in commands
 */

class BuiltIn
    : public Executable
{
public:
    BuiltIn(std::vector<std::string> argList)
        : Executable(argList)
    {}
    ~BuiltIn() {}

    virtual bool execute() override {}
/*
protected:
    std::vector<std::string> args; // entire command
*/
};

//==================================================
// Built in commands                               =
//==================================================

// built in command 'test'
struct Test
    : public BuiltIn
{
    Test(std::vector<std::string> argList)
        : BuiltIn(argList)
    {}
    ~Test() {}

    bool execute() override;
};

#endif
