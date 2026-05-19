#ifndef TESTSUITEREPORT_H
#define TESTSUITEREPORT_H

#include <string>
#include <vector>
#include <sstream>
#include <format>

#include "TestReport.h"

struct TestSuiteReport
{
private:
    std::string suite_name;
    bool passed = true;
    std::vector<TestReport> reports;
    size_t num_failing_reports = 0;

public:
    TestSuiteReport(const std::string& suite_name)
        : suite_name{suite_name}
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

    void log(std::vector<TestReport> reports)
    {
        for (auto report : reports)
            log(report);
    }

    std::string getName()
    {
        return suite_name;
    }

    std::string getSummary()
    {
        std::stringstream summary;

        summary << std::format(
            "Test suite \"{}\" ({}/{} passing tests)",
            suite_name,
            numTests() - numFailingTests(),
            numTests()
        ) << std::endl;

        for (TestReport report : reports)
        {
            if (report.testPassed())
                continue;

            std::stringstream report_summary(report.getSummary());

            std::string line;
            for (std::getline(report_summary, line); !report_summary.eof(); std::getline(report_summary, line))
                summary << '\t' << line << std::endl;
            if (line.size() > 0)
                summary << line << std::endl;
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

    size_t numFailingTests()
    {
        return num_failing_reports;
    }

    size_t numPassingTests()
    {
        return numTests() - numFailingTests();
    }
};

#endif