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
    std::vector<std::shared_ptr<std::function<void(TestEnvironment&)>>> tests;

public:
    TestSuite(const std::string& name)
        : name {name}
    {}
};

#endif