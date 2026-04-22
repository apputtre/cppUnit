#ifndef TEST7_H
#define TEST7_H

#include "TestEnvironment.h"

TestEnvironment Test7()
{
    TestEnvironment tenv;

    tenv.beginSuite("endTest()");

    tenv.beginTest("War is peace?");
    tenv.assertEq(std::string("War"), std::string("Peace"), "War is not Peace!");

    tenv.endTest();

    tenv.assert("2+2=5?");
    tenv.assertEq(2+2, 5, "Two plus two does not equal five!");

    return tenv;
}

#endif