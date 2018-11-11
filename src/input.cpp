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

    }
}

void Input::tokenize(std::string input)
{
    // get string into a char array
    char* charInput = new char[input.size() + 1];
    std::strcpy(charInput, input.c_str());
    
    StringVec tokens;

    char* tokenStr;
    tokenStr = strtok(charInput, " ");
    while(tokenStr != NULL)
    {
        std::string tokenTemp(tokenStr);
        int endOfToken = tokenTemp.size();

        tokens.push_back(tokenTemp);

        if(tokenTemp[endOfToken - 1] == ';')
        {
            tokenTemp.pop_back();
            tokens.pop_back();

            tokens.push_back(tokenTemp);
            tokens.push_back(";");
        }
    }

    // seperate commands and arguments from connectors
    StringVec argList;
    for(int i = 0; i < tokens.size(); ++i)    
    {
        argList.push_back(tokens[i]) 

        if(tokens[i] == ";")
        {
            argList.pop_back();            
            connectors.push_back(new SemiColon());
            executables.push_back(new Executable(argList));
            argList.clear();
        }
        if(tokens[i] == "||")
        {
            argList.pop_back();            
            connectors.push_back(new Or());
            executables.push_back(new Executable(argList));
            argList.clear();
        }
        if(tokens[i] == "&&")
        {
            argList.pop_back();            
            connectors.push_back(new And());
            executables.push_back(new Executable(argList));
            argList.clear();
        }
    }

    if(argList > 0)
    {
        executables.push_back(new Executable(argList));
    }

    if(connectors.size() < 1)
    {
        singleCommand = true;
    }
}

void Input::initializeCommands()
{
}
