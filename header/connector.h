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

    bool execute(int fdin, int fdout) override;
    bool getFilePath(std::string& filepath) override
    {
        return false;
    }

protected:
    std::string connectorValue;

    Command* lhs;
    Command* rhs;
};

#endif
