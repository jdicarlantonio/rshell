#ifndef INPUT_H
#define INPUT_H

// std library
#include <map>
#include <string>

using TokenMap = std::map<std::string, std::string>

class Input
{
public:
    Input();
    ~Input();

    std::string getInput();

private:
    void tokenize();

protected:
    TokenMap tokens;

};

#endif
