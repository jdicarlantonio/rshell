#include "../header/semicolon.h"

SemiColon::SemiColon()
{}

SemiColon::SemiColon(Command* left, Command* right)
    : Connector(left, right)
{
}

SemiColon::~SemiColon()
{}

bool SemiColon::execute(int fdin, int fdout)
{
    lhs->execute(fdin, fdout);
    return rhs->execute(fdin, fdout);
}
