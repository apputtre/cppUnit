#ifndef TESTEQNEQ_H
#define TESTEQNEQ_H

#include "TestEnvironment.h" 
#include "ComparableButNotPrintable.h"
#include "ComparableAndPrintable.h"

#include <math.h>

TestEnvironment testEqNeq()
{
    TestEnvironment tenv;

    ComparableButNotPrintable comp_not_print_1{1};
    ComparableButNotPrintable comp_not_print_2{2};
    ComparableButNotPrintable comp_not_print_3{1};

    ComparableAndPrintable comp_and_print_1{1};
    ComparableAndPrintable comp_and_print_2{2};
    ComparableAndPrintable comp_and_print_3{1};

    tenv.beginSuite("assertEq");

    tenv.beginTest("assertEq with printable arguments 1");
    tenv.assertEq(2+2, 5, "Two plus two does not equal five!");

    tenv.beginTest("assertEq with printable arguments 2");
    tenv.assertEq(std::cos(0), 1, "cos(0) is not 1!");

    tenv.beginTest("assertEq with printable arguments 3");
    tenv.assertEq(std::string("War"), std::string("Peace"), "War is not peace!");

    tenv.beginTest("assertEq with printable arguments 4");
    tenv.assertEq(true, false);

    tenv.beginTest("assertEq with non-printable arguments");
    tenv.assertEq(comp_not_print_1, comp_not_print_2);

    tenv.beginTest("assertEq with arguments with custom print operation");
    tenv.assertEq(comp_and_print_1, comp_and_print_2);

    tenv.beginSuite("assertNeq");

    tenv.beginTest("assertNeq with printable arguments 1");
    tenv.assertNeq(2+2, 5, "Two plus two equals five!");

    tenv.beginTest("assertNeq with printable arguments 2");
    tenv.assertNeq(std::cos(0), 1, "cos(0) is 1!");

    tenv.beginTest("assertNeq with printable arguments 3");
    tenv.assertNeq(std::string("War"), std::string("Peace"), "War is peace!");

    tenv.beginTest("assertNeq with printable arguments 4");
    tenv.assertNeq(true, true);

    tenv.beginTest("assertNeq with non-printable arguments");
    tenv.assertNeq(comp_not_print_1, comp_not_print_3);

    tenv.beginTest("assertNeq with arguments with custom print operation");
    tenv.assertNeq(comp_and_print_1, comp_and_print_3);

    return tenv;
}

#endif