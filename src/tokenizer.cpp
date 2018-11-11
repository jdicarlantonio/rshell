#include <iostream>
#include <string>
#include <cstring>
#include <vector>

void tokenize(std::string input)
{
    // get string into a char array
    char* charInput = new char[input.size() + 1];
    std::strcpy(charInput, input.c_str());

    std::vector<std::string> arguments;
    std::vector<std::string> connectors;

    char* tokenStr;
    tokenStr = strtok(charInput, " ");
    while(tokenStr != NULL)
    {
        std::string tokenTemp(tokenStr);
        int endOfString = tokenTemp.size();

        if(tokenTemp[endOfString - 1] == ';')
        {
            tokenTemp.pop_back();
            connectors.push_back(";");
        }

        if(tokenTemp == "||" || tokenTemp == "&&")
        {
            connectors.push_back(tokenTemp);
        }
        else
        {
            arguments.push_back(tokenTemp);
        }
        
        tokenStr = strtok(NULL, " ");
    }
    
    if(connectors.size() < 1)
    {
        std::string val = input;
        std::cout << val << '\n';
    }
}

int main()
{
    std::cout << "$ ";

    std::string currentInput;
    std::getline(std::cin, currentInput);

    tokenize(currentInput);

    return 0;
}
