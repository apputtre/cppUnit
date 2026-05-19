#ifndef TESTINGUNIT_H
#define TESTINGUNIT_H

#include <string>

#include "TestReport.h"
#include "TestSuiteReport.h"
#include "TestEnvironment.h"

class TestingUnit
{
private:
    class Suite
    {
    private:
        std::unique_ptr<TestSuiteReport> report;

    public:
        std::string name;
        std::vector<std::shared_ptr<TestEnvironment>> tests {};

        Suite(const std::string& name)
        {
            this->name = name;
        }

        TestSuiteReport getReport()
        {
            report = std::make_unique<TestSuiteReport>(name);

            for (auto& tenv : tests)
                report->log(tenv->runTests());

            return TestSuiteReport(*report);
        }
    };

    std::string file_name;
    Suite default_suite;

public:
    std::vector<Suite> suites {};

    TestingUnit(const std::string& file_name = "")
        : default_suite {""}
    {
        this->file_name = file_name;
    }

    void addTestEnvironment(std::shared_ptr<TestEnvironment> p_tenv, const std::string& suite_name)
    {
        if (suite_name == "")
        {
            default_suite.tests.emplace_back(p_tenv);

            return;
        }

        for (auto& suite : suites)
        {
            if (suite.name == suite_name)
            {
                suite.tests.emplace_back(p_tenv);

                return;
            }
        }

        suites.push_back(Suite(suite_name));
        suites.back().tests.emplace_back(p_tenv);
    }

    void addSuite(Suite& suite)
    {
        for (auto& test : suite.tests)
            addTestEnvironment(test, suite.name);
    }

    std::string getSummary()
    {
        std::stringstream summary;

        TestSuiteReport default_suite_report = default_suite.getReport();

        summary << default_suite_report.getSummaryNoHeader();

        if (suites.size() > 0)
            summary << std::endl;

        for (auto it = suites.begin(); it != suites.end(); ++it)
        {
            Suite& suite = *it;

            if (suite.getReport().allTestsPassed())
                continue;

            summary << suite.getReport().getSummary();

            if (it != suites.end() - 1)
                summary << std::endl;
        }

        return summary.str();
    }

    std::string getFileName()
    {
        return file_name;
    }
};

#endif