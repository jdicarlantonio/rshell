#ifndef INPUTREDIR_H
#define INPUTREDIR_H

#include "connector.h"

class InputRedir
    : public Connector
{
public:
    InputRedir(Command* lhs, Command* rhs);
    InputRedir();
    ~InputRedir();

    bool execute(int fdin, int fdout) override;
};

#endif
