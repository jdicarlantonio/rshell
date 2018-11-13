#include "header/input.h"
#include "semicolon.h"
#include "and.h"
#include "or.h"
#include "executable.h"

Input::Input()
    : singleCommand("");
{}

Input::~Input()
{}

// this function does what you think it does
void Input::getInput()
{
    std::cout << "$ ";

    std::string currentInput;
    std::getline(std::cin, currentInput);

    tokenize(currentInput);
}

bool Input::run()
{
    if(argList[0] == "exit")
    {
        return false;
    }
    else
    {
        if(singleCommand)
        {
            // we should only have one executable object
            executables[0].execute();
        }
        else
        {
            // the last connector in the array should be the top of the tree
            int numConnectors = connectors.size();
            connectors[numConnectors - 1].execute();
        }
    }
}

// takes user input and puts them into tokens which are then differentiated between
// a connector and an executable with arguments
void Input::tokenize(std::string input)
{
    // get string into a char array
    char* charInput = new char[input.size() + 1];
    std::strcpy(charInput, input.c_str());
   
    // initially all tokens in the input 
    StringVec tokens;

    char* tokenStr;
    tokenStr = strtok(charInput, " ");
    while(tokenStr != NULL)
    {
        std::string tokenTemp(tokenStr);
        int endOfToken = tokenTemp.size();

        tokens.push_back(tokenTemp);

        // check for semi colon cancer
        if(tokenTemp[endOfToken - 1] == ';')
        {
            // remove semicolon from token and pop off the token that contained
            // the semicolon
            tokenTemp.pop_back();
            tokens.pop_back();

            // add the new token without semicolon and a seperate semicolon
            tokens.push_back(tokenTemp);
            tokens.push_back(";");
        }
    }

    // seperate commands and arguments from connectors
    StringVec argList;
    for(int i = 0; i < tokens.size(); ++i)    
    {
        // bassically push every token till we hit a connector
        argList.push_back(tokens[i]) 

        // remove connector from arglist, create an executable object, and store
        // the connector type, but don't create a connector object just yet
        if(tokens[i] == ";")
        {
            argList.pop_back();            
            executables.push_back(new Executable(argList));
            connectorValues.push_back(";");
        }
        if(tokens[i] == "||")
        {
            argList.pop_back();            
            executables.push_back(new Executable(argList));
            connectorValues.push_back("||");
        }
        if(tokens[i] == "&&")
        {
            argList.pop_back();            
            executables.push_back(new Executable(argList));
            connectorValues.push_back("&&");
        }
    }

    // if only a single command was entered, we should handle that differently
    if(connectors.size() < 1)
    {
        singleCommand = true;
    }
}

void Input::initializeCommands()
{
    // handle the initial connector first
    // this should only have two executables and no connectors as arguments
    if(connectorValues[0] == ";") 
    {
        connectors.push_back(
            new SemiColon(executables[0], executables[1])
        );
    }  
    if(connectorValues[0] == "||") 
    {
        connectors.push_back(
            new Or(executables[0], executables[1])
        );
    }  
    if(connectorValues[0] == "&&") 
    {
        connectors.push_back(
            new And(executables[0], executables[1])
        );
    }  
    
    // need to initialize a counter for the connectorvalues vector
    int j = 0;

    // this shouldn't run if there was only 1 connector
    for(int i = 2; i < executables.size() - 1; ++i) 
    {
        // if we have more than one connector, the lhs will always be a connector
        // and the rhs will always be an executable
        if(connectorValues[j] == ";") 
        {
            connectors.push_back(
                new SemiColon(connectors[j], executables[i])
            );
        }  
        if(connectorValues[j] == "||") 
        {
            connectors.push_back(
                new Or(connectors[j], executables[i])
            );
        }  
        if(connectorValues[j] == "&&") 
        {
            connectors.push_back(
                new And(connectors[j], executables[i])
            );
        }  
    }
}
