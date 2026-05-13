#ifndef TESTENDTEST_H
#define TESTENDTEST_H

#include "TestEnvironment.h"

TestEnvironment testEndTest()
{
    TestEnvironment tenv;

    tenv.beginSuite("endTest()");

    tenv.beginTest("War is Peace?");
    tenv.assertEq(std::string("War"), std::string("Peace"), "War is not peace!");

    tenv.endTest();

    tenv.assertEq(2+2, 5, "Two plus two does not equal five!");

    return tenv;
}

#endif