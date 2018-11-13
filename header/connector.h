#ifndef CONNECTOR_H
#define CONNECTOR_H

// user includes
#include "command.h"

class Connector
    : public Command
{
public: 
    Connector(Command* left, Command* right);
    ~Connector();

    bool execute() override;

protected:
    std::string connectorValue;

    Command* lhs;
    Command* rhs;
};

#endif
