#ifndef COMPARISONFAILUREREPORT_H
#define COMPARISONFAILUREREPORT_H

#include <ostream>

#include "AssertionFailureReport.h"

namespace yUnit_impl 
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
    TParam1 x;
    TParam2 y;
    std::string comparison_symbol;

    ComparisonFailureReport(
        const std::source_location& location,
        const std::string& msg,
        const TParam1& x,
        const TParam2& y,
        const std::string& comparison_symbol
    ) : AssertionFailureReport(location, msg)
    {
        this->x = x;
        this->y = y;
        this->comparison_symbol = comparison_symbol;
    }

    std::string getSummary() const override
    {
        std::stringstream summary;

        summary << formatMessage(location, msg);

        summary << std::endl << '\t';

        if constexpr (yUnit_impl::Printable<TParam1>)
            summary << x;
        else
            summary << "<LHS>";
        
        summary << " " << comparison_symbol << " ";

        if constexpr (yUnit_impl::Printable<TParam2>)
            summary << y;
        else
            summary << "<RHS>";
        
        summary << std::endl;
        
        summary.flush();

        return summary.str();
    }
};

#endif