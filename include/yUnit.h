#ifndef YUNIT_H
#define YUNIT_H

#include <vector>
#include <sstream>
#include <string>

#include "TestEnvironment.h"

namespace yUnit
{
    namespace impl
    {
        std::vector<std::shared_ptr<TestSuiteReport>> suiteReports;
    }

    std::string getSummary()
    {
        std::stringstream summary;

        for (auto report : impl::suiteReports)
            if (!report->allTestsPassed())
                summary << report->getSummary();
        
        summary.flush();
        return summary.str();
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
            impl::suiteReports.push_back(getLastSuiteReport());\
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