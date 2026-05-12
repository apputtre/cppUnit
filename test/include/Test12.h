#include "yUnit.h"

class TestEnvironmentSubclass : public TestEnvironment
{
private:
    std::vector<void(TestEnvironmentSubclass::*)()> tests;

public:
    TestEnvironmentSubclass()
    {
        tests.push_back(test);
    }

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
        for (auto t : tests)
        {
            setUp();
            (this->*t)();
            tearDown();
        }

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

        assert(!tenv.ran, "\'ran\' flag was true before running test!");
        assertEq(tenv.log, std::string(""), "Log is not empty before running test!");

        tenv.run();

        assert(tenv.ran, "\'run\' flag was not set!");
        assertEq(tenv.log, std::string("setUp tearDown run "));
    })
})