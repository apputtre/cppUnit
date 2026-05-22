#ifndef TESTBASICASSERTIONS_H
#define TESTBASICASSERTIONS_H

#include "cppUnit.h"

TEST("Basic assertions")
{
    assert(2 + 2 == 5, "Two plus two does not equal 5!");
    assert(3*3 + 4*4 == 5*5, "3^2 + 4^2 does not equal 5^2!");
    assert(std::string("War") == std::string("Peace"), "War is not Peace!");
}

#endif