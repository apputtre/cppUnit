#ifndef TEST10_H
#define TEST10_H

#include <vector>

#include "yUnit.h"

/*
Tests for confusion in macro expansion caused by commas being interpreted as delimiters for macro arguments,
even when they're in a template argument list.

This test fails if it doesn't compile.
*/
SUITE(templateArgList,
{
    TEST(test,
    {
        std::pair<int, int> p;
    })
})

#endif