#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <format>

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
            summary << "Test " << "\"" << testName << "\"" << " passed" << std::endl;
        else
            summary << "Test " << "\"" << testName << "\"" << " failed" << std::endl;

        
        for (const std::string& entry : log)
            summary << '\t' << entry << std::endl;

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
    std::string suite_name;
    bool passed = true;
    std::vector<TestReport> reports;
    size_t num_failing_reports = 0;

public:
    TestSuiteReport(const std::string& suiteName)
        : suite_name{suiteName}
    {}

    void log(TestReport report)
    {
        reports.push_back(report);

        if (!report.testPassed())
        {
            passed = false;
            ++num_failing_reports;
        }
    }

    std::string getSummary()
    {
        std::stringstream summary;

        summary << std::format("Test suite \"{}\" ({}/{} passing tests)", suite_name, reports.size() - num_failing_reports, reports.size()) << std::endl;

        for (TestReport report : reports)
        {
            if (report.testPassed())
                continue;

            std::stringstream reportSummary(report.getSummary());

            for (std::string line; !reportSummary.eof(); std::getline(reportSummary, line))
                summary << '\t' << line << std::endl;
        }

        summary.flush();

        return summary.str();
    }

    bool allTestsPassed()
    {
        return passed;
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

        TestSuite suite("Test test suite");

        suite.add(test1);
        suite.add(test2);

        TestSuiteReport report = suite.run();

        std::cout << report.getSummary() << std::endl;
    }

    return 0;
}