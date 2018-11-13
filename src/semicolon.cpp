#include "header/and.h"

SemiColon::SemiColon()
{}

SemiColon::SemiColon(Command* left, Command* right)
    : Connector(left, right)
{
}

SemiColon::~SemiColon()
{}

void SemiColon::execute()
{
}
