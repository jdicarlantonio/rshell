#include "../header/input.h"
#include "../header/semicolon.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/executable.h"

#include <iostream>
#include <cstring>

Input::Input()
    : singleCommand(false)
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
    if(tokens[0] == "exit")
    {
        return false;
    }
    else
    { 
        if(singleCommand)
        {
            // we should only have one executable object
            executables[0]->execute();
        }
        else
        {
            // the last connector in the array should be the top of the tree
            initializeCommands();
            int numConnectors = connectors.size();
            connectors[numConnectors - 1]->execute();
        }

        tokens.clear();
        connectorValues.clear();
        connectors.clear();
        executables.clear();
    }
    
    return true;
}

// takes user input and puts them into tokens which are then differentiated between
// a connector and an executable with arguments
void Input::tokenize(std::string input)
{
    // get string into a char array
    char* charInput = new char[input.size() + 1];
    std::strcpy(charInput, input.c_str());
   
    char* tokenStr;
    tokenStr = strtok(charInput, " ");
    int count = 0;
    while(tokenStr != NULL)
    {
        std::string tokenTemp(tokenStr);
        int endOfToken = tokenTemp.size();
    
        tokens.push_back(tokenStr);

        // check for semi colon cancer
        if(tokenTemp[endOfToken - 1] == ';')
        {
            // remove semicolon from token and pop off the token that contained
            // the semicolon
            tokenTemp.pop_back();
            tokens.pop_back();
            
            // add the new token without semicolon and a seperate semicolon
            tokens.push_back((char*)tokenTemp.c_str());
            tokens.push_back(";");
        }
        
        tokenStr = strtok(NULL, " ");
        ++count;
    }
    
    // seperate commands and arguments from connectors
    StringVec argList;
    for(int i = 0; i < tokens.size(); ++i)    
    {
        // remove connector from arglist, create an executable object, and store
        // the connector type, but don't create a connector object just yet
        std::cout << tokens[i]  << '\n';

        if(tokens[i] == ";")
        {
            executables.push_back(new Executable(argList));
            connectorValues.push_back(";");
            ++i;
        }
        if(tokens[i] == "||")
        {
            executables.push_back(new Executable(argList));
            connectorValues.push_back("||");
            ++i;
        }
        if(tokens[i] == "&&")
        {
            executables.push_back(new Executable(argList));
            connectorValues.push_back("&&");
            ++i;
        }
        
        argList.push_back(tokens[i]);
    }

    // if only a single command was entered, we should handle that differently
    if(connectorValues.size() < 1)
    {
        executables.push_back(new Executable(argList));
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
        
        ++j;
    }
}
