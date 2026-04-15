#ifndef ASSERTIONFAILUREREPORT_H
#define ASSERTIONFAILUREREPORT_H

#include <string>
#include <source_location>
#include <format>
#include <ostream>

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
        std::stringstream summary;


        summary << std::format("Assertion failure (file {}, line {})", location.file_name(), location.line());

        if (msg != "")
            summary << std::format(": {}", msg);
        
        summary.flush();

        return summary.str();
    }
};

namespace xUnitCpp_impl
{
    template<typename T>
    concept Printable = requires(T t, std::ostream os)
    {
        os << t;
    };
};

template<typename TParam1, typename TParam2>
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

    TParam1 x;
    TParam2 y;
    ComparisonType comparisonType;

    ComparisonFailureReport(
        const std::source_location& location,
        const std::string& msg,
        const TParam1& x,
        const TParam2& y,
        const ComparisonType& comparisonType
    ) : AssertionFailureReport(location, msg)
    {
        this->x = x;
        this->y = y;
        this->comparisonType = comparisonType;
    }

    ComparisonFailureReport(
        const std::source_location& location,
        const TParam1& x,
        const TParam2& y,
        const ComparisonType& comparisonType
    ) : AssertionFailureReport(location)
    {
        this->x = x;
        this->y = y;
        this->comparisonType = comparisonType;
    }

    std::string getSummary() const override
    {
        std::stringstream summary;

        summary << std::format("Assertion failure (file {}, line {})", location.file_name(), location.line());

        if constexpr (xUnitCpp_impl::Printable<TParam1> && xUnitCpp_impl::Printable<TParam2>)
        {
            summary << std::endl;

            switch(comparisonType)
            {
                case ComparisonType::EqualTo:
                    summary << x << " == " << y << std::endl;
                    break;
                default:
                    throw std::runtime_error("Not implemented");
            }
        }
        
        summary.flush();

        return summary.str();
    }

};

#endif