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

    Suite default_suite;
    std::vector<Suite> suites {};

public:
    TestingUnit(const std::string& file_name = "")
        : default_suite {file_name}
    {}

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

    void addSuite(const Suite& suite)
    {
        for (auto& test : suite.tests)
            addTestEnvironment(test, suite.name);
    }

    void combineReports(const TestingUnit& other)
    {
        for (auto test : other.default_suite.tests)
            default_suite.tests.push_back(test);

        for (auto& suite : other.suites)
            addSuite(suite);
    }

    std::string getSummary()
    {
        std::string default_suite_summary = default_suite.getReport().getSummaryNoHeader();

        std::stringstream main_summary;
        for (auto it = suites.begin(); it != suites.end(); ++it)
        {
            Suite& suite = *it;

            if (suite.getReport().allTestsPassed())
                continue;

            main_summary << suite.getReport().getSummary();

            if (it != suites.end() - 1)
                main_summary << std::endl;
        }
        main_summary.flush();

        std::stringstream full_summary;

        full_summary << default_suite_summary;

        if (main_summary.str() != "")
            full_summary << std::endl;
        
        full_summary << main_summary.str();
        full_summary.flush();

        return full_summary.str();
    }
};

#endif