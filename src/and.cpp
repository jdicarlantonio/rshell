#include "../header/and.h"

#include <iostream>

And::And()
{}

And::And(Command* left, Command* right)
    : Connector(left, right)
{
}

And::~And()
{}

bool And::execute(int fdin, int fdout)
{
    return (lhs->execute(fdin, fdout) && rhs->execute(fdin, fdout));
}
