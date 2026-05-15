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
        inline std::vector<std::unique_ptr<TestEnvironment>> testEnvs;

        inline TestEnvironment globalTestEnv;

        template<std::derived_from<TestEnvironment> T>
        inline void registerTestEnvironment(std::unique_ptr<T>& p_tenv)
        {
            testEnvs.emplace_back(p_tenv.release());
        }

        inline void runTests()
        {
            for (auto& tenv : impl::testEnvs)
            {
                tenv->runTests();
                impl::globalTestEnv.combineReports(*tenv);
            }
        }

        inline void clearTests()
        {
            impl::testEnvs.clear();
        }

        template<std::derived_from<TestEnvironment> T>
        struct TestEnvironmentRegistrar
        {
            TestEnvironmentRegistrar(std::unique_ptr<T>&& p_tenv)
            {
                registerTestEnvironment(p_tenv);
            }

            TestEnvironmentRegistrar(std::unique_ptr<T>& p_tenv) : TestEnvironmentRegistrar(std::move(p_tenv))
            {}
        };
    }

    inline TestEnvironment& getGlobalTestEnvironment()
    {
        return impl::globalTestEnv;
    }

    inline std::string getSummary()
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