#include "header/and.h"

And::And()
{}

And::And(Command* left, Command* right)
    : Connector(left, right)
{
}

And::~And()
{}

void And::execute()
{

}
