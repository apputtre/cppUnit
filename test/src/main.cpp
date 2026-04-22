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

#define EXPECTED_OUTPUT_DIR "../test_outputs"
#define TAB_WIDTH 4

std::string checkOutput(const std::string& actual_output, const std::string& expected_output_file);
std::string visualizeWhitespace(std::string str);
std::string getFileContents(const std::string& path);
std::string replaceSpaces(const std::string& str);

int main()
{
    std::cout << "Running tests" << std::endl;

    {
        // Basic assertions

        TestEnvironment tenv = Test1();

        std::string summary = tenv.getSummary();

        std::string report = checkOutput(summary, "test_1.txt");

        if (report != "")
        {
            std::cout << "Test 1 failed\n";
            std::cout << report << std::endl;
        }
    }

    {
        // Multiple suites

        TestEnvironment tenv = Test2();

        std::string summary = tenv.getSummary();

        std::string report = checkOutput(summary, "test_2.txt");

        if (report != "")
        {
            std::cout << "Test 2 failed\n";
            std::cout << report << std::endl;
        }
    }

    {
        // assertEq, assertNeq

        TestEnvironment tenv = Test3();

        std::string summary = tenv.getSummary();

        std::string report = checkOutput(summary, "test_3.txt");

        if (report != "")
        {
            std::cout << "Test 3 failed\n";
            std::cout << report << std::endl;
        }
    }

    {
        // assertGtEq, assertLtEq

        TestEnvironment tenv = Test5();

        std::string summary = tenv.getSummary();

        std::string report = checkOutput(summary, "test_5.txt");

        if (report != "")
        {
            std::cout << "Test 5 failed\n";
            std::cout << report << std::endl;
        }
    }

    {
        // Default suite

        TestEnvironment tenv = Test6();

        std::string summary = tenv.getSummary();

        std::string report = checkOutput(summary, "test_6.txt");

        if (report != "")
        {
            std::cout << "Test 6 failed\n";
            std::cout << report << std::endl;
        }
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