#ifndef ASSERTIONFAILUREREPORT_H
#define ASSERTIONFAILUREREPORT_H

#include <string>
#include <source_location>

struct AssertionFailureReport
{
    std::string& msg;
    std::source_location location;

    std::string getSummary()
    {
        
    }
};

/*
template<typename Param1, typename Param2>
struct ComparisonFailureReport : public AssertionFailureReport
{
    Param1 x;
    Param2 y;
};
*/

#endif