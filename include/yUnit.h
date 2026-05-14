#ifndef YUNIT_H
#define YUNIT_H

#include <vector>
#include <sstream>
#include <string>
#include <regex>

#include "TestEnvironment.h"

namespace yUnit
{
    namespace impl
    {
        std::vector<std::pair<const std::string, std::shared_ptr<TestSuiteReport>>> suiteReports;
        std::vector<std::unique_ptr<TestEnvironment>> testEnvs;

        TestEnvironment globalTestEnv;

        void logSuiteReport(std::shared_ptr<TestSuiteReport> report, const std::string& path)
        {
            std::smatch file_name_match;\
            const std::regex regex("^(?:.*/)?(.+?)(?:\\.[^.]*$|$)");\
            std::regex_match(path, file_name_match, regex);\
            std::string file_name = file_name_match[1];\

            suiteReports.emplace_back(file_name, report);
        }

        template<std::derived_from<TestEnvironment> T>
        void registerTestEnvironment(std::unique_ptr<T>& p_tenv)
        {
            testEnvs.emplace_back(std::move(p_tenv));
        }
    }

    TestEnvironment& getGlobalTestEnvironment()
    {
        return impl::globalTestEnv;
    }

    void runTests()
    {
        for (std::unique_ptr<TestEnvironment>& tenv : impl::testEnvs)
        {
            tenv->runTests();
            impl::globalTestEnv.combineReports(*tenv);
        }
    }

    std::string getSummary(const std::string& file_name = "")
    {
        std::stringstream summary;

        bool found_requested_file = true;
        if (file_name != "")
            found_requested_file = false;

        bool first_report = true;
        for (auto report : impl::suiteReports)
        {
            if (file_name == "" || report.first == file_name)
            {
                found_requested_file = true;
                if (!report.second->allTestsPassed() || report.second->numTestsSkipped() > 0)
                {
                    if (!first_report)
                        summary << std::endl;

                    summary << report.second->getSummary();

                    first_report = false;
                }
            }
        }

        if (!found_requested_file)
            throw std::runtime_error("File not found");
        
        summary.flush();
        return summary.str();
    }

    void clearSummary()
    {
        impl::suiteReports.clear();
    }
};

#define SUITE(suite_name, ...)\
namespace yUnit\
{\
    class Suite_##suite_name : public TestEnvironment\
    {\
    public:\
        Suite_##suite_name()\
        {\
            beginSuite(#suite_name);\
            __VA_ARGS__\
            endSuite();\
            impl::logSuiteReport(getLastSuiteReport(), __FILE__);\
        }\
    };\
    namespace impl\
    {\
        Suite_##suite_name suite_##suite_name;\
    }\
};

#define TEST(test_name, ...)\
    beginTest(#test_name);\
    __VA_ARGS__\
    endTest();

#endif