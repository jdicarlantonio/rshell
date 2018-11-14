#include "../header/semicolon.h"

SemiColon::SemiColon()
{}

SemiColon::SemiColon(Command* left, Command* right)
    : Connector(left, right)
{
}

SemiColon::~SemiColon()
{}

bool SemiColon::execute()
{
    lhs->execute();
    return rhs->execute();
}
