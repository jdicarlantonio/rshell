#ifndef SHELL_H
#define SHELL_H

// user includes
#include "input.h"
#include "command.h"

class Shell
{
public:
    Shell();
    ~Shell();

    void initialize();
    
private: // private functions
    void loop();
    bool isExiting();

private: // private members
    enum State
    {
        IN_LOOP = 0,
        EXITING
    };

    State state;
    Input* userInput; 
    Command* cmd;
};

#endif
