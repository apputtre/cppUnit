#ifndef TESTCOMBINEREPORTS_H
#define TESTCOMBINEREPORTS_H

#include "yUnit.h"

TestEnvironment testCombineReports()
{
    TestEnvironment tenv1;
    TestEnvironment tenv2;

    tenv1.beginSuite("Suite 1");
    tenv1.beginTest("2+2=5?");
    tenv1.assertEq(2+2, 5, "Two plus two does not equal five!");
    tenv1.endTest();

    tenv2.beginTest("War is Peace?");
    tenv2.assertEq(std::string("War"), std::string("Peace"), "War is not Peace!");

    tenv2.combineReports(tenv1);

    return tenv2;
}

#endif
