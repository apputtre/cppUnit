#ifndef TESTFIXTURES_H
#define TESTFIXTURES_H

#include "cppUnit.h"

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
        log += "test_1 ";

        assertEq(2+2, 5, "Two plus two does not equal five!");

    }

    FTEST("Second test")
    {
        log += "test_2 ";

        // teardown for this test hasn't been called yet
        assertEq(log, "setUp() test_1 tearDown() setUp() test_2 ", "Log is not correct!");
    }
}

#endif