#ifndef TESTGLOBALGETSUMMARY_H
#define TESTGLOBALGETSUMMARY_H

#include "testutils.h"
#include "yUnit.h"

class TestEnvironmentSubclass3 : public TestEnvironment
{
public:
    void test()
    {
        beginTest("2+2=5?");
        assertEq(2+2, 5, "Two plus two does not equal five!");
    }
};

std::string testGlobalGetSummary()
{
    std::unique_ptr<TestEnvironmentSubclass3> p = std::make_unique<TestEnvironmentSubclass3>();

    p->addTest(TestEnvironmentSubclass3::test);
    yUnit::impl::registerTestEnvironment(p);

    return yUnit::getSummary();
}

#endif