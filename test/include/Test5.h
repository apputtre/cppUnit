#ifndef TEST5_H
#define TEST5_H

#include "TestEnvironment.h"
#include "ComparableButNotPrintable.h"
#include "ComparableAndPrintable.h"

TestEnvironment Test5()
{
    TestEnvironment tenv;

    ComparableButNotPrintable comp_not_print_1{1};
    ComparableButNotPrintable comp_not_print_2{2};

    ComparableAndPrintable comp_and_print_1{1};
    ComparableAndPrintable comp_and_print_2{2};

    tenv.beginSuite("assertGtEq");

    tenv.beginTest("assertGtEq with printable arguments 1");
    tenv.assertGtEq(1, 2, "One is not greater than or equal to two!");

    tenv.beginTest("assertGtEq with printable arguments 2");
    tenv.assertGtEq('Z', 'A', "Z is not greater than or equal to A!");

    tenv.beginTest("assertGtEq with printable arguments 3");
    tenv.assertGtEq(2.5, 3);

    tenv.beginTest("assertGtEq with non-printable arguments");
    tenv.assertGtEq(comp_not_print_1, comp_not_print_2);

    tenv.beginTest("assertGtEq with arguments with custom print operation");
    tenv.assertGtEq(comp_and_print_1, comp_and_print_2);

    /*
    tenv.beginSuite("assertLt");

    tenv.beginTest("assertLt with printable arguments 1");
    tenv.assertLt(2, 1, "Two is not less than one!");

    tenv.beginTest("assertLt with printable arguments 2");
    tenv.assertLt('A', 'Z', "A is not less than Z!");

    tenv.beginTest("assertLt with printable arguments 3");
    tenv.assertLt(3, 2.5);

    tenv.beginTest("assertLt with non-printable arguments");
    tenv.assertLt(comp_not_print_2, comp_not_print_1);

    tenv.beginTest("assertLt with arguments with custom print operation");
    tenv.assertLt(comp_and_print_2, comp_and_print_1);
    */

    return tenv;
}

#endif