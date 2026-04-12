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

int main()
{
    std::cout << "Hello world\n";

    return 0;
}