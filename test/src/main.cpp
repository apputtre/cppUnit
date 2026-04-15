#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <format>

#include "TestSuiteReport.h"
#include "TestCase.h"
#include "TestSuite.h"
#include "TestEnvironment.h"

class TestTestCase : public TestCase
{
public:
    TestTestCase(const std::string& name) : TestCase(name)
    {}

    TestReport run()
    {
        std::cout << "Running test " << this->name << std::endl;

        return TestCase::run();
    }

    void setUp()
    {
        std::cout << "setUp called\n";
    }

    void tearDown()
    {
        std::cout << "tearDown called\n";
    }
};

class TwoPlusTwoEqualsFive : public TestTestCase
{
public:
    TwoPlusTwoEqualsFive(const std::string& name) : TestTestCase(name)
    {}

    void test() override
    {
        assert(2 + 2 == 5, "Two plus two does not equal five!");
    }
};

class TwoPlusTwoEqualsFour : public TestTestCase
{
public:
    TwoPlusTwoEqualsFour(const std::string& name) : TestTestCase(name)
    {}

    void test() override
    {
        assert(2 + 2 == 4, "Two plus two does not equal four!");
    }
};

class TwoPlusTwoEqualsSeven : public TestTestCase
{
public:
    TwoPlusTwoEqualsSeven(const std::string& name) : TestTestCase(name)
    {}

    void test() override
    {
        assert(2 + 2 == 7, "Two plus two does not equal seven!");
    }
};

int main()
{
    {
        std::cout << "=== TEST 1 ===" << std::endl;
        TwoPlusTwoEqualsFive test("2+2=5?");
        TestReport report = test.run();
        std::cout << report.getSummary();
    }

    std::cout << std::endl;
   
    {
        std::cout << "=== TEST 2 ===" << std::endl;
        TwoPlusTwoEqualsFour test("2+2=4?");
        TestReport report = test.run();
        std::cout << report.getSummary();
    }

    std::cout << std::endl;

    {
        std::cout << "=== TEST 3 ===" << std::endl;
        TwoPlusTwoEqualsFive test1("2+2=5?");
        TwoPlusTwoEqualsFour test2("2+2=4?");
        TwoPlusTwoEqualsSeven test3("2+2=7?");

        TestSuite suite("Test Suite");

        suite.add(test1);
        suite.add(test2);
        suite.add(test3);

        TestSuiteReport report = suite.run();

        std::cout << report.getSummary();
    }

    std::cout << std::endl;

    {
        std::cout << "=== TEST 4 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginTest("2+2=5?");
        tenv.assert(2 + 2 == 5, "Two plus two does not equal 5!");

        tenv.beginTest("2+2=4?");
        tenv.assert(2 + 2 == 4, "Two plus two does not equal 4!");

        tenv.beginTest("2+2=7?");
        tenv.assert(2 + 2 == 7, "Two plus two does not equal 7!");

        std::cout << tenv.getSummary();
    }

    std::cout << std::endl;

    {
        std::cout << "=== TEST 5 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginSuite("Basic arithmetic");

        tenv.beginTest("2+2=5?");
        tenv.assert(2 + 2 == 5, "Two plus two does not equal 5!");

        tenv.beginTest("2+2=4?");
        tenv.assert(2 + 2 == 4, "Two plus two does not equal 4!");

        tenv.beginTest("2+2=7?");
        tenv.assert(2 + 2 == 7, "Two plus two does not equal 7!");

        tenv.beginSuite("String comparison");

        tenv.beginTest("abc=def?");
        tenv.assert(std::string("abc") == std::string("def"), "abc does not equal def!");

        tenv.beginTest("abc=abc?");
        tenv.assert(std::string("abc") == std::string("abc"), "abc does not equal abc!");

        std::cout << tenv.getSummary();
    }

    std::cout << std::endl;

    {
        std::cout << "=== TEST 6 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginSuite("First suite");

        tenv.beginTest();
        tenv.assert(false, "false is false!");

        tenv.beginTest();
        tenv.assert(false, "false is false!");

        tenv.beginTest();
        tenv.assert(false, "false is false!");

        tenv.beginSuite("Second suite");

        tenv.beginTest();
        tenv.assert(true, "This test should pass");

        tenv.beginTest();
        tenv.assert(false, "This test should fail");

        std::cout << tenv.getSummary();
    }

    std::cout << std::endl;

    {
        std::cout << "=== TEST 7 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginSuite("Test suite");

        tenv.beginTest();
        tenv.assert(false);

        std::cout << tenv.getSummary();
    }

    return 0;
}