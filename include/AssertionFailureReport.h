#ifndef ASSERTIONFAILUREREPORT_H
#define ASSERTIONFAILUREREPORT_H

#include <string>
#include <source_location>
#include <format>

struct AssertionFailureReport
{
    std::source_location location;
    std::string msg = "";

    AssertionFailureReport(const std::source_location& location, const std::string& msg)
    {
        this->location = location;
        this->msg = msg;
    }

    AssertionFailureReport(const std::source_location& location)
    {
        this->location = location;
    }

    virtual std::string getSummary() const
    {
        return std::format("Assertion failure (file {}, line {})", location.file_name(), location.line());
    }
};

template<typename Param1, typename Param2>
struct ComparisonFailureReport : AssertionFailureReport
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

    ComparisonFailureReport(
        const std::source_location& location,
        const std::string& msg,
        const Param1& x,
        const Param2& y,
        const ComparisonType& comparisonType
    ) : AssertionFailureReport(location, msg)
    {
        this->x = x;
        this->y = y;
        this->comparisonType = comparisonType;
    }

    ComparisonFailureReport(
        const std::source_location& location,
        const Param1& x,
        const Param2& y,
        const ComparisonType& comparisonType
    ) : AssertionFailureReport(location)
    {
        this->x = x;
        this->y = y;
        this->comparisonType = comparisonType;
    }

    std::string getSummary() const override
    {
        std::cout << 1 << std::endl;
        std::string comparison_description;

        switch(comparisonType)
        {
            case ComparisonType::EqualTo:
                comparison_description = std::format("{} == {}", x, y);
                break;
            default:
                throw std::runtime_error("Not implemented");
        }

        return std::format("Assertion failure (file {}, line {})\n{}", location.file_name(), location.line(), comparison_description);
    }
};

#endif