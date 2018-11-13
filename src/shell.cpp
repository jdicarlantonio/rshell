#include "header/shell.h"

Shell::Shell()
{
    userInput = new Input();
}

Shell::~Shell()
{
    delete userInput;
}

void Shell::initialize()
{
    while(isExiting())
    {
        loop();
    }
}

void Shell::loop()
{
    switch(state)
    {
        case IN_LOOP:
        {
            userInput.getInput();
        }
        case EXITING:
        {
            state = EXITING;
        }
        default:
        {

        }
    }
}

bool Shell::isExiting()
{
    if(state == EXITING)
    {
        return true;
    }

    return false;
}
