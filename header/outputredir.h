#ifndef OUTPUTREDIR_H
#define OUTPUTREDIR_H

#include "connector.h"

class OutputRedir
    : public Connector
{
public:
    OutputRedir(Command* lhs, Command* rhs);
    OutputRedir();
    ~OutputRedir();

    bool execute(int fdin, int fdout) override;
};

#endif
