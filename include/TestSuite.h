#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>

#include "TestEnvironment.h"

class TestSuite
{
public:
    TestSuiteReport report;
    std::unique_ptr<TestReport> curr_test_report;

    TestSuite(const std::string& name)
        : report{name}
    {}

    void beginTest(const std::string& test_name)
    {
        endTest();

        curr_test_report = std::make_unique<TestReport>(test_name);
    }

    void beginTest()
    {
        beginTest("Test " + std::to_string(report.numTests() + 1 + (curr_test_report ? 1 : 0)));
    }

    void endTest()
    {
        if (curr_test_report)
            report.log(*curr_test_report);
        
        curr_test_report = nullptr;
    }

    std::string getSummary()
    {
        std::stringstream summary;

        if (curr_test_report)
            report.log(*curr_test_report);
        
        return summary.str();
    }
};

#endif