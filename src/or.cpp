#include "../header/or.h"

Or::Or()
{}

Or::Or(Command* left, Command* right)
    : Connector(left, right)
{
}

Or::~Or()
{}

bool Or::execute(int fdin, int fdout)
{
    return (lhs->execute(fdin, fdout) || rhs->execute(fdin, fdout));
}
