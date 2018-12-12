#ifndef AND_H
#define AND_H

// user include
#include "connector.h"

class And
    : public Connector
{
public:
    And();
    And(Command* left, Command* right);
    ~And();

    bool execute(int fdin, int fdout) override;
};

#endif
