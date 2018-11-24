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
    BuiltIn() {}
    BuiltIn(std::string c)
        : cmd(c)
    { split(); }

    ~BuiltIn() {}

    bool execute() override 
    {}

    void clearPathname() { pathname.clear(); }

protected:
    std::string cmd; // entire command
};

//==================================================
// Built in commands                               =
//==================================================

// built in command 'test'
struct Test
    : public BuiltIn
{
    Test(std::string c)
        : cmd(c)
    {}

    bool execute() override;
};

#endif
