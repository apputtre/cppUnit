#ifndef TESTGTEQLTEQ_H
#define TESTGTEQLTEQ_H


#include "yUnit.h"

#include "ComparableButNotPrintable.h"
#include "ComparableAndPrintable.h"

TEST("assertGtEq with printable arguments 1")
{
    assertGtEq(1, 2, "One is not greater than or equal to two!");
}

TEST("assertGtEq with printable arguments 2")
{
    assertGtEq('Z', 'A', "Z is not greater than or equal to A!");
}

TEST("assertGtEq with printable arguments 3")
{
    assertGtEq(2.5, 3);
}

TEST("assertGtEq with printable arguments 4")
{
    assertGtEq(2.5, 2.5, "2.5 is not greater than or equal to 2.5!");
}

TEST("assertGtEq with non-printable arguments")
{
    ComparableButNotPrintable comp_not_print_1{1};
    ComparableButNotPrintable comp_not_print_2{2};

    assertGtEq(comp_not_print_1, comp_not_print_2);
}

TEST("assertGtEq with arguments with custom print operation")
{
    ComparableAndPrintable comp_and_print_1{1};
    ComparableAndPrintable comp_and_print_2{2};

    assertGtEq(comp_and_print_1, comp_and_print_2);
}

TEST("assertLtEq with printable arguments 1")
{
    assertLtEq(2, 1, "Two is not less than or equal to one!");
}

TEST("assertLtEq with printable arguments 2")
{
    assertLtEq('Z', 'A', "Z is not less than or equal to A!");
}

TEST("assertLtEq with printable arguments 3")
{
    assertLtEq(3, 2.5);
}

TEST("assertLt with printable arguments 4")
{
    assertLtEq(2.5, 2.5, "2.5 is not less than or equal to 2.5!");
}

TEST("assertLtEq with non-printable arguments")
{
    ComparableButNotPrintable comp_not_print_1{1};
    ComparableButNotPrintable comp_not_print_2{2};

   assertLtEq(comp_not_print_2, comp_not_print_1);
}

TEST("assertLtEq with arguments with custom print operation")
{
    ComparableAndPrintable comp_and_print_1{1};
    ComparableAndPrintable comp_and_print_2{2};

   assertLtEq(comp_and_print_2, comp_and_print_1);
}

#endif