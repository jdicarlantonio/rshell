#include "../header/or.h"

Or::Or()
{}

Or::Or(Command* left, Command* right)
    : Connector(left, right)
{
}

Or::~Or()
{}

bool Or::execute()
{
    return (lhs->execute() || rhs->execute());
}
