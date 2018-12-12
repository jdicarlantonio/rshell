#include "../header/input.h"
#include "../header/semicolon.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/executable.h"
#include "../header/builtin.h"
#include "../header/command.h"
#include "../header/parenthesis.h"
#include "../header/pipe.h"
#include "../header/outputredir.h"
#include "../header/inputredir.h"
#include "../header/outputappend.h"

#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <csignal>

Input::Input()
    : singleCommand(false)
{}

Input::~Input()
{
    if(executables.size() > 0)
    {
        for(int i = 0; i < executables.size(); ++i)
        {
            delete executables[i];
        }
    }
    
    if(connectors.size() > 0)
    {
        for(int i = 0; i < connectors.size(); ++i)
        {
            delete connectors[i];
        }
    }
}

// this function does what you think it does
void Input::getInput()
{
    std::string userLog(getlogin());
    char hostname[256];
    gethostname(hostname, 256);
    
    std::cout << userLog << '@' << hostname << "$ ";

    std::string currentInput;
    std::getline(std::cin, currentInput);

    if(!splitParen(currentInput))
    {
        std::cout << "Error: expected ')'\n";
        return;
    }

    tokenize(currentInput);
}

bool Input::run()
{
    if(tokens.size() < 1)
    {
        return true; // we probably have a comment here, so just continue
    }

    if(tokens[0] == "exit")
    {   
        exit(0);
        return false;
    }
    else
    { 
        if(singleCommand)
        {
            // we should only have one executable object
            executables[0]->execute(0, 1);
            singleCommand = false; 
        }
        else
        {
            if(precedence)
            {
                constructPrecedence();
//                connectors.back()->execute();
            }
            else
            {
                initializeCommands();
                
                int numConnectors = connectors.size();
                connectors[numConnectors - 1]->execute(0, 1);
            }
        }

        tokens.clear();
        connectorValues.clear();
        connectors.clear();
        executables.clear();

        return true;
    }
}

// takes user input and puts them into tokens which are then differentiated between
// a connector and an executable with arguments
// this is one hell of a function and should probably be split up
void Input::tokenize(std::string input)
{
    // get string into a char array
    char* charInput = new char[input.size() + 1];
    std::strcpy(charInput, input.c_str());
  
    bool inParens = false;
 
    char* tokenStr;
    tokenStr = strtok(charInput, " ");
    while(tokenStr != NULL)
    {
        std::string tokenTemp(tokenStr);
        int endOfToken = tokenTemp.size();
        
        if(tokenTemp == "#" || tokenTemp[0] == '#')
        {
            break;
        }

        tokens.push_back(tokenTemp);
        // check for brackets, and if its an open bracket switch with "test"
        // remove close bracket
        if(tokenTemp == "[")
        {
            tokens.pop_back();
            tokens.push_back("test");
        }
        
        if(tokenTemp == "]")
        {
            tokens.pop_back();
        }

        // check for semi colon 
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
        
        tokenStr = strtok(NULL, " ");
    }

    if(tokens.size() < 1)
    {
        return;
    }
    
    // seperate commands and arguments from connectors
    StringVec argList;
    for(int i = 0; i < tokens.size(); ++i)    
    {
        // ignore parenthesis for now
        if(tokens[i] == "(" || tokens[i] == ")")
        {
            continue;
        }
        // remove connector from arglist, create an executable object, and store
        // the connector type, but don't create a connector object just yet
        if(tokens[i] == ";")
        {
            pushExecutable(argList);
            connectorValues.push_back(";");
            ++i;
            
            argList.clear();
        }
        if(tokens[i] == "||")
        {
            pushExecutable(argList);
            connectorValues.push_back("||");
            ++i;
            
            argList.clear();
        }
        if(tokens[i] == "&&")
        {
            pushExecutable(argList);
            connectorValues.push_back("&&");
            ++i;
            
            argList.clear();
        }
        if(tokens[i] == "|")
        {
            pushExecutable(argList);
            connectorValues.push_back("|");
            ++i;
            
            argList.clear();
        }
        if(tokens[i] == "<")
        {
            pushExecutable(argList);
            connectorValues.push_back("<");
            ++i;
            
            argList.clear();
        }
        if(tokens[i] == ">")
        {
            pushExecutable(argList);
            connectorValues.push_back(">");
            ++i;
            
            argList.clear();
        }
        if(tokens[i] == ">>")
        {
            pushExecutable(argList);
            connectorValues.push_back(">>");
            ++i;
            
            argList.clear();
        }
        
        argList.push_back(tokens[i]);
    }

    pushExecutable(argList);
//    executables.push_back(new Executable(argList));
 
    // if only a single command was entered, we should handle that differently
    if(connectorValues.size() < 1)
    {
        // not sure if im going to need some of this code or not
//        pushExecutable(argList);
//        executables.push_back(new Executable(argList));
        singleCommand = true;
    }
}

