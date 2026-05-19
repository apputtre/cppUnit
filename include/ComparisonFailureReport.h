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
    std::string x;
    std::string y;
    std::string comparison_symbol;

    ComparisonFailureReport(
        const std::source_location& location,
        const std::string& msg,
        const TParam1& x,
        const TParam2& y,
        const std::string& comparison_symbol
    ) : AssertionFailureReport(location, msg)
    {
        std::stringstream ss;

        if constexpr (yUnit_impl::Printable<TParam1>)
            ss << x;
        else
            ss << "<LHS>";

        ss.flush();
        this->x = ss.str();
        ss.str("");

        if constexpr (yUnit_impl::Printable<TParam2>)
            ss << y;
        else
            ss << "<RHS>";

        ss.flush();
        this->y = ss.str();

        this->comparison_symbol = comparison_symbol;
    }

    std::string getSummary() const override
    {
        std::stringstream summary;

        summary << formatMessage(location, msg) << std::endl;
        summary << '\t' << std::format("{} {} {}", x, comparison_symbol, y) << std::endl;

        summary.flush();
        return summary.str();
    }
};

#endif