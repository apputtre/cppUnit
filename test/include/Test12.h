#include "yUnit.h"

struct TestRunner
{
    template<std::derived_from<TestEnvironment> T_TestEnvironment>
    TestRunner(T_TestEnvironment& tenv, void(T_TestEnvironment::*test_func)())
    {
        tenv.setUp();
        (tenv.*test_func)();
        tenv.tearDown();
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

SUITE(registerTest,
{
    TEST(test1,
    {
        TestEnvironmentSubclass tenv;

        assert(!tenv.ran, "\'ran\' flag was true before running test!");
        assertEq(tenv.log, std::string(""), "Log is not empty before running test!");

        TestRunner trun(tenv, tenv.test);

        assert(tenv.ran, "\'run\' flag was not set!");
        assertEq(tenv.log, std::string("setUp test tearDown "));
    })
})