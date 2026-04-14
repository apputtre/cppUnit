#ifndef TESTENVIRONMENT_H
#define TESTENVIRONMENT_H

#include <string>

#include "TestReport.h"
#include "TestSuiteReport.h"

class TestEnvironment
{
private:
    std::vector<std::shared_ptr<TestSuiteReport>> suite_reports;
    std::unique_ptr<TestReport> curr_test_report;

public:
    TestEnvironment()
    {}

    void beginSuite(const std::string& suite_name)
    {
        if (curr_test_report)
            suite_reports.back()->log(*curr_test_report);
        
        curr_test_report = nullptr;

        suite_reports.emplace_back(std::make_shared<TestSuiteReport>(suite_name));
    }

    void beginTest(const std::string& test_name)
    {
        if (suite_reports.size() == 0)
            suite_reports.emplace_back(std::make_shared<TestSuiteReport>("Default"));

        if (curr_test_report)
            suite_reports.back()->log(*curr_test_report);

        curr_test_report = std::make_unique<TestReport>(test_name);
    }

    void beginTest()
    {
        beginTest("Dummy test");
    }

    void assert(bool statement, const std::string& msg)
    {
        if (!statement)
            curr_test_report->logFailedAssertion(msg);
    }

    std::string getSummary()
    {
        std::stringstream summary;

        if (curr_test_report)
            suite_reports.back()->log(*curr_test_report);

        for (std::shared_ptr<TestSuiteReport> report : suite_reports)
            summary << report->getSummary() << std::endl;
        
        return summary.str();
    }
};

#endif