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
    std::cout << "Hello world\n";

    return 0;
}