#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>

struct TestReport
{
private:
    std::vector<std::string> log;
    bool passed = true;
    std::string testName;

public:

    TestReport(const std::string& testName)
        : testName{testName}
    {}

    bool testPassed()
    {
        return passed;
    }

    std::string getSummary()
    {
        std::stringstream summary;

        if (passed)
            summary << "Test " << testName << " passed" << std::endl;
        else
            summary << "Test " << testName << " failed" << std::endl;

        for (const std::string& entry : log)
            summary << entry << std::endl;

        summary.flush();

        return summary.str();
    }

    void logFailedAssertion()
    {
        log.push_back("Assertion failure");
        passed = false;
    }

    void logFailedAssertion(const std::string& msg)
    {
        log.push_back("Assertion failure: " + msg);
        passed = false;
    }
};

struct TestSuiteReport
{
private:
    std::string suiteName;
    bool passed = true;
    std::vector<TestReport> reports;

public:
    TestSuiteReport(const std::string& suiteName)
        : suiteName{suiteName}
    {}
};

class TestCase
{
public:
    TestCase(const std::string& name)
        : name{name}, report{name}
    {}

    TestReport run()
    {
        this->report = TestReport {name};

        setUp();
        test();
        tearDown();

        return report;
    }

    virtual void setUp() {}
    virtual void tearDown() {}

    virtual void test() = 0;

protected:
    std::string name;
    TestReport report;

    void assert(bool statement)
    {
        if (!statement)
            report.logFailedAssertion();
    }

    void assert(bool statement, const std::string& msg)
    {
        if (!statement)
            report.logFailedAssertion(msg);
    }
};

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

class TestSuite
{
private:
    std::vector<TestCase*> tests;

public:
    TestSuite() {};

    template <typename T>
    void add(const T& test)
    {
        T* t = new T(test);
        this->tests.push_back(t);
    }

    bool run()
    {
        bool all_tests_passed = true;

        for (TestCase* test_case_ptr : tests)
            if (!test_case_ptr->run().testPassed())
                all_tests_passed = false;
        
        return all_tests_passed;
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

        TestSuite suite;

        suite.add(test1);
        suite.add(test2);

        if (suite.run())
            std::cout << "Test suite passed" << std::endl;
        else
            std::cout << "Test suite failed" << std::endl;

        /*
        std::cout << suite.getSummary() std::endl;

        suite.add("2+2=5?", []{assert(2 + 2 == 5, "Two plus two does not equal 5!";)});
        */
    }

    return 0;
}