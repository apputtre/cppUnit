#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>

#include "TestEnvironment.h"

class TestSuite
{
private:
    const std::string name;
    std::vector<void(TestSuite::*)(TestEnvironment&)> tests;

public:
    TestSuite(const std::string& name)
        : name {name}
    {
        addTest(Test);
    }

    void addTest(void(TestSuite::*test)(TestEnvironment&))
    {
        tests.push_back(test);
    }

    void run(TestEnvironment& tenv)
    {
        tenv.beginSuite(name);

        for (auto test : tests)
            (*this.*test)(tenv);

        tenv.endSuite();
    }

    void Test(TestEnvironment& tenv) {tenv.beginTest(); tenv.assert(false);}
};

#endif