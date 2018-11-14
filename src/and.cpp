#include "../header/and.h"

And::And()
{}

And::And(Command* left, Command* right)
    : Connector(left, right)
{
}

And::~And()
{}

bool And::execute()
{
    return (lhs->execute() && rhs->execute());
}
