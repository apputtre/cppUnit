#include <iostream>

#include "test.h"

class WasRun;

class TestCase
{
protected:
    void (WasRun::* func)();

public:
    TestCase(void (WasRun::* func)())
        : func{func}
    {}
};

class WasRun : public TestCase
{
private:
    bool wasRun;

public:
    WasRun(void (WasRun::* func)()) : TestCase(func),
        wasRun{false}
    {

    }

    void run()
    {
        ((*this).*func)();
    }

    void testMethod()
    {
        wasRun = true;
    }

    bool getWasRun()
    {
        return wasRun;
    }
};

class TestCaseTest
{
public:
    TestCaseTest()
    {
        testRunning();
    }

    void testRunning()
    {
        WasRun test = WasRun(WasRun::testMethod);
        assert(test.getWasRun() == 0, "Class reports being run before it has been run");
        test.run();
        assert(test.getWasRun() == 1, "Class reports not being after it has been run");
    }
};

int main()
{
    TestCaseTest testCaseTest;

    return 0;
}