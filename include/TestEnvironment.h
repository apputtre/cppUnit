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
    std::vector<std::unique_ptr<TestReport>> reports;
    std::unique_ptr<TestReport> curr_test_report = nullptr;

    struct Test
    {
        std::string name;
        void(TestEnvironment::*func)();
    };

    std::vector<Test> tests;

    void runTest(const Test& test)
    {
        setUp();

        if (test.name != "")
            beginTest(test.name);
        else
            beginTest();
        (this->*test.func)();
        endTest();

        tearDown();
    }

    void beginTest(const std::string& test_name)
    {
        endTest();
        curr_test_report = std::make_unique<TestReport>(test_name);
    }

    void beginTest()
    {
        beginTest("Test " + std::to_string(reports.size() + 1 + (curr_test_report ? 1 : 0)));
    }

    void endTest()
    {
        if (curr_test_report)
            reports.emplace_back(curr_test_report.release());
        
        curr_test_report = nullptr;
    }

protected:
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

public:
    TestEnvironment() {}

    virtual void setUp() {}
    virtual void tearDown() {}

    template<std::derived_from<TestEnvironment> TSubclass>
    void addTest(const std::string& name, void(TSubclass::*test)())
    {
        tests.push_back(
            Test {name, static_cast<void(TestEnvironment::*)()>(test)}
        );
    }

    template<std::derived_from<TestEnvironment> TSubclass>
    void addTest(void(TSubclass::*test)())
    {
        tests.push_back(
            Test {"", static_cast<void(TestEnvironment::*)()>(test)}
        );
    }

    std::vector<TestReport> runTests()
    {
        reports.clear();

        for (auto test : tests)
            runTest(test);

        std::vector<TestReport> ret;
        for (auto& report : reports)
            ret.emplace_back(*report);

        return ret;
    }

    TestReport runTest(const std::string& name)
    {
        for (auto test : tests)
        {
            if (test.name == name)
            {
                reports.clear();
                runTest(test);
                return TestReport(*reports.begin()->get());
            }
        }

        throw std::runtime_error(std::format("Attempted to run nonexistant test {}", name));
    }

    std::vector<std::string> getTests()
    {
        std::vector<std::string> ret;

        for (auto test : tests)
            ret.push_back(test.name);
        
        return ret;
    }

    std::string getSummary()
    {
        runTests();

        std::stringstream summary;

        for (auto& report : reports)
        {
            if (report->testPassed())
                continue;

            summary << report->getSummary();
        }

        return summary.str();
    }
};

#endif