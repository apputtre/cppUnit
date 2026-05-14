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
        std::vector<std::unique_ptr<TestEnvironment>> testEnvs;

        TestEnvironment globalTestEnv;

        template<std::derived_from<TestEnvironment> T>
        void registerTestEnvironment(std::unique_ptr<T>& p_tenv)
        {
            testEnvs.emplace_back(std::move(p_tenv));
        }

        void runTests()
        {
            for (std::unique_ptr<TestEnvironment>& tenv : impl::testEnvs)
            {
                tenv->runTests();
                impl::globalTestEnv.combineReports(*tenv);
            }
        }

        void clearTests()
        {
            impl::testEnvs.clear();
        }
    }

    TestEnvironment& getGlobalTestEnvironment()
    {
        return impl::globalTestEnv;
    }

    std::string getSummary()
    {
        getGlobalTestEnvironment().clear();
        impl::runTests();
        return getGlobalTestEnvironment().getSummary();
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