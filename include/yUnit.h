#ifndef YUNIT_H
#define YUNIT_H

#include <vector>
#include <sstream>
#include <string>
#include <regex>
#include <source_location>

#include "TestEnvironment.h"

namespace yUnit
{
    namespace impl
    {
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

        struct TestingUnit
        {
            std::string file_name;
            Suite default_suite;
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

                for (auto it = default_suite.tests.begin(); it != default_suite.tests.end(); ++it)
                {
                    TestEnvironment& tenv = **it;

                    summary << tenv.getSummary();

                    if (it == default_suite.tests.end() - 1)
                    {
                        if (suites.size() > 0)
                            summary << std::endl;
                    }
                }

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
        };

        inline std::vector<TestingUnit> testing_units;
        template<std::derived_from<TestEnvironment> T>
        inline void registerTestEnvironment(const std::string& file_name, std::shared_ptr<T> p_tenv, const std::string& suite_name)
        {
            auto it = std::find_if(testing_units.begin(), testing_units.end(), [file_name](TestingUnit& t)
            {
                return (t.file_name == file_name);
            });

            if (it != testing_units.end())
            {
                it->addTestEnvironment(p_tenv, suite_name);
            }
            else
            {
                testing_units.emplace_back(TestingUnit {file_name});
                testing_units.back().addTestEnvironment(p_tenv, suite_name);
            }
        }

        template<std::derived_from<TestEnvironment> T>
        struct TestEnvironmentRegistrar
        {
            TestEnvironmentRegistrar(const std::string& file_name, std::shared_ptr<T> p_tenv, const std::string& suite_name = "")
            {
                registerTestEnvironment(file_name, p_tenv, suite_name);
            }
        };
    }

    inline std::string getSummary()
    {
        impl::TestingUnit global_tu;

        for (auto& tu : impl::testing_units)
            for (auto& suite : tu.suites)
                global_tu.addSuite(suite);

        return global_tu.getSummary();
    }

    inline std::string getSummary(const std::string& file_name)
    {
        auto it = std::find_if(impl::testing_units.begin(), impl::testing_units.end(), [file_name](impl::TestingUnit& tu)
        {
            return (tu.file_name == file_name);
        });

        if (it == impl::testing_units.end())
            throw std::runtime_error(std::format("File \"{}\" does not have any associated tests", file_name));

        return it->getSummary();
    }
};

const std::string yunit_suite_name = "";

#define YUNIT_CONCAT(prefix, postfix) prefix##postfix

#define _TEST(name, id)\
namespace yUnit::impl\
{\
    class YUNIT_CONCAT(Test_, id) : public TestEnvironment\
    {\
    public:\
        YUNIT_CONCAT(Test_, id)()\
        {\
            addTest(name, test);\
        }\
        void test();\
    };\
    ::yUnit::impl::TestEnvironmentRegistrar YUNIT_CONCAT(testRegistrar_, id)(std::source_location::current().file_name(), std::make_shared<YUNIT_CONCAT(Test_, id)>(), yunit_suite_name);\
}\
void yUnit::impl::YUNIT_CONCAT(Test_, id)::test()

#define TEST(name) _TEST(name, __COUNTER__)

#define _SUITE(name, id)\
namespace YUNIT_CONCAT(suite_, id)\
{\
    const std::string yunit_suite_name = name;\
}\
namespace YUNIT_CONCAT(suite_, id)

#define SUITE(name) _SUITE(name, __COUNTER__)

#endif
