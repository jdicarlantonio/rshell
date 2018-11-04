#ifndef CONNECTOR_H
#define CONNECTOR_H

// user includes
#include "command.h"

class Connector
    : public Command
{
public: 
    Connector();
    ~Connector();

    void execute() override;

protected:
    Command* lhs;
    Command* rhs;
};

#endif
