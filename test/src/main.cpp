#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <format>
#include <fstream>
#include <algorithm>

#include "TestSuiteReport.h"
#include "TestEnvironment.h"

#define EXPECTED_OUTPUT_DIR "../test_outputs"

std::string checkOutput(std::string actual_output, const std::string& expected_output_file);
std::string visualizeWhitespace(std::string str);

int main()
{
    {
        std::cout << "=== TEST 1 ===" << std::endl;

        TestEnvironment tenv;

        tenv.beginSuite("Basic assertions");

        tenv.beginTest("2+2=5?");
        tenv.assert(2 + 2 == 5, "Two plus two does not equal 5!");

        tenv.beginTest("3-4-5");
        tenv.assert(3*3 + 4*4 == 5*5, "3^2 + 4^2 does not equal 5^2!");

        tenv.beginTest("War is Peace?");
        tenv.assert(std::string("War") == std::string("Peace"), "War is not Peace!");

        std::string summary = tenv.getSummary();

        std::string report = checkOutput(summary, "test_1.txt");

        if (report != "")
            std::cout << report << std::endl;
    }

    {
        std::cout << "=== TEST 2 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginSuite("Basic arithmetic");

        tenv.beginTest("2+2=5?");
        tenv.assert(2 + 2 == 5, "Two plus two does not equal 5!");

        tenv.beginTest("2+2=4?");
        tenv.assert(2 + 2 == 4, "Two plus two does not equal 4!");

        tenv.beginTest("2+2=7?");
        tenv.assert(2 + 2 == 7, "Two plus two does not equal 7!");

        tenv.beginSuite("String comparison");

        tenv.beginTest("abc=def?");
        tenv.assert(std::string("abc") == std::string("def"), "abc does not equal def!");

        tenv.beginTest("abc=abc?");
        tenv.assert(std::string("abc") == std::string("abc"), "abc does not equal abc!");

        std::cout << tenv.getSummary();
    }

    {
        std::cout << "=== TEST 3 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginSuite("First suite");

        tenv.beginTest();
        tenv.assert(false, "false is false!");

        tenv.beginTest();
        tenv.assert(false, "false is false!");

        tenv.beginTest();
        tenv.assert(false, "false is false!");

        tenv.beginSuite("Second suite");

        tenv.beginTest();
        tenv.assert(true, "This test should pass");

        tenv.beginTest();
        tenv.assert(false, "This test should fail");

        std::cout << tenv.getSummary();
    }

    {
        std::cout << "=== TEST 4 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginSuite("Test suite");

        tenv.beginTest("Assertion without message");
        tenv.assert(false);

        std::cout << tenv.getSummary();
    }

    {
        std::cout << "=== TEST 5 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginSuite("assertEq");

        tenv.beginTest("Printable arguments");
        tenv.assertEq(2+2, 5, "Two plus two does not equal five!");

        tenv.beginTest("Non-printable arguments");

        struct A
        {
            int x;

            bool operator==(const A& other) const
            {
                return x == other.x;
            }
        };

        A a1{0};
        A a2{1};
        tenv.assertEq(a1, a2, "a1 does not equal a2!");

        std::cout << tenv.getSummary();
    }
    return 0;
}

std::string checkOutput(std::string actual_output, const std::string& expected_output_file)
{
    std::stringstream report;

    std::ifstream fs(std::format("{}/{}", EXPECTED_OUTPUT_DIR, expected_output_file).c_str());

    if (!fs.good())
        throw std::runtime_error(std::format("Could not open file {}", expected_output_file));

    fs.seekg(0, std::ifstream::end);
    const size_t file_size = fs.tellg();
    fs.seekg(0, std::ifstream::beg);
    
    char* buf = new char[file_size];

    fs.read(buf, file_size);
    std::string expected_output(buf);

    delete[](buf);

    std::stringstream ss;

    for (char& c : actual_output)
        if (c == '\t')
            ss << "    ";
        else
            ss << c;

    actual_output = ss.str();

    if (actual_output != expected_output)
        report << "Test 1 failed" << std::endl;
    
    report << "=== EXPECTED ===" << std::endl;
    report << expected_output << std::endl;
    report << "=== ACTUAL ===" << std::endl;

    /*
    for (char& c : actual_output)
        if (c == '\t')
            ss << "[ \\t]";
        else
            ss << c;
    */

    report << actual_output << std::endl;

    // line-by-line comparison
    std::stringstream ss_expected(expected_output);
    std::stringstream ss_actual(actual_output);
    std::string line_expected, line_actual;
    int i = 0;
    do
    {
        getline(ss_expected, line_expected);
        getline(ss_actual, line_actual);

        if (line_expected != line_actual)
        {
            report << "Lines differ " << i << std::endl;

            size_t pos = 0;
            while (line_expected[pos] == line_actual[pos])
                ++pos;
            
            report << "Lines differ at position " << pos << std::endl;

            report << line_expected << std::endl;
            report << line_actual << std::endl;

            for (int i = 0; i < (int) pos; ++i)
                report << " ";
            report << "^HERE" << std::endl;
        }
        
        ++i;

    } while (line_expected.size() > 0 && line_actual.size() > 0);

    report.flush();

    return report.str();
}

std::string visualizeWhitespace(std::string str)
{

}