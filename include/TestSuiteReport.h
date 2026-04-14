#ifndef TESTSUITEREPORT_H
#define TESTSUITEREPORT_H

#include <string>
#include <vector>
#include <sstream>

#include "TestReport.h"

struct TestSuiteReport
{
private:
    std::string suite_name;
    bool passed = true;
    std::vector<TestReport> reports;
    size_t num_failing_reports = 0;

public:
    TestSuiteReport(const std::string& suiteName)
        : suite_name{suiteName}
    {}

    void log(TestReport report)
    {
        reports.push_back(report);

        if (!report.testPassed())
        {
            passed = false;
            ++num_failing_reports;
        }
    }

    std::string getSummary()
    {
        std::stringstream summary;

        summary << std::format(
            "Test suite \"{}\" ({}/{} passing tests)",
            suite_name,
            reports.size() - num_failing_reports,
            reports.size()
        ) << std::endl;

        for (TestReport report : reports)
        {
            if (report.testPassed())
                continue;

            std::stringstream reportSummary(report.getSummary());

            for (std::string line; !reportSummary.eof(); std::getline(reportSummary, line))
                summary << '\t' << line << std::endl;
        }

        summary.flush();

        return summary.str();
    }

    bool allTestsPassed()
    {
        return passed;
    }

    size_t numTests()
    {
        return reports.size();
    }
};

#endif