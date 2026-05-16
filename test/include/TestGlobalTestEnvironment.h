#ifndef TESTGLOBALTESTENVIRONMENT_H
#define TESTGLOBALTESTENVIRONMENT_H

#include "yUnit.h"

TEST("2+2=5?")
{
    assertEq(2+2, 5, "Two plus two does not equal five!");
}

BEGIN_SUITE("Test suite")
    TEST("War is Peace?")
    {
        assertEq(std::string("War"), std::string("Peace"), "War is not Peace!");
    }

    TEST("Freedom is Slavery?")
    {
        assertEq(std::string("Freedom"), std::string("Slavery"), "Freedom is not Slavery!");
    }
END_SUITE()

TEST("True is false?")
{
    assertEq(true, false, "True is not false!");
}

TestEnvironment testGlobalTestEnvironment()
{
    yUnit::impl::runTests();
    return yUnit::getGlobalTestEnvironment();
}

#endif