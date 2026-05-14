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
#include "TestSuiteReport.h"
#include "TestEnvironment.h"
#include "TestBasicAssertions.h"
#include "TestSuitelessTests.h"
#include "TestEndSuite.h"
#include "TestEndTest.h"
#include "TestEqNeq.h"
#include "TestGtLt.h"
#include "TestGtEqLtEq.h"
#include "TestRunTest.h"
#include "TestSuites.h"
#include "TestCombineReports.h"
#include "TestGlobalTestEnvironment.h"
#include "TestGlobalGetSummary.h"
#include "TestClear.h"

void runTest(const std::string& test_name, TestEnvironment tenv, const std::string& expected_output_file);
void runTest(const std::string& test_name, const std::string& summary, const std::string& expected_output_file);

int main()
{
    std::cout << "Running tests" << std::endl;

    runTest("Basic assertions", testBasicAssertions(), "BasicAssertions.txt");
    runTest("Suites", testSuites(), "Suites.txt");
    runTest("assertEq, assertNeq", testEqNeq(), "EqNeq.txt");
    runTest("assertGt, assertLt", testGtLt(), "GtLt.txt");
    runTest("assertGtEq, assertLtEq", testGtEqLtEq(), "GtEqLtEq.txt");
    runTest("Suiteless tests", testSuitelessTests(), "SuitelessTests.txt");
    runTest("endTest", testEndTest(), "EndTest.txt");
    runTest("endSuite", testEndSuite(), "EndSuite.txt");
    runTest("runTest", testRunTest(), "RunTest.txt");
    runTest("Combine Reports", testCombineReports(), "CombineReports.txt");
    runTest("TestSummary.clear()", testClear(), "Clear.txt");
    runTest("Global test environment()", testGlobalTestEnvironment(), "GlobalTestEnvironment.txt");
    runTest("Global getSummary()", testGlobalGetSummary(), "GlobalGetSummary.txt");

    return 0;
}

void runTest(const std::string& test_name, TestEnvironment tenv, const std::string& expected_output_file)
{
    std::string summary = tenv.getSummary();
    runTest(test_name, summary, expected_output_file);
}

void runTest(const std::string& test_name, const std::string& summary, const std::string& expected_output_file)
{
    std::string report = testutils::checkOutput(summary, expected_output_file);

    if (report != "")
    {
        std::cout << "Test " << test_name << " failed" << std::endl;;
        std::cout << report << std::endl;
    }
}