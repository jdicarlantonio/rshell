#ifndef OUTPUTAPPEND_H
#define OUTPUTAPPEND_H

#include "connector.h"

class OutputAppend
    : public Connector
{
public:
    OutputAppend();
    OutputAppend(Command* lhs, Command* rhs);
    ~OutputAppend();

    bool execute(int fdin, int fdout) override;
};

#endif
