#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <format>

#include "TestSuiteReport.h"
#include "TestEnvironment.h"

int main()
{
    std::cout << std::endl;

    {
        std::cout << "=== TEST 1 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginTest("2+2=5?");
        tenv.assert(2 + 2 == 5, "Two plus two does not equal 5!");

        tenv.beginTest("2+2=4?");
        tenv.assert(2 + 2 == 4, "Two plus two does not equal 4!");

        tenv.beginTest("2+2=7?");
        tenv.assert(2 + 2 == 7, "Two plus two does not equal 7!");

        std::cout << tenv.getSummary();
    }

    std::cout << std::endl;

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

    std::cout << std::endl;

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

    std::cout << std::endl;

    {
        std::cout << "=== TEST 4 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginSuite("Test suite");

        tenv.beginTest("Assertion without message");
        tenv.assert(false);

        std::cout << tenv.getSummary();
    }

    std::cout << std::endl;

    {
        std::cout << "=== TEST 5 ===" << std::endl;
        TestEnvironment tenv;

        tenv.beginSuite("assertEq");

        tenv.beginTest();
        tenv.assertEq(2+2, 5, "Two plus two does not equal five!");

        std::cout << tenv.getSummary();
    }

    return 0;
}