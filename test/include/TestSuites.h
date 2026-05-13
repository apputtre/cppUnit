#ifndef TESTSUITES_H
#define TESTSUITES_H

#include <math.h>

#include "TestEnvironment.h"

TestEnvironment testSuites()
{
    TestEnvironment tenv;

    tenv.beginSuite("First suite");

    tenv.beginTest("3^2+4^2=5^2?");
    tenv.assert(3*3 + 4*4 == 5*5, "3^2 + 4^2 does not equal 5^2!");

    tenv.beginTest("sin(pi)=1?");
    tenv.assert(std::cos(0) == 1, "Cos(0) is not 1!");

    tenv.beginTest("2+2=5?");
    tenv.assert(2 + 2 == 5, "Two plus two does not equal five!");

    tenv.beginSuite("Second suite");

    tenv.beginTest("true?");
    tenv.assert(true, "True is false!");

    tenv.beginTest("1=1?");
    tenv.assert(1 == 1, "One does not equal one!");

    tenv.beginSuite("Third suite");

    tenv.beginTest("Assertion without message");
    tenv.assert(false);

    tenv.beginTest("War is peace?");
    tenv.assert(std::string("War") == std::string("Peace"), "War is not Peace!");

    return tenv;
}

#endif