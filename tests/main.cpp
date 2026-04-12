#include <iostream>

#include "test.h"

class TestCase
{
    public:
        void setUp();
        void tearDown();

        virtual bool test() = 0;
    private:
};

class TwoPlusTwoEqualsFive : public TestCase
{
public:
    bool test() override
    {
        return 2 + 2 == 5;
    }
};

class TwoPlusTwoEqualsFour : public TestCase
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
        if (!test.test())
            std::cout << "Test failed\n";
        else
            std::cout << "Test passed\n";
    }
   
    {
        TwoPlusTwoEqualsFour test;

        std::cout << "Running test 2+2=4?\n";
        if (!test.test())
            std::cout << "Test failed\n";
        else
            std::cout << "Test passed\n";    
    }

    return 0;
}