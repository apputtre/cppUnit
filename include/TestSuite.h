#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <vector>
#include <string>

#include "TestCase.h"
#include "TestSuiteReport.h"

class TestSuite
{
private:
    std::vector<std::shared_ptr<TestCase>> tests;
    std::string name;
    TestSuiteReport report;

public:
    TestSuite(const std::string name)
        : name{name}, report{name}
    {};

    template <typename T>
    void add(const T& test)
    {
        static_assert(std::is_base_of<TestCase, T>::value, "T must derive from TestCase");

        this->tests.emplace_back(std::make_shared<T>(test));
    }

    TestSuiteReport run()
    {
        for (std::shared_ptr<TestCase> test : tests)
            report.log(test->run());
        
        return report;
    }
};

#endif