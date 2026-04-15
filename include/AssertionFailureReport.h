#ifndef ASSERTIONFAILUREREPORT_H
#define ASSERTIONFAILUREREPORT_H

#include <string>
#include <source_location>
#include <format>

struct AssertionFailureReport
{
    std::source_location location;
    std::string msg = "";

    std::string getSummary() const
    {
        return std::format("Assertion failure (file {}, line {})", location.file_name(), location.line());
    }
};

template<typename Param1, typename Param2>
struct ComparisonFailureReport : public AssertionFailureReport
{
    enum ComparisonType
    {
        EqualTo,
        NotEqualTo,
        LessThan,
        LessThanOrEqualTo,
        GreaterThan,
        GreaterThanOrEqualTo
    };

    Param1 x;
    Param2 y;
    ComparisonType comparisonType;

    std::string getSummary() const
    {
        return std::format("Assertion failure (file {}, line {})", location.file_name(), location.line());
    }
};

#endif