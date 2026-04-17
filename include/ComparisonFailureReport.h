#ifndef COMPARISONFAILUREREPORT_H
#define COMPARISONFAILUREREPORT_H

#include <ostream>

#include "AssertionFailureReport.h"

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
    std::string comparisonSymbol;

    ComparisonFailureReport(
        const std::source_location& location,
        const std::string& msg,
        const TParam1& x,
        const TParam2& y,
        const std::string& comparisonSymbol
    ) : AssertionFailureReport(location, msg)
    {
        this->x = x;
        this->y = y;
        this->comparisonSymbol = comparisonSymbol;
    }

    ComparisonFailureReport(
        const std::source_location& location,
        const TParam1& x,
        const TParam2& y,
        const ComparisonType& comparisonSymbol
    ) : AssertionFailureReport(location)
    {
        this->x = x;
        this->y = y;
        this->comparisonSymbol = comparisonSymbol;
    }

    std::string getSummary() const override
    {
        std::stringstream summary;

        summary << formatMessage(location, msg);

        if constexpr (xUnitCpp_impl::Printable<TParam1> && xUnitCpp_impl::Printable<TParam2>)
            summary << std::endl << std::format("{} {} {}", x, comparisonSymbol, y) << std::endl; 
        
        summary.flush();

        return summary.str();
    }
};

#endif