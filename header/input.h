#ifndef INPUT_H
#define INPUT_H

// std library
#include <map>
#include <string>

// user includes
#include "connector.h"
#include "executable.h"

using StringVec = std::vector<char*>;

class Input
{
public:
    Input();
    ~Input();

    void getInput();
    bool run(); // runs the command as per input

private:
    void tokenize(std::string input);
    void initializeCommands();

protected:
    StringVec tokens;
    StringVec connectorValues;

    bool singleCommand;
    
    std::vector<Connector*> connectors;
    std::vector<Executable*> executables;
};

#endif
