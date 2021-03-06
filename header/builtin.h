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

    virtual bool execute(int fdin, int fdout) override {}
    bool getFilePath(std::string& filepath) override
    {
        return false;
    }
};

//==================================================
// Built in commands                               =
//==================================================

// built in command 'test'
struct test
    : public BuiltIn
{
    test(std::vector<std::string> argList)
        : BuiltIn(argList)
    {}
    ~test() {}

    bool execute(int fdin, int fdout) override;
};

#endif
