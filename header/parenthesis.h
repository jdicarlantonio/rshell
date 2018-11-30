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
        root->execute();
    } 

private:
    Connector* root;
};

#endif
