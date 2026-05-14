#ifndef TESTGLOBALTESTENVIRONMENT_H
#define TESTGLOBALTESTENVIRONMENT_H

#include "yUnit.h"

class TestEnvironmentSubclass2 : public TestEnvironment
{
public:
    void setUp() {}

    void tearDown() {}

    void test()
    {
        beginTest("2+2=5?");
        assertEq(2+2, 5, "Two plus two does not equal five!");
    }
};

TestEnvironment testGlobalTestEnvironment()
{
    yUnit::impl::clearTests();

    std::unique_ptr<TestEnvironmentSubclass2> p_s = std::make_unique<TestEnvironmentSubclass2>();
    p_s->addTest(TestEnvironmentSubclass2::test);

    yUnit::impl::registerTestEnvironment(p_s);
    yUnit::impl::runTests();

    return yUnit::getGlobalTestEnvironment();
}

#endif