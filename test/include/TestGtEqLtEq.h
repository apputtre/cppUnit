#ifndef TESTGTEQLTEQ_H
#define TESTGTEQLTEQ_H

#include "TestEnvironment.h"
#include "ComparableButNotPrintable.h"
#include "ComparableAndPrintable.h"

TestEnvironment testGtEqLtEq()
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

    tenv.beginTest("assertGtEq with printable arguments 4");
    tenv.assertGtEq(2.5, 2.5, "2.5 is not greater than or equal to 2.5!");

    tenv.beginTest("assertGtEq with non-printable arguments");
    tenv.assertGtEq(comp_not_print_1, comp_not_print_2);

    tenv.beginTest("assertGtEq with arguments with custom print operation");
    tenv.assertGtEq(comp_and_print_1, comp_and_print_2);

    tenv.beginSuite("assertLtEq");

    tenv.beginTest("assertLtEq with printable arguments 1");
    tenv.assertLtEq(2, 1, "Two is not less than or equal to one!");

    tenv.beginTest("assertLtEq with printable arguments 2");
    tenv.assertLtEq('Z', 'A', "Z is not less than or equal to A!");

    tenv.beginTest("assertLtEq with printable arguments 3");
    tenv.assertLtEq(3, 2.5);

    tenv.beginTest("assertLt with printable arguments 4");
    tenv.assertLtEq(2.5, 2.5, "2.5 is not less than or equal to 2.5!");

    tenv.beginTest("assertLtEq with non-printable arguments");
    tenv.assertLtEq(comp_not_print_2, comp_not_print_1);

    tenv.beginTest("assertLtEq with arguments with custom print operation");
    tenv.assertLtEq(comp_and_print_2, comp_and_print_1);

    return tenv;
}

#endif