bool Input::splitParen(std::string& input)
{
    int openParenCount = 0, closedParenCount = 0;

    for(int i = 0; i < input.size(); ++i) 
    {
        if(input[i] == '(')
        {
            ++openParenCount;
            
            if(input[i + 1] != ' ')
            {
                input.insert(i + 1, " ");
            }
        }

        if(input[i] == ')')
        {
            ++closedParenCount;
           
            if(input[i - 1] != ' ')
            {
                input.insert(i, " ");
                ++i;
            }
        }
    }

    if(openParenCount > 0 && closedParenCount > 0)
    {
        if(openParenCount != closedParenCount)
        {
            precedence = false;
            return false; 
        }

        precedence = true;
        return true;
    }

    precedence = false;
    return true;
}

void Input::pushExecutable(StringVec& argList)
{
    if(argList[0] == "test")
    {
        executables.push_back(new test(argList));
    }
    else
    {
        executables.push_back(new Executable(argList));
    }
}

void Input::initializeCommands()
{
    // handle the initial connector first
    // this should only have two executables and no other connectors as arguments
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
    if(connectorValues[0] == "|")
    {
        connectors.push_back(
            new Pipe(executables[0], executables[1])
        );
    }
    if(connectorValues[0] == "<")
    {
        connectors.push_back(
            new InputRedir(executables[0], executables[1])
        );
    }
    if(connectorValues[0] == ">")
    {
        connectors.push_back(
            new OutputRedir(executables[0], executables[1])
        );
    }
    if(connectorValues[0] == ">>")
    {
        connectors.push_back(
            new OutputAppend(executables[0], executables[1])
        );
    }
    
    // need to initialize a counter for the connectorvalues vector
    int j = 1;

    // this shouldn't run if there was only 1 connector
    for(int i = 2; i < executables.size(); ++i) 
    {
        // if we have more than one connector, the lhs will always be a connector
        // and the rhs will always be an executable
        if(connectorValues[j] == ";") 
        {
            connectors.push_back(
                new SemiColon(connectors[j - 1], executables[i])
            );
        }  
        if(connectorValues[j] == "||") 
        {
            connectors.push_back(
                new Or(connectors[j - 1], executables[i])
            );
        }  
        if(connectorValues[j] == "&&") 
        {
            connectors.push_back(
                new And(connectors[j - 1], executables[i])
            );
        }  
        if(connectorValues[j] == "|")
        {
            connectors.push_back(
                new Pipe(connectors[j - 1], executables[i])
            );
        }
        if(connectorValues[j] == "<")
        {
            connectors.push_back(
                new InputRedir(connectors[j - 1], executables[i])
            );
        }
        if(connectorValues[j] == ">")
        {
            connectors.push_back(
                new OutputRedir(connectors[j - 1], executables[i])
            );
        }
        if(connectorValues[j] == ">>")
        {
            connectors.push_back(
                new OutputAppend(connectors[j - 1], executables[i])
            );
        }
        
        ++j;
    }
}

