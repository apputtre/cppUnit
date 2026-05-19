#ifndef TESTGTLT_H
#define TESTGTLT_H

#include "yUnit.h"

#include "ComparableButNotPrintable.h"
#include "ComparableAndPrintable.h"

TEST("assertGt with printable arguments 1")
{
    assertGt(1, 2, "One is not greater than two!");
}

TEST("assertGt with printable arguments 2")
{
    assertGt('Z', 'A', "Z is not greater than A!");
}

TEST("assertGt with printable arguments 3")
{
    assertGt(2.5, 3);
}

TEST("assertGt with non-printable arguments")
{
    ComparableButNotPrintable comp_not_print_1{1};
    ComparableButNotPrintable comp_not_print_2{2};

    assertGt(comp_not_print_1, comp_not_print_2);
}

TEST("assertGt with arguments with custom print operation")
{
    ComparableAndPrintable comp_and_print_1{1};
    ComparableAndPrintable comp_and_print_2{2};

    assertGt(comp_and_print_1, comp_and_print_2);
}

TEST("assertLt with printable arguments 1")
{
    assertLt(2, 1, "Two is not less than one!");
}

TEST("assertLt with printable arguments 2")
{
    assertLt('A', 'Z', "A is not less than Z!");
}

TEST("assertLt with printable arguments 3")
{
    assertLt(3, 2.5);
}

TEST("assertLt with non-printable arguments")
{
    ComparableButNotPrintable comp_not_print_1{1};
    ComparableButNotPrintable comp_not_print_2{2};

    assertLt(comp_not_print_2, comp_not_print_1);
}

TEST("assertLt with arguments with custom print operation")
{
    ComparableAndPrintable comp_and_print_1{1};
    ComparableAndPrintable comp_and_print_2{2};

    assertLt(comp_and_print_2, comp_and_print_1);
}

#endif