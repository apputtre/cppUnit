#ifndef TEST9_H
#define TEST9_H

#include <vector>

#include "TestEnvironment.h"
#include "TestSuite.h"

TestEnvironment tenv;

#define SUITE(suite_name, tests)\
class TestSuite_##suite_name : public TestEnvironment\
{\
public:\
    TestSuite_##suite_name()\
    {\
        beginSuite(#suite_name);\
        tests\
        endSuite();\
    }\
};\

#define TEST(test_name, statements)\
    beginTest(#test_name);\
    statements\
    endTest();\

SUITE(testTestSuite,
{
    TEST(firstTest,
    {
        assertEq(2+2, 5, "Two plus two does not equal 5!");
    })

    TEST(secondTest,
    {
        assertEq(std::string("War"), std::string("Peace"), "War is not Peace!");
    })
})

TestEnvironment Test9()
{
    TestEnvironment tenv;

    std::cout << TestSuite_testTestSuite().getSummary() << std::endl;

    return tenv;
}

#endif