#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <format>
#include <math.h>

#include "TestSuiteReport.h"
#include "TestEnvironment.h"

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

        std::cout << tenv.getSummary();
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