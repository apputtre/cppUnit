#include <iostream>

#include "test.h"

class TestCase
{
    public:
        void setUp();
        bool run();
        void tearDown();
    private:
};

int main()
{
    std::cout << "Hello world\n";

    return 0;
}