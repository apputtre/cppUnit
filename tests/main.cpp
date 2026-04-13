#include <string>
#include <sstream>
#include <iostream>
#include <vector>

struct TestReport
{
    bool passed = true;

    std::vector<std::string> log;

    std::string getSummary()
    {
        std::stringstream summary;

        for (const std::string& entry : log)
            summary << entry << std::endl;

        summary.flush();

        return summary.str();
    }
};

class TestCase
{
public:
    TestCase(const std::string& name)
        : name{name}
    {}

    TestReport run()
    {
        this->report = TestReport {};
        setUp();
        test();
        tearDown();
        return report;
    }

    virtual void setUp() {}
    virtual void tearDown() {}

    virtual void test() = 0;

protected:
    std::string name;
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
    TestTestCase(const std::string& name) : TestCase(name)
    {}

    TestReport run()
    {
        std::cout << "Running test " << this->name << std::endl;

        return TestCase::run();
    }

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
    TwoPlusTwoEqualsFive(const std::string& name) : TestTestCase(name)
    {}

    void test() override
    {
        assert(2 + 2 == 5);
    }
};

class TwoPlusTwoEqualsFour : public TestTestCase
{
public:
    TwoPlusTwoEqualsFour(const std::string& name) : TestTestCase(name)
    {}

    void test() override
    {
        assert(2 + 2 == 4);
    }
};

int main()
{

    {
        TwoPlusTwoEqualsFive test("2+2=5?");

        TestReport report = test.run();
        if (report.passed)
            std::cout << "Test passed\n";
        else
            std::cout << "Test failed\n";
    }
   
    {
        TwoPlusTwoEqualsFour test("2+2=4?");

        TestReport report = test.run();
        if (report.passed)
            std::cout << "Test passed\n";
        else
            std::cout << "Test failed\n";    
    }

    std::cout << "\n";

    {
        TestReport report;

        report.log.push_back("This is a test (first entry)"); 
        report.log.push_back("Another entry (second entry)");

        std::cout << report.getSummary() << std::endl;

    }

    return 0;
}