// this function is a beast and is probably bad
void Input::constructPrecedence()
{
    StringVec symbols; // keep track of connectors and parenthesis
    std::vector<Command*> cmd; // keep track of commands and arguments

    StringVec commands;
    for(int i = 0; i < tokens.size(); ++i)
    {
        if(tokens.at(i) == "(")
        {
            symbols.push_back("()");
        }

        if(tokens.at(i) != "||" && tokens.at(i) != "&&" && tokens.at(i) != ";" 
            && tokens.at(i) != "(" && tokens.at(i) != ")" && tokens.at(i) != ">"
            && tokens.at(i) != "<" && tokens.at(i) != ">>" && tokens.at(i) != "|")
        {
            commands.push_back(tokens.at(i));
        }

        if(tokens.at(i) == "||" || tokens.at(i) == "&&" || tokens.at(i) == ";"
            || tokens.at(i) == "<" || tokens.at(i) == ">" || tokens.at(i) == "|"
            || tokens.at(i) == ">>")
        {
            if(commands.size() > 0)
            {
                Executable* exec;
                if(commands[0] == "test")
                {
                    exec = new test(commands);
                }
                else
                { 
                    exec = new Executable(commands);
                }
                cmd.push_back(exec);       
                commands.clear();
            }
 
            if(symbols.empty() || symbols.back() == "()")
            {
                symbols.push_back(tokens[i]);
            }
            else
            {
                if(symbols.back() == "||")
                {
                    Command* rhs = cmd.back();
                    cmd.pop_back();

                    Command* lhs = cmd.back();
                    cmd.pop_back(); 
        
                    cmd.push_back(new Or(lhs, rhs));
                    symbols.pop_back();
                    symbols.push_back(tokens.at(i));
                }
                else if(symbols.back() == "&&")
                {
                    Command* rhs = cmd.back();
                    cmd.pop_back();

                    Command* lhs = cmd.back();
                    cmd.pop_back(); 
        
                    cmd.push_back(new And(lhs, rhs));
                    symbols.pop_back();
                    symbols.push_back(tokens.at(i));
                }
                else if(symbols.back() == ";")
                {
                    Command* rhs = cmd.back();
                    cmd.pop_back();

                    Command* lhs = cmd.back();
                    cmd.pop_back(); 
        
                    cmd.push_back(new SemiColon(lhs, rhs));
                    symbols.pop_back();
                    symbols.push_back(tokens.at(i));
                }
                else if(symbols.back() == "|")
                {
                    Command* rhs = cmd.back();
                    cmd.pop_back();

                    Command* lhs = cmd.back();
                    cmd.pop_back(); 
        
                    cmd.push_back(new Pipe(lhs, rhs));
                    symbols.pop_back();
                    symbols.push_back(tokens.at(i));
                }
                else if(symbols.back() == ">")
                {
                    Command* rhs = cmd.back();
                    cmd.pop_back();

                    Command* lhs = cmd.back();
                    cmd.pop_back(); 
        
                    cmd.push_back(new OutputRedir(lhs, rhs));
                    symbols.pop_back();
                    symbols.push_back(tokens.at(i));
                }
                else if(symbols.back() == "<")
                {
                    Command* rhs = cmd.back();
                    cmd.pop_back();

                    Command* lhs = cmd.back();
                    cmd.pop_back(); 
        
                    cmd.push_back(new InputRedir(lhs, rhs));
                    symbols.pop_back();
                    symbols.push_back(tokens.at(i));
                }
                else if(symbols.back() == ">>")
                {
                    Command* rhs = cmd.back();
                    cmd.pop_back();

                    Command* lhs = cmd.back();
                    cmd.pop_back(); 
        
                    cmd.push_back(new OutputAppend(lhs, rhs));
                    symbols.pop_back();
                    symbols.push_back(tokens.at(i));
                }
            }
        }

        if(tokens.at(i) == ")")
        {
            if(commands.size() > 0)
            {
                Executable* exec;
                if(commands[0] == "test")
                {
                    exec = new test(commands);
                }
                else
                {
                    exec = new Executable(commands);
                }
                cmd.push_back(exec);       
                commands.clear();
            }

            Command* rhs = cmd.back();
            cmd.pop_back();
            
            Command* lhs = cmd.back();
            cmd.pop_back();

            if(symbols.back() == "()")
            {
                symbols.pop_back();
                if(symbols.back() == "&&")
                {
                    cmd.push_back(new And(lhs, rhs));
                    symbols.pop_back();
                }
                else if(symbols.back() == "||")
                {
                    cmd.push_back(new Or(lhs, rhs));
                    symbols.pop_back();
                }
                else if(symbols.back() == ";")
                {
                    cmd.push_back(new SemiColon(lhs, rhs));
                    symbols.pop_back();
                }
                else if(symbols.back() == "<")
                {
                    cmd.push_back(new InputRedir(lhs, rhs));
                    symbols.pop_back();
                }
                else if(symbols.back() == ">")
                {
                    cmd.push_back(new OutputRedir(lhs, rhs));
                    symbols.pop_back();
                }
                else if(symbols.back() == ">>")
                {
                    cmd.push_back(new OutputAppend(lhs, rhs));
                    symbols.pop_back();
                }
                else if(symbols.back() == "|")
                {
                    cmd.push_back(new Pipe(lhs, rhs));
                    symbols.pop_back();
                }
            }
            else
            { 
                if(symbols.back() == "&&")
                {
                    cmd.push_back(new And(lhs, rhs));
                    symbols.pop_back();
                    symbols.pop_back();
                }
                else if(symbols.back() == "||")
                {
                    cmd.push_back(new Or(lhs, rhs));
                    symbols.pop_back();
                    symbols.pop_back();
                }
                else if(symbols.back() == ";")
                {
                    cmd.push_back(new SemiColon(lhs, rhs));
                    symbols.pop_back();
                    symbols.pop_back();
                }
                else if(symbols.back() == "<")
                {
                    cmd.push_back(new InputRedir(lhs, rhs));
                    symbols.pop_back();
                    symbols.pop_back();
                }
                else if(symbols.back() == ">")
                {
                    cmd.push_back(new OutputRedir(lhs, rhs));
                    symbols.pop_back();
                    symbols.pop_back();
                }
                else if(symbols.back() == ">>")
                {
                    cmd.push_back(new OutputAppend(lhs, rhs));
                    symbols.pop_back();
                    symbols.pop_back();
                }
                else if(symbols.back() == "|")
                {
                    cmd.push_back(new Pipe(lhs, rhs));
                    symbols.pop_back();
                    symbols.pop_back();
                }
            }
        }
    }

    if(cmd.size() > 1)
    {
        if(symbols.back() == "||") 
        {
            Command* rhs = cmd.back();
            cmd.pop_back();

            Command* lhs = cmd.back();
            cmd.pop_back();            

            Or* orExec = new Or(lhs, rhs);
            orExec->execute(0, 1);
        }
        if(symbols.back() == "&&") 
        {
            Command* rhs = cmd.back();
            cmd.pop_back();

            Command* lhs = cmd.back();
            cmd.pop_back();            

            And* andExec = new And(lhs, rhs);
            andExec->execute(0, 1);
        }
        if(symbols.back() == ";") 
        {
            Command* rhs = cmd.back();
            cmd.pop_back();

            Command* lhs = cmd.back();
            cmd.pop_back();            

            SemiColon* semiColon = new SemiColon(lhs, rhs);
            semiColon->execute(0, 1);
        }
        if(symbols.back() == "<") 
        {
            Command* rhs = cmd.back();
            cmd.pop_back();

            Command* lhs = cmd.back();
            cmd.pop_back();            

            InputRedir* inred = new InputRedir(lhs, rhs);
            inred->execute(0, 1);
        }
        if(symbols.back() == ">") 
        {
            Command* rhs = cmd.back();
            cmd.pop_back();

            Command* lhs = cmd.back();
            cmd.pop_back();            

            OutputRedir* outred = new OutputRedir(lhs, rhs);
            outred->execute(0, 1);
        }
        if(symbols.back() == ">>") 
        {
            Command* rhs = cmd.back();
            cmd.pop_back();

            Command* lhs = cmd.back();
            cmd.pop_back();            

            OutputAppend* outapp = new OutputAppend(lhs, rhs);
            outapp->execute(0, 1);
        }
        if(symbols.back() == "|") 
        {
            Command* rhs = cmd.back();
            cmd.pop_back();

            Command* lhs = cmd.back();
            cmd.pop_back();            

            Pipe* pipe = new Pipe(lhs, rhs);
            pipe->execute(0, 1);
        }
    }
    else
    {
        cmd.back()->execute(0, 1); 
    } 
}
