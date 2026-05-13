#ifndef TESTDEFAULTSUITE_H
#define TESTDEFAULTSUITE_H

#include "TestEnvironment.h"

TestEnvironment testSuitelessTests()
{
    TestEnvironment tenv;

    tenv.beginTest("2+2=5?");
    tenv.assert(2 + 2 == 5, "Two plus two does not equal 5!");

    tenv.beginSuite("Suite");
    tenv.beginTest("War is Peace?");
    tenv.assert(std::string("War") == std::string("Peace"), "War is not Peace!");

    return tenv;
}

#endif