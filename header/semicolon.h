#ifndef SEMICOLON_H
#define SEMICOLON_H

// user include
#include "connector.h"

class SemiColon
    : public Connector
{
public:
    SemiColon();
    ~SemiColon();

    void execute() override;
};

#endif
