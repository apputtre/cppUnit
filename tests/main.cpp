#include <iostream>

struct TestReport
{
    bool passed = true;
};

class TestCase
{
public:
    TestCase()
        : report {}
    {}

    TestReport run()
    {
        setUp();
        test();
        tearDown();
        return report;
    }

    virtual void setUp() {}
    virtual void tearDown() {}

    virtual void test() = 0;

protected:
    TestReport report;

    void assert(bool statement)
    {
        if (!statement)
            report.passed = false;
    }
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
    void test() override
    {
        assert(2 + 2 == 5);
    }
};

class TwoPlusTwoEqualsFour : public TestTestCase
{
public:
    void test() override
    {
        assert(2 + 2 == 4);
    }
};

int main()
{

    {
        TwoPlusTwoEqualsFive test;
        std::cout << "Running test 2+2=5?\n";

        TestReport report = test.run();
        if (report.passed)
            std::cout << "Test passed\n";
        else
            std::cout << "Test failed\n";
    }
   
    {
        TwoPlusTwoEqualsFour test;
        std::cout << "Running test 2+2=4?\n";

        TestReport report = test.run();
        if (report.passed)
            std::cout << "Test passed\n";
        else
            std::cout << "Test failed\n";    
    }

    return 0;
}