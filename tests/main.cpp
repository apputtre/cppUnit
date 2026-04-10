#include <iostream>

#include "test.h"

class WasRun
{
private:
    std::string name;
    bool wasRun;

public:

    WasRun(const std::string& name)
        : name{name}, wasRun{false}
    {}

    void testMethod()
    {
        wasRun = true;
    }

    std::string getName()
    {
        return name;
    }

    bool getWasRun()
    {
        return wasRun;
    }
};

int main()
{
    WasRun test("testMethod");
    assert(test.getWasRun() == 0, "Class reports being run before it has been run");
    test.testMethod();
    assert(test.getWasRun() == 1, "Class reports not being after it has been run");

    return 0;
}