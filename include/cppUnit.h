#ifndef CPPUNIT_H
#define CPPUNIT_H

#include <vector>
#include <sstream>
#include <string>
#include <regex>
#include <source_location>

#include "TestEnvironment.h"
#include "TestingUnit.h"

namespace cppUnit
{
    namespace impl
    {
        inline std::vector<std::pair<std::string, TestingUnit>> testing_units;

        decltype(impl::testing_units)::iterator getTestingUnit(const std::string& file_name)
        {
            auto it = std::find_if(impl::testing_units.begin(), impl::testing_units.end(), [file_name](auto& p)
            {
                return (p.first == file_name);
            });

            return it;
        }

        template<std::derived_from<TestEnvironment> T>
        inline void registerTestEnvironment(const std::string& file_name, std::shared_ptr<T> p_tenv, const std::string& suite_name)
        {
            auto it = getTestingUnit(file_name);

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
        auto it = impl::getTestingUnit(file_name);

        if (it == impl::testing_units.end())
            throw std::runtime_error(std::format("File \"{}\" does not have any associated tests", file_name));

        return it->second.getSummary();
    }
};

const std::string yunit_suite_name = "";

#define YUNIT_CONCAT(prefix, postfix) prefix##postfix

#define _TEST(name, id)\
namespace cppUnit::impl\
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
    ::cppUnit::impl::TestEnvironmentRegistrar YUNIT_CONCAT(testRegistrar_, id)(std::source_location::current().file_name(), std::make_shared<YUNIT_CONCAT(Test_, id)>(), yunit_suite_name);\
}\
void cppUnit::impl::YUNIT_CONCAT(Test_, id)::test()

#define TEST(name) _TEST(name, __COUNTER__)

#define _SUITE(name, id)\
namespace YUNIT_CONCAT(suite_, id)\
{\
    const std::string yunit_suite_name = name;\
}\
namespace YUNIT_CONCAT(suite_, id)

#define SUITE(name) _SUITE(name, __COUNTER__)

#define _FIXTURE(id)\
namespace YUNIT_CONCAT(Fixture_, id)\
{\
    namespace cppUnit::impl\
    {\
        class YUNIT_CONCAT(Fixture_, id) : public TestEnvironment {};\
    }\
    std::shared_ptr<TestEnvironment> fixture = std::make_shared<cppUnit::impl::YUNIT_CONCAT(Fixture_, id)>();\
    ::cppUnit::impl::TestEnvironmentRegistrar YUNIT_CONCAT(testRegistrar_, id)(std::source_location::current().file_name(), fixture, yunit_suite_name);\
}\
namespace YUNIT_CONCAT(Fixture_, id)

#define FIXTURE() _FIXTURE(__COUNTER__)

#define SETUP()\
class FixtureSetUp : public std::remove_reference<decltype(*fixture)>::type\
{\
public:\
    FixtureSetUp()\
    {\
        fixture->setSetUp(setUpImpl);\
    }\
    void setUpImpl();\
};\
FixtureSetUp fixtureSetUp;\
void FixtureSetUp::setUpImpl()

#define TEARDOWN()\
class FixtureTearDown : public std::remove_reference<decltype(*fixture)>::type\
{\
public:\
    FixtureTearDown()\
    {\
        fixture->setTearDown(tearDownImpl);\
    }\
    void tearDownImpl();\
};\
FixtureTearDown fixtureTearDown;\
void FixtureTearDown::tearDownImpl()

#define _FTEST(name, id)\
class YUNIT_CONCAT(FixtureTest_, id) : public std::remove_reference<decltype(*fixture)>::type\
{\
public:\
    YUNIT_CONCAT(FixtureTest_, id)()\
    {\
        fixture->addTest(name, test);\
    }\
    void test();\
};\
YUNIT_CONCAT(FixtureTest_, id) YUNIT_CONCAT(fixtureTest_, id);\
void YUNIT_CONCAT(FixtureTest_, id)::test()

#define FTEST(name) _FTEST(name, __COUNTER__)

#endif
