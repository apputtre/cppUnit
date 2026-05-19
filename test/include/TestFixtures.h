#ifndef TESTFIXTURES_H
#define TESTFIXTURES_H

#include "yUnit.h"

FIXTURE()
{
    std::string log;

    SETUP()
    {
        log += "setUp() ";
    }

    TEARDOWN()
    {
        log += "tearDown() ";
    }

    FTEST("First test")
    {
        assertEq(2+2, 5, "Two plus two does not equal five!");

        log += "test_1 ";
    }

    FTEST("Second test")
    {
        assertEq(log, "setUp() test_1 tearDown() ", "Log is not correct!");
    }
}

#endif