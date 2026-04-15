#ifndef TESTREPORT_H
#define TESTREPORT_H

#include <vector>
#include <string>
#include <sstream>
#include <source_location>

#include "AssertionFailureReport.h"

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
            std::stringstream entry(*it);

            std::string line;
            for (std::getline(entry, line); !entry.eof(); std::getline(entry, line))
                summary << '\t' << line << std::endl;
            summary << '\t' << line;

            if (it != log.end() - 1)
                summary << std::endl;
        }

        summary.flush();

        return summary.str();
    }

    void logFailedAssertion(const AssertionFailureReport& report)
    {
        log.push_back(report.getSummary());
        passed = false;
    }
};

#endif