#ifndef TESTENVIRONMENT_H
#define TESTENVIRONMENT_H

#include <string>

#include "TestReport.h"
#include "TestSuiteReport.h"

class TestEnvironment
{
private:
    std::vector<std::shared_ptr<TestSuiteReport>> suite_reports;
    TestSuiteReport suite_report;
    std::unique_ptr<TestReport> curr_test_report;

public:
    TestEnvironment()
        : suite_report{"Default"}
    {}

    void beginSuite(const std::string& suite_name)
    {
        suite_reports.emplace_back(std::make_shared<TestSuiteReport>(suite_name));
    }

    void beginTest(const std::string& test_name)
    {
        if (curr_test_report)
            suite_report.log(*curr_test_report);

        curr_test_report = std::make_unique<TestReport>(test_name);
    }

    void assert(bool statement, const std::string& msg)
    {
        if (!statement)
            curr_test_report->logFailedAssertion(msg);
    }

    std::string getSummary()
    {
        if (curr_test_report)
            suite_report.log(*curr_test_report);

        return suite_report.getSummary();
    }
};

#endif