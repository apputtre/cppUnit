#include <string>
#include <sstream>
#include <iostream>
#include <vector>

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
        assert(2 + 2 == 5);
    }
};

class TwoPlusTwoEqualsFour : public TestTestCase
{
public:
    TwoPlusTwoEqualsFour(const std::string& name) : TestTestCase(name)
    {}

    void test() override
    {
        assert(2 + 2 == 4);
    }
};

int main()
{

    {
        TwoPlusTwoEqualsFive test("2+2=5?");

        TestReport report = test.run();
        if (report.testPassed())
            std::cout << "Test passed\n";
        else
            std::cout << "Test failed\n";
        std::cout << "Report summary:\n";
        std::cout << report.getSummary();
    }
   
    {
        TwoPlusTwoEqualsFour test("2+2=4?");

        TestReport report = test.run();
        if (report.testPassed())
            std::cout << "Test passed\n";
        else
            std::cout << "Test failed\n";    
        std::cout << "Report summary:\n";
        std::cout << report.getSummary();
    }

    return 0;
}