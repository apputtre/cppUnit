#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <string>

class TestSuite
{
private:
    const std::string name;

public:
    TestSuite(const std::string& name)
        : name {name}
    {}
};

#endif