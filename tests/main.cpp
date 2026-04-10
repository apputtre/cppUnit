#include <iostream>

#include "test.h"

class WasRun
{
private:
    void (WasRun::* func)();
    bool wasRun;

public:
    WasRun(void (WasRun::* func)())
        : func{func}, wasRun{false}
    {}

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

void t()
{

}

int main()
{
    WasRun test(&WasRun::testMethod);
    assert(test.getWasRun() == 0, "Class reports being run before it has been run");
    test.run();
    assert(test.getWasRun() == 1, "Class reports not being after it has been run");

    return 0;
}