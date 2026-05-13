#ifndef TESTREGISTERTEST_H
#define TESTREGISTERTEST_H

#include "yUnit.h"

struct TestRegistrar
{
    template<std::derived_from<TestEnvironment> TSubclass>
    TestRegistrar(TSubclass& tenv, void(TSubclass::*test)())
    {
        tenv.addTest(test);
    }
};

class TestEnvironmentSubclass : public TestEnvironment
{
public:
    std::string log;

    bool ran = false;

    void setUp()
    {
        log += "setUp ";

        TestEnvironment::setUp();
    }

    void tearDown()
    {
        log += "tearDown ";

        TestEnvironment::tearDown();
    }

    void test()
    {
        ran = true;

        log += "test ";
    }
};

TestEnvironment testRunTest()
{
    TestEnvironmentSubclass tenv;

    tenv.assert(!tenv.ran, "\'ran\' flag was true before running test!");
    tenv.assertEq(tenv.log, std::string(""), "Log is not empty before running test!");

    TestRegistrar r(tenv, TestEnvironmentSubclass::test);
    tenv.runTests();

    tenv.assert(tenv.ran, "\'run\' flag was not set!");
    tenv.assertEq(tenv.log, std::string("setUp test tearDown "));

    return tenv;
}

#endif