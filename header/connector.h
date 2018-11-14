#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>

// user includes
#include "command.h"

class Command;

class Connector
    : public Command
{
public: 
    Connector();
    Connector(Command* left, Command* right);
    ~Connector();

    bool execute() override;

protected:
    std::string connectorValue;

    Command* lhs;
    Command* rhs;
};

#endif
