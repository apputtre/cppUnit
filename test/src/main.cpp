#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <format>
#include <fstream>
#include <algorithm>
#include <ios>
#include <ostream>

#include "TestSuiteReport.h"
#include "TestEnvironment.h"
#include "Test1.h"
#include "Test2.h"
#include "Test3.h"
#include "Test4.h"
#include "Test5.h"
#include "Test6.h"
#include "Test7.h"
#include "Test8.h"
#include "Test9.h"
#include "Test10.h"
#include "Test11.h"

#define EXPECTED_OUTPUT_DIR "../test_outputs"
#define TAB_WIDTH 4

std::string checkOutput(const std::string& actual_output, const std::string& expected_output_file);
std::string visualizeWhitespace(std::string str);
std::string getFileContents(const std::string& path);
std::string replaceSpaces(const std::string& str);

void runTest(TestEnvironment& tenv, const std::string& expected_output_file);
void runTest(const std::string& summary, const std::string& expected_output_file);

int main()
{
    std::cout << "Running tests" << std::endl;

    {
        // Basic assertions
        auto tenv = Test1();
        runTest(tenv, "test_1.txt");
    }

    {
        // Multiple suites
        auto tenv = Test2();
        runTest(tenv, "test_2.txt");
    }

    {
        // assertEq, assertNeq
        auto tenv = Test3();
        runTest(tenv, "test_3.txt");
    }

    {
        // assertGtEq, assertLtEq
        auto tenv = Test5();
        runTest(tenv, "test_5.txt");
    }

    {
        // Default suite
        auto tenv = Test6();
        runTest(tenv, "test_6.txt");
    }

    {
        // endTest()
        auto tenv = Test7();
        runTest(tenv, "test_7.txt");    
    }

    {
        // endSuite()
        auto tenv = Test8();
        runTest(tenv, "test_8.txt");
    }

    {
        // TestSuite
        auto tenv = yUnit::getSummary("Test9");
        runTest(tenv, "test_9.txt");
    }

    {
        // TestSuite
        auto tenv = yUnit::getSummary("Test10");
        runTest(tenv, "test_10.txt");
    }

    {
        // skip
        auto tenv = yUnit::getSummary("Test11");
        runTest(tenv, "test_11.txt");
    }

    return 0;
}

std::string checkOutput(const std::string& actual_output, const std::string& expected_output_file)
{
    std::stringstream report;

    std::string expected_output = replaceSpaces(getFileContents(expected_output_file));

    if (actual_output == expected_output)
        return "";
    
    report << "=== ACTUAL ===" << std::endl;
    report << visualizeWhitespace(actual_output) << std::endl;
    report << "=== EXPECTED ===" << std::endl;
    report << visualizeWhitespace(expected_output) << std::endl;

    std::stringstream ss_actual(visualizeWhitespace(actual_output));
    std::stringstream ss_expected(visualizeWhitespace(expected_output));
    int i = 0;
    do
    {
        std::string line_actual = "";

        if (!ss_actual.eof())
            getline(ss_actual, line_actual);

        std::string line_expected = "";

        if (!ss_expected.eof())
            getline(ss_expected, line_expected);

        if (line_expected != line_actual)
        {
            report << "=== LINE " << i + 1 << " ===" << std::endl;

            size_t pos = 0;
            while (line_expected[pos] == line_actual[pos])
                ++pos;
            
            report << line_actual << std::endl;
            report << line_expected << std::endl;

            for (int j = 0; j < (int) pos; ++j)
                report << " ";
            report << "^HERE (" << pos << ")" << std::endl;
        }
        
        ++i;

    } while (!ss_actual.eof() && !ss_expected.eof());

    report.flush();

    return report.str();
}

std::string visualizeWhitespace(std::string str)
{
    std::stringstream ss(str);

    for (char& c : str)
        if (c == '\t')
            ss << "[\\t ]";
        else if (c == '\n')
            ss << "[\\n]\n";
        else
            ss << c;

    return ss.str();
}

std::string getFileContents(const std::string& filename)
{
    std::ifstream file(std::format("{}/{}", EXPECTED_OUTPUT_DIR, filename));

    if (!file)
    {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::stringstream contents;

    contents << file.rdbuf();

    return contents.str();
}

std::string replaceSpaces(const std::string& str)
{
    std::stringstream ss_out;

    std::string buf;
    std::string tab_replacement;

    for (int i = 0; i < TAB_WIDTH; ++i)
        tab_replacement += " ";

    for (int i = 0; i < (int) str.length(); ++i)
    {
        for (int j = 0; j < TAB_WIDTH && i + j < (int) str.length(); ++j)
            buf += str[i + j];

        if (buf == tab_replacement)
        {
            ss_out << '\t';
            i += buf.size() - 1;
        }
        else
            ss_out << str[i];
        
        buf.erase();
    }

    return ss_out.str();
}

void runTest(TestEnvironment& tenv, const std::string& expected_output_file)
{
    std::string summary = tenv.getSummary();

    runTest(summary, expected_output_file);
}

void runTest(const std::string& summary, const std::string& expected_output_file)
{
    std::string report = checkOutput(summary, expected_output_file);

    if (report != "")
    {
        std::cout << "Test 1 failed\n";
        std::cout << report << std::endl;
    }
}