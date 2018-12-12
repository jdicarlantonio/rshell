#ifndef PIPE_H
#define PIPE_H

#include "connector.h"

class Pipe
    : public Connector
{
public:
    Pipe();
    Pipe(Command* lhs, Command* rhs);
    ~Pipe();

    bool execute(int fdin, int fdout) override;
};

#endif
