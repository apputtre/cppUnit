#include "yUnit.h"

struct TestRegistrar
{
    template<std::derived_from<TestEnvironment> TSubclass>
    TestRegistrar(TSubclass& tenv, void(TSubclass::*test)())
    {
        tenv.registerTest(test);
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

        TestRegistrar r(tenv, TestEnvironmentSubclass::test);
        tenv.runTests();

        assert(tenv.ran, "\'run\' flag was not set!");
        assertEq(tenv.log, std::string("setUp test tearDown "));
    })
})