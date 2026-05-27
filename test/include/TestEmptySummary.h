#ifndef TESTEMPTYSUMMARY_H
#define TESTEMPTYSUMMARY_H

#include <math.h>

#include "cppUnit.h"

// If there are no failing tests, then the summary should be empty.

SUITE("First suite")
{
    TEST("cos(0)=1?")
    {
        assert(std::cos(0) == 1, "Cos(0) is not 1!");
    }

    TEST("2+2=5?")
    {
        assert(2 + 2 == 4, "Two plus two does not equal four!");
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
        assertNeq(std::string("War"), std::string("Peace"), "War is Peace!");
    }
}

TEST("Suiteless test")
{
    assert(true);
}

#endif