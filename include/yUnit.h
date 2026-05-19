#ifndef YUNIT_H
#define YUNIT_H

#include <vector>
#include <sstream>
#include <string>
#include <regex>
#include <source_location>

#include "TestEnvironment.h"
#include "TestingUnit.h"

namespace yUnit
{
    namespace impl
    {
        inline std::vector<std::pair<std::string, TestingUnit>> testing_units;

        template<std::derived_from<TestEnvironment> T>
        inline void registerTestEnvironment(const std::string& file_name, std::shared_ptr<T> p_tenv, const std::string& suite_name)
        {
            auto it = std::find_if(testing_units.begin(), testing_units.end(), [file_name](auto& p)
            {
                return (p.first == file_name);
            });

            if (it != testing_units.end())
            {
                it->second.addTestEnvironment(p_tenv, suite_name);
            }
            else
            {
                testing_units.emplace_back(std::pair {file_name, TestingUnit {file_name}});
                testing_units.back().second.addTestEnvironment(p_tenv, suite_name);
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
        TestingUnit global_tu;

        for (auto& it : impl::testing_units)
            global_tu.combineReports(it.second);

        return global_tu.getSummary();
    }

    inline std::string getSummary(const std::string& file_name)
    {
        auto it = std::find_if(impl::testing_units.begin(), impl::testing_units.end(), [file_name](auto& p)
        {
            return (p.first == file_name);
        });

        if (it == impl::testing_units.end())
            throw std::runtime_error(std::format("File \"{}\" does not have any associated tests", file_name));

        return it->second.getSummary();
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
