#include "../header/shell.h"

Shell::Shell()
    : running{false}
{
    userInput = new Input();
}

Shell::~Shell()
{
    delete userInput;
}

void Shell::initialize()
{
    running = true;
    while(running)
    {
        loop();
    }
}

void Shell::loop()
{
    userInput->getInput();
    running = userInput->run();
}
