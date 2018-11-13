#include "header/or.h"

Or::Or()
{}

Or::Or(Command* left, Command* right)
    : Connector(left, right)
{
}

Or::~Or()
{}

void Or::execute()
{
    if(!lhs->execute())
    {
        rhs->execute();
    }
}
