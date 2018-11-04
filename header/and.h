#ifndef AND_H
#define AND_H

// user include
#include "connector.h"

class And
    : public Connector
{
public:
    And();
    ~And();

    void execute() override;
};

#endif
