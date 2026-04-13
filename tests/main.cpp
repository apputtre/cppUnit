#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <format>

#include "TestSuiteReport.h"
#include "TestCase.h"

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

class TestSuite
{
private:
    std::vector<std::shared_ptr<TestCase>> tests;
    std::string name;
    TestSuiteReport report;

public:
    TestSuite(const std::string name)
        : name{name}, report{name}
    {};

    template <typename T>
    void add(const T& test)
    {
        static_assert(std::is_base_of<TestCase, T>::value, "T must derive from TestCase");

        this->tests.emplace_back(std::make_shared<T>(test));
    }

    TestSuiteReport run()
    {
        for (std::shared_ptr<TestCase> test : tests)
            report.log(test->run());
        
        return report;
    }
};

class TestEnvironment
{
private:
    TestSuiteReport report;
    std::unique_ptr<TestReport> current_test;

public:
    TestEnvironment()
        : report{"Default"}
    {}

    void beginTest(const std::string& test_name)
    {
        if (current_test)
            report.log(*current_test);

        current_test = std::make_unique<TestReport>(test_name);
    }

    void assert(bool statement, const std::string& msg)
    {
        if (!statement)
            current_test->logFailedAssertion(msg);
    }

    std::string getSummary()
    {
        if (current_test)
            report.log(*current_test);

        return report.getSummary();
    }
};

int main()
{
    {
        TwoPlusTwoEqualsFive test("2+2=5?");
        TestReport report = test.run();
        std::cout << report.getSummary() << std::endl;
    }
   
    {
        TwoPlusTwoEqualsFour test("2+2=4?");
        TestReport report = test.run();
        std::cout << report.getSummary() << std::endl << std::endl;
    }

    {
        TwoPlusTwoEqualsFive test1("2+2=5?");
        TwoPlusTwoEqualsFour test2("2+2=4?");
        TwoPlusTwoEqualsSeven test3("2+2=7?");

        TestSuite suite("Test test suite");

        suite.add(test1);
        suite.add(test2);
        suite.add(test3);

        TestSuiteReport report = suite.run();

        std::cout << report.getSummary() << std::endl;
    }

    {
        TestEnvironment tenv;

        tenv.beginTest("2+2=5?");
        tenv.assert(2 + 2 == 5, "Two plus two does not equal 5!");

        tenv.beginTest("2+2=4?");
        tenv.assert(2 + 2 == 4, "Two plus two does not equal 4!");

        tenv.beginTest("2+2=7?");
        tenv.assert(2 + 2 == 7, "Two plus two does not equal 7!");

        std::cout << tenv.getSummary() << std::endl;
    }

    return 0;
}