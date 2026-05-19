#ifndef TESTEQNEQ_H
#define TESTEQNEQ_H

#include "yUnit.h"
#include "ComparableButNotPrintable.h"
#include "ComparableAndPrintable.h"

#include <math.h>

TEST("assertEq with printable arguments 1")
{
    assertEq(2+2, 5, "Two plus two does not equal five!");
}

TEST("assertEq with printable arguments 2")
{
    assertEq(std::cos(0), 1, "cos(0) is not 1!");
}

TEST("assertEq with printable arguments 3")
{
    assertEq(std::string("War"), std::string("Peace"), "War is not peace!");
}

TEST("assertEq with printable arguments 4")
{
    assertEq(true, false);
}

TEST("assertEq with non-printable arguments")
{
    ComparableButNotPrintable comp_not_print_1{1};
    ComparableButNotPrintable comp_not_print_2{2};

    assertEq(comp_not_print_1, comp_not_print_2);
}

TEST("assertEq with arguments with custom print operation")
{
    ComparableAndPrintable comp_and_print_1{1};
    ComparableAndPrintable comp_and_print_2{2};

    assertEq(comp_and_print_1, comp_and_print_2);
}

TEST("assertNeq with printable arguments 1")
{
    assertNeq(2+2, 5, "Two plus two equals five!");
}

TEST("assertNeq with printable arguments 2")
{
    assertNeq(std::cos(0), 1, "cos(0) is 1!");
}

TEST("assertNeq with printable arguments 3")
{
    assertNeq(std::string("War"), std::string("Peace"), "War is peace!");
}

TEST("assertNeq with printable arguments 4")
{
    assertNeq(true, true);
}

TEST("assertNeq with non-printable arguments")
{
    ComparableButNotPrintable comp_not_print_1{1};
    ComparableButNotPrintable comp_not_print_3{1};

    assertNeq(comp_not_print_1, comp_not_print_3);
}

TEST("assertNeq with arguments with custom print operation")
{

    ComparableAndPrintable comp_and_print_1{1};
    ComparableAndPrintable comp_and_print_3{1};

    assertNeq(comp_and_print_1, comp_and_print_3);
}

#endif