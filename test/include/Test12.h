#include "yUnit.h"

class TestEnvironmentSubclass : public TestEnvironment
{
public:
    std::string log;

    bool ran = false;

    void setUp()
    {
        log += "setUp ";
    }
    void tearDown()
    {
        log += "tearDown ";
    }

    void run()
    {
        setUp();
        test();
        tearDown();

        log += "run ";
    }

    void test()
    {
        ran = true;       
    }
};

SUITE(registerTest,
{
    TEST(test1,
    {
        TestEnvironmentSubclass tenv;

        tenv.registerTest(TestEnvironmentSubclass::test);

        assert(!tenv.ran, "\'ran\' flag was true before running test!");
        assertEq(tenv.log, std::string(""), "Log is not empty before running test!");

        tenv.run();

        assert(tenv.ran, "\'run\' flag was not set!");
        assertEq(tenv.log, std::string("setUp tearDown run "));
    })
})