#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>
#include <source_location>

#include "TestReport.h"
#include "TestCase.h"

class TestCase
{
public:
    TestCase(const std::string& name)
        : name{name}, report{name}
    {}

    TestReport run()
    {
        this->report = TestReport {name};

        setUp();
        test();
        tearDown();

        return report;
    }

    virtual void setUp() {}
    virtual void tearDown() {}

    virtual void test() = 0;

protected:
    std::string name;
    TestReport report;

    void assert(bool statement, const std::source_location location = std::source_location::current())
    {
        if (!statement)
            report.logFailedAssertion(location);
    }

    void assert(bool statement, const std::string& msg, std::source_location location = std::source_location::current())
    {
        if (!statement)
            report.logFailedAssertion(msg, location);
    }
};

#endif