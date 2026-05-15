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

/*
#define _BEGIN_SUITE(name, unique_name)\
namespace yUnit::impl\
{\
    struct unique_name\
    {\
        unique_name()\
        {\
            yUnit::getGlobalTestEnvironment().beginSuite(name);\
        }\
    };\
    unique_name beginSuite;\
}

#define BEGIN_SUITE(suite_name)\
namespace yUnit::impl\
{\
    struct BeginSuite_##__COUNTER__\
    {\
        BeginSuite_##__COUNTER__()\
        {\
            yUnit::getGlobalTestEnvironment().beginSuite(suite_name);\
        }\
    };\
    BeginSuite_##__COUNTER__ beginSuite_##__COUNTER__;\
}

#define END_SUITE()\
namespace yUnit::impl\
{\
    struct EndSuite_##__COUNTER__\
    {\
        EndSuite_##__COUNTER__()\
        {\
            yUnit::getGlobalTestEnvironment().endSuite();\
        }\
    };\
    EndSuite_##__COUNTER__ endSuite_##__COUNTER__;\
}
*/

#endif