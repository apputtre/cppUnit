#ifndef TEST9_H
#define TEST9_H

#include "TestEnvironment.h"
#include "TestSuite.h"

class TestSuiteTest : public TestSuite 
{
public:
    TestSuiteTest(const std::string& name) : TestSuite(name)
    {}
};

TestEnvironment Test9()
{
    TestEnvironment tenv;

    TestSuiteTest test("Test suite class");

    // test.run(tenv);

    return tenv;
}

#endif