#include "../header/connector.h"

Connector::Connector()
{}

Connector::Connector(Command* left, Command* right)
    : lhs(left)
    , rhs(right)
{}

Connector::~Connector()
{}

bool Connector::execute()
{

}
