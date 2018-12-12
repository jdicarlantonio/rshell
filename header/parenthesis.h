#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "command.h"
#include "connector.h"

class Parenthesis
    : public Command
{
public:
    Parenthesis(Connector* c)
        : root(c)
    {}
    ~Parenthesis()
    { 
//        delete root; 
    }

    bool execute()
    {
        root->execute(0, 0);
    } 

private:
    Connector* root;
};

#endif
