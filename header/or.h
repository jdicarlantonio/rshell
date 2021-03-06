#ifndef OR_H
#define OR_H

// user include
#include "connector.h"

class Or
    : public Connector
{
public:
    Or();
    Or(Command* left, Command* right);
    ~Or();

    bool execute(int fdin, int fdout) override;
};

#endif
