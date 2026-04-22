#ifndef TEST8_H
#define TEST8_H

#include "TestEnvironment.h"

TestEnvironment Test8()
{
    TestEnvironment tenv;

    tenv.beginSuite("endSuite()");

    tenv.beginTest("War is Peace?");
    tenv.assertEq(std::string("War"), std::string("Peace"), "War is not peace!");

    tenv.endSuite();

    tenv.beginTest("2+2=5?");
    tenv.assertEq(2+2, 5, "Two plus two does not equal five!");

    return tenv;
}

#endif