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

private: // private members
    bool running;    

    Input* userInput; 
};

#endif
