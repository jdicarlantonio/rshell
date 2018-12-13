#ifndef INPUT_H
#define INPUT_H

// std library
#include <string>

// user includes
#include "connector.h"
#include "executable.h"
#include "command.h"

using StringVec = std::vector<std::string>;

class Input
{
public:
    Input();
    ~Input();

    void getInput();
    bool run(); // runs the command as per input
    void tokenize(std::string input);
    // seperate parenthesis from input returns false if closing parens don't match
    // the opening parens
    bool splitParen(std::string& input); 

    StringVec getTokens() { return tokens; }

private:
    void pushExecutable(StringVec& argList);
    void initializeCommands();
    void constructPrecedence();

    StringVec tokens;
    StringVec connectorValues;

    bool singleCommand;
    bool precedence = false;
    bool emptyParen = false;
    
    std::vector<Connector*> connectors;
    std::vector<Executable*> executables;
};

#endif
