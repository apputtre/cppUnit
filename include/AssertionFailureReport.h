#ifndef ASSERTIONFAILUREREPORT_H
#define ASSERTIONFAILUREREPORT_H

#include <string>
#include <source_location>
#include <format>
#include <ostream>

struct AssertionFailureReport
{
public:
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

        summary << formatMessage(location, msg);
        
        summary.flush();

        return summary.str();
    }

protected:
    std::string formatMessage(const std::source_location& location, const std::string& msg) const
    {
        std::stringstream message;

        message << std::format("Assertion failure (file {}, line {})", location.file_name(), location.line());

        if (msg != "")
            message << ": \"" << msg << "\"";
        
        return message.str();
    }
};

#endif