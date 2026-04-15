#ifndef TESTREPORT_H
#define TESTREPORT_H

#include <vector>
#include <string>
#include <sstream>

struct TestReport
{
private:
    std::vector<std::string> log;
    bool passed = true;
    std::string testName;

public:

    TestReport(const std::string& testName)
        : testName{testName}
    {}

    bool testPassed()
    {
        return passed;
    }

    std::string getSummary()
    {
        std::stringstream summary;

        summary << "Test " << '\"' << testName << '\"' << (passed ? " passed" : " failed") << std::endl;
        
        for (auto it = log.begin(); it != log.end(); ++it)
        {
            summary << '\t' << *it;

            if (it != log.end() - 1)
                summary << std::endl;
        }

        summary.flush();

        return summary.str();
    }

    void logFailedAssertion()
    {
        log.push_back("Assertion failure");
        passed = false;
    }

    void logFailedAssertion(const std::string& msg)
    {
        log.push_back("Assertion failure: " + msg);
        passed = false;
    }
};

#endif