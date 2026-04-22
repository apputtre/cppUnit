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

    auto test_case = [](TestEnvironment& tenv){ tenv.beginTest(); tenv.assertEq(2+2, 5); tenv.endTest(); };

    test.registerTest(test_case);

    test.run(tenv);

    return tenv;
}

#endif