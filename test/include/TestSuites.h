#ifndef TESTSUITES_H
#define TESTSUITES_H

#include <math.h>

#include "yUnit.h"

SUITE("First suite")
{
    TEST("cos(0)=1?")
    {
        assert(std::cos(0) == 1, "Cos(0) is not 1!");
    }

    TEST("2+2=5?")
    {
        assert(2 + 2 == 5, "Two plus two does not equal five!");
    }
}

SUITE("Second suite")
{
    TEST("True is true?")
    {
        assert(true, "True is not true!");
    }
}

SUITE("Third suite")
{
    TEST("War is Peace?")
    {
        assert(std::string("War") == std::string("Peace"), "War is not Peace!");
    }
}

TEST("Suiteless test")
{
    assert(false);
}

#endif