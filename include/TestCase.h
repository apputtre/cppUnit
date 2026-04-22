#ifndef TESTCASE_H
#define TESTCASE_H

#include "TestReport.h"

class TestCase
{
public:
    TestReport report;

    void assert(bool statement, const std::string& msg, const std::source_location location = std::source_location::current())
    {
        if (!statement)
        {
            AssertionFailureReport assertion_report(location, msg);

            report.logFailedAssertion(assertion_report);
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
            ComparisonFailureReport<TParam1, TParam2> assertion_report(location, msg, x, y, "==");

            report.logFailedAssertion(assertion_report);
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
            ComparisonFailureReport<TParam1, TParam2> assertion_report(location, msg, x, y, "!=");

            report.logFailedAssertion(assertion_report);
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
        if (!(x > y))
        {
            ComparisonFailureReport<TParam1, TParam2> assertion_report(location, msg, x, y, ">");

            report.logFailedAssertion(assertion_report);
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
        if (!(x < y))
        {
            ComparisonFailureReport<TParam1, TParam2> assertion_report(location, msg, x, y, "<");

            report.logFailedAssertion(assertion_report);
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
        if (!(x >= y))
        {
            ComparisonFailureReport<TParam1, TParam2> assertion_report(location, msg, x, y, ">=");

            report.logFailedAssertion(assertion_report);
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
        if (!(x <= y))
        {
            ComparisonFailureReport<TParam1, TParam2> assertion_report(location, msg, x, y, "<=");

            report.logFailedAssertion(assertion_report);
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

        return summary.str();
    }
};

#endif