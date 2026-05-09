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
    size_t num_skipped_tests = 0;

public:
    TestSuiteReport(const std::string& suite_name)
        : suite_name{suite_name}
    {}

    void log(TestReport report)
    {
        reports.push_back(report);

        if (report.testSkipped())
        {
            ++num_skipped_tests;
        }
        else if (!report.testPassed())
        {
            passed = false;
            ++num_failing_reports;
        }
    }

    std::string getName()
    {
        return suite_name;
    }

    std::string getSummary()
    {
        std::stringstream summary;

        if (numTestsSkipped() == numTests())
        {
            summary << std::format(
                "Test suite \"{}\" was skipped ({} skipped tests)",
                suite_name,
                numTestsSkipped()
            ) << std::endl;

            summary.flush();

            return summary.str();
        }
        else if (numTestsSkipped() > 0)
        {
            summary << std::format(
                "Test suite \"{}\" ({}/{} passing tests, {} skipped)",
                suite_name,
                numTestsRan() - numFailingTests(),
                numTestsRan(),
                numTestsSkipped()
            ) << std::endl;
        }
        else
        {
            summary << std::format(
                "Test suite \"{}\" ({}/{} passing tests)",
                suite_name,
                numTestsRan() - numFailingTests(),
                numTestsRan()
            ) << std::endl;
        }

        for (TestReport report : reports)
        {
            if (report.testPassed() || report.testSkipped())
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

    size_t numTestsRan()
    {
        return numTests() - numTestsSkipped();
    }

    size_t numFailingTests()
    {
        return num_failing_reports;
    }

    size_t numTestsSkipped()
    {
        return num_skipped_tests;
    }

    size_t numPassingTests()
    {
        return numTests() - numFailingTests() - numTestsSkipped();
    }
};

#endif