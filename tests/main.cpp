#include <iostream>

#include "test.h"

class TestCase
{
    public:
        void setUp();
        void tearDown();

        virtual bool run() = 0;
    private:
};

class TestTestCase : TestCase
{
public:
    bool run() override
    {
        return true;
    }
};

int main()
{
    TestTestCase test;

    if (test.run())
        std::cout << "Test passed\n";
    else
        std::cout << "Test failed\n";

    return 0;
}