#ifndef SEMICOLON_H
#define SEMICOLON_H

// user include
#include "connector.h"

class SemiColon
    : public Connector
{
public:
    SemiColon();
    SemiColon(Command* left, Command* right);
    ~SemiColon();

    bool execute() override;
};

#endif
