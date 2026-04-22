#ifndef TEST6_H
#define TEST6_H

#include "TestEnvironment.h"

TestEnvironment Test6()
{
    TestEnvironment tenv;

    tenv.beginTest("2+2=5?");
    tenv.assert(2 + 2 == 5, "Two plus two does not equal 5!");

    tenv.beginTest("3^2+4^2=5^2?");
    tenv.assert(3*3 + 4*4 == 5*5, "3^2 + 4^2 does not equal 5^2!");

    tenv.beginTest("War is Peace?");
    tenv.assert(std::string("War") == std::string("Peace"), "War is not Peace!");

    return tenv;
}

#endif