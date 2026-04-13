#include <iostream>

#include "test.h"

struct TestReport
{
    bool passed;
};

class TestCase
{
public:
    bool run()
    {
        setUp();
        bool result = test();
        tearDown();
        return result;
    }

    virtual void setUp() {}
    virtual void tearDown() {}

    virtual bool test() = 0;
private:
};

class TestTestCase : public TestCase
{
public:
    void setUp()
    {
        std::cout << "setUp called\n";
    }

    void tearDown()
    {
        std::cout << "tearDown called\n";
    }
};

class TwoPlusTwoEqualsFive : public TestTestCase
{
public:
    bool test() override
    {
        return 2 + 2 == 5;
    }
};

class TwoPlusTwoEqualsFour : public TestTestCase
{
public:
    bool test() override
    {
        return 2 + 2 == 4;
    }
};

int main()
{

    {
        TwoPlusTwoEqualsFive test;

        std::cout << "Running test 2+2=5?\n";
        if (!test.run())
            std::cout << "Test failed\n";
        else
            std::cout << "Test passed\n";
    }
   
    {
        TwoPlusTwoEqualsFour test;

        std::cout << "Running test 2+2=4?\n";
        if (!test.run())
            std::cout << "Test failed\n";
        else
            std::cout << "Test passed\n";    
    }

    return 0;
}