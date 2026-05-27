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

#include "testutils.h"
#include "cppUnit.h"

#include "TestBasicAssertions.h"
#include "TestSuites.h"
#include "TestEqNeq.h"
#include "TestGtEqLtEq.h"
#include "TestGtLt.h"
#include "TestSuites.h"
#include "TestFixtures.h"
#include "TestEmptySummary.h"

bool all_tests_passed = true;

void runTest(const std::string& test_file, const std::string& expected_output_file);

int main()
{
    std::cout << "Running tests...\n";

    runTest("include/TestBasicAssertions.h", "BasicAssertions.txt");
    runTest("include/TestSuites.h", "Suites.txt");
    runTest("include/TestEqNeq.h", "EqNeq.txt");
    runTest("include/TestGtLt.h", "GtLt.txt");
    runTest("include/TestGtEqLtEq.h", "GtEqLtEq.txt");
    runTest("include/TestSuites.h", "Suites.txt");
    runTest("include/TestFixtures.h", "Fixtures.txt");
    runTest("include/TestEmptySummary.h", "EmptySummary.txt");

    if (all_tests_passed)
        std::cout << "All tests passed.\n";

    return 0;
}

void runTest(const std::string& test_file, const std::string& expected_output_file)
{
    std::string summary = cppUnit::getSummary(test_file);

    std::string report = testutils::checkOutput(summary, expected_output_file);

    if (report != "")
    {
        std::cout << "Test " << test_file << " failed" << std::endl;;
        std::cout << report << std::endl;

        all_tests_passed = false;
    }
}