#include "header/connector.h"

Connector::Connector(Command* left, Command* right)
    : lhs(left)
    , rhs(right)
{}

Connector::~Connector()
{}

void Connector::execute()
{

}
