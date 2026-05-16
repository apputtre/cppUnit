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
        struct Suite
        {
            std::string name;
            std::vector<std::unique_ptr<TestEnvironment>> tests {};

            Suite(const std::string& name)
            {
                this->name = name;
            }
        };

        inline std::vector<std::unique_ptr<TestEnvironment>> suitelessTests;
        inline std::vector<Suite> suites;
        inline bool in_suite = false;

        inline TestEnvironment globalTestEnv;

        template<std::derived_from<TestEnvironment> T>
        inline void registerTestEnvironment(std::unique_ptr<T>& p_tenv)
        {
            std::cout << (in_suite ? "true" : "false") << std::endl;

            if (in_suite)
                suites.back().tests.emplace_back(p_tenv.release());
            else
                suitelessTests.emplace_back(p_tenv.release());
        }

        inline void runTests()
        {
            for (auto& tenv : impl::suitelessTests)
            {
                tenv->runTests();
                impl::globalTestEnv.combineReports(*tenv);
            }

            for (auto& suite : impl::suites)
            {
                for (auto& tenv : suite.tests)
                {
                    tenv->beginSuite(suite.name);
                    tenv->runTests();
                    globalTestEnv.combineReports(*tenv);
                }
            }
        }

        inline void clearTests()
        {
            impl::suitelessTests.clear();
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

/*
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
*/

/*
#define __YUNIT_GET_UNIQUE_NAME(prefix, postfix) prefix##postfix
#define _YUNIT_GET_UNIQUE_NAME(prefix, postfix) __YUNIT_GET_UNIQUE_NAME(prefix, postfix)
#define YUNIT_GET_UNIQUE_NAME(prefix) _YUNIT_GET_UNIQUE_NAME(prefix, __COUNTER__)
*/

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
    TestEnvironmentRegistrar YUNIT_CONCAT(testRegistrar_, id)(std::make_unique<YUNIT_CONCAT(Test_, id)>());\
}\
void yUnit::impl::YUNIT_CONCAT(Test_, id)::test()

#define TEST(name) _TEST(name, __COUNTER__)

#define _BEGIN_SUITE(name, id)\
namespace yUnit::impl\
{\
    struct YUNIT_CONCAT(BeginSuite_, id)\
    {\
        YUNIT_CONCAT(BeginSuite_, id)()\
        {\
            yUnit::impl::in_suite = true;\
            yUnit::impl::suites.push_back(yUnit::impl::Suite{name});\
        }\
    };\
    YUNIT_CONCAT(BeginSuite_, id) YUNIT_CONCAT(beginSuite_, id);\
}

#define BEGIN_SUITE(name) _BEGIN_SUITE(name, __COUNTER__)

#define _END_SUITE(id)
namespace yUnit::impl\
{\
    struct YUNIT_CONCAT(EndSuite_, id)
    {\
        YUNIT_CONCAT(EndSuite_, id)()\
        {\
            yUnit::impl::in_suite = false;
            std::cout << yUnit::impl::in_suite << std::endl;
        }\
    };\
    YUNIT_CONCAT(EndSuite_, id) YUNIT_CONCAT(endSuite_, id);\
}

#define END_SUITE() _END_SUITE(__COUNTER__)

#endif
