#ifndef TESTENVIRONMENT_H
#define TESTENVIRONMENT_H

#include <string>
#include <memory>
#include <source_location>

#include "TestReport.h"
#include "TestSuiteReport.h"
#include "ComparisonFailureReport.h"

class TestEnvironment
{
private:
    std::vector<std::shared_ptr<TestSuiteReport>> suite_reports;

    std::unique_ptr<TestReport> curr_test_report;
    std::shared_ptr<TestSuiteReport> curr_test_suite_report;

    bool skip_tests = false;

    std::vector<void(TestEnvironment::*)()> tests;

protected:
    std::shared_ptr<TestSuiteReport> getLastSuiteReport()
    {
        return suite_reports.back();
    }

public:
    TestEnvironment()
    {}

    virtual void setUp() {}

    virtual void tearDown() {}

    template<std::derived_from<TestEnvironment> TSubclass>
    void registerTest(void(TSubclass::*test)())
    {
        tests.push_back(static_cast<void(TestEnvironment::*)()>(test));
    }

    void runTests()
    {
        for (auto test : tests)
        {
            setUp();
            (this->*test)();
            tearDown();
        }
    }

    void beginSuite(const std::string& suite_name)
    {
        endSuite();
        
        suite_reports.emplace_back(std::make_shared<TestSuiteReport>(suite_name));
        curr_test_suite_report = suite_reports.back();
    }

    void beginSuite()
    {
        beginSuite("Default");
    }

    void endSuite()
    {
        endTest();

        curr_test_suite_report = nullptr;
        skip_tests = false;
    }

    void beginTest(const std::string& test_name)
    {
        if (!curr_test_suite_report)
            beginSuite();

        endTest();

        curr_test_report = std::make_unique<TestReport>(test_name);

        if (skip_tests)
            curr_test_report->skip();
    }

    void beginTest()
    {
        if (!curr_test_suite_report)
            beginSuite();

        beginTest("Test " + std::to_string(curr_test_suite_report->numTests() + 1 + (curr_test_report ? 1 : 0)));
    }

    void endTest()
    {
        if (curr_test_report)
            curr_test_suite_report->log(*curr_test_report);
        
        curr_test_report = nullptr;
    }

    void skip()
    {
        if (curr_test_report)
            curr_test_report->skip();
        else 
            skip_tests = true;
    }

    void assert(bool statement, const std::string& msg, const std::source_location location = std::source_location::current())
    {
        if (!curr_test_report)
            beginTest();

        if (!statement)
        {
            AssertionFailureReport report(location, msg);

            curr_test_report->logFailedAssertion(report);
        }
    }

    void assert(bool statement, const std::source_location location = std::source_location::current())
    {
        assert(statement, "", location);
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 == p2;}
    void assertEq(const TParam1& x, const TParam2& y, const std::string& msg, const std::source_location location = std::source_location::current())
    {
        if (!curr_test_report)
            beginTest();

        if (!(x == y))
        {
            ComparisonFailureReport<TParam1, TParam2> report(location, msg, x, y, "==");

            curr_test_report->logFailedAssertion(report);
        }
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 == p2;}
    void assertEq(const TParam1& x, const TParam2& y, const std::source_location location = std::source_location::current())
    {
        assertEq(x, y, "", location);
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 != p2;}
    void assertNeq(const TParam1& x, const TParam2& y, const std::string& msg, const std::source_location location = std::source_location::current())
    {
        if (!curr_test_report)
            beginTest();

        if (!(x != y))
        {
            ComparisonFailureReport<TParam1, TParam2> report(location, msg, x, y, "!=");

            curr_test_report->logFailedAssertion(report);
        }
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 != p2;}
    void assertNeq(const TParam1& x, const TParam2& y, const std::source_location location = std::source_location::current())
    {
        assertNeq(x, y, "", location);
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 > p2;}
    void assertGt(const TParam1& x, const TParam2& y, const std::string& msg, const std::source_location location = std::source_location::current())
    {
        if (!curr_test_report)
            beginTest();

        if (!(x > y))
        {
            ComparisonFailureReport<TParam1, TParam2> report(location, msg, x, y, ">");

            curr_test_report->logFailedAssertion(report);
        }
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 > p2;}
    void assertGt(const TParam1& x, const TParam2& y, const std::source_location location = std::source_location::current())
    {
        assertGt(x, y, "", location);
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 < p2;}
    void assertLt(const TParam1& x, const TParam2& y, const std::string& msg, const std::source_location location = std::source_location::current())
    {
        if (!curr_test_report)
            beginTest();

        if (!(x < y))
        {
            ComparisonFailureReport<TParam1, TParam2> report(location, msg, x, y, "<");

            curr_test_report->logFailedAssertion(report);
        }
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 < p2;}
    void assertLt(const TParam1& x, const TParam2& y, const std::source_location location = std::source_location::current())
    {
        assertLt(x, y, "", location);
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 >= p2;}
    void assertGtEq(const TParam1& x, const TParam2& y, const std::string& msg, const std::source_location location = std::source_location::current())
    {
        if (!curr_test_report)
            beginTest();

        if (!(x >= y))
        {
            ComparisonFailureReport<TParam1, TParam2> report(location, msg, x, y, ">=");

            curr_test_report->logFailedAssertion(report);
        }
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 >= p2;}
    void assertGtEq(const TParam1& x, const TParam2& y, const std::source_location location = std::source_location::current())
    {
        assertGtEq(x, y, "", location);
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 <= p2;}
    void assertLtEq(const TParam1& x, const TParam2& y, const std::string& msg, const std::source_location location = std::source_location::current())
    {
        if (!curr_test_report)
            beginTest();

        if (!(x <= y))
        {
            ComparisonFailureReport<TParam1, TParam2> report(location, msg, x, y, "<=");

            curr_test_report->logFailedAssertion(report);
        }
    }

    template<typename TParam1, typename TParam2>
        requires requires (TParam1 p1, TParam2 p2) {p1 <= p2;}
    void assertLtEq(const TParam1& x, const TParam2& y, const std::source_location location = std::source_location::current())
    {
        assertLtEq(x, y, "", location);
    }

    std::string getSummary()
    {
        std::stringstream summary;

        if (curr_test_report)
            curr_test_suite_report->log(*curr_test_report);

        for (auto it = suite_reports.begin(); it != suite_reports.end(); ++it)
        {
            if (!it->get()->allTestsPassed() || it->get()->numTestsSkipped() > 0)
            {
                summary << it->get()->getSummary();

                if (it != suite_reports.end() - 1)
                    summary << std::endl;
            }
        }
        
        return summary.str();
    }
};

#endif