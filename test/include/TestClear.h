#ifndef TESTCLEAR_H
#define TESTCLEAR_H

#include "TestEnvironment.h"

TestEnvironment testClear()
{
    TestEnvironment tenv;

    tenv.beginTest("2+2=5?");
    tenv.assertEq(2+2, 5, "Two plus two does not equal five!");

    tenv.clear();

    return tenv;
}

#endif