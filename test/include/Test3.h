#include "TestEnvironment.h" 

struct ComparableButNotPrintable
{
    int x;

    bool operator==(const ComparableButNotPrintable& other) const
    {
        return x == other.x;
    }

    bool operator!=(const ComparableButNotPrintable& other) const
    {
        return x != other.x;
    }

    bool operator>(const ComparableButNotPrintable& other) const
    {
        return x > other.x;
    }

    bool operator<(const ComparableButNotPrintable& other) const
    {
        return x < other.x;
    }
};

struct ComparableAndPrintable : ComparableButNotPrintable {};

std::ostream& operator<<(std::ostream& os, const ComparableAndPrintable& x)
{
    os << "ComparableAndPrintable(" << x.x << ")";

    return os;
}

TestEnvironment Test3()
{
    TestEnvironment tenv;

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

    ComparableButNotPrintable comp_not_print_1{1};
    ComparableButNotPrintable comp_not_print_2{2};

    tenv.assertEq(comp_not_print_1, comp_not_print_2);

    ComparableAndPrintable comp_and_print_1{1};
    ComparableAndPrintable comp_and_print_2{2};

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
    ComparableButNotPrintable comp_not_print_3{1};
    tenv.assertNeq(comp_not_print_1, comp_not_print_3);

    tenv.beginTest("assertNeq with arguments with custom print operation");
    ComparableAndPrintable comp_and_print_3{1};
    tenv.assertNeq(comp_and_print_1, comp_and_print_3);

    tenv.beginSuite("assertGt");

    tenv.beginTest("assertGt with printable arguments 1");
    tenv.assertGt(1, 2, "One is not greater than two!");

    tenv.beginTest("assertGt with printable arguments 2");
    tenv.assertGt('Z', 'A', "Z is not greater than A!");

    tenv.beginTest("assertGt with printable arguments 4");
    tenv.assertGt(2.5, 3);

    tenv.beginTest("assertGt with non-printable arguments");
    tenv.assertGt(comp_not_print_1, comp_not_print_2);

    tenv.beginTest("assertGt with arguments with custom print operation");
    tenv.assertGt(comp_and_print_1, comp_and_print_2);

    tenv.beginSuite("assertLt");

    tenv.beginTest("assertLt with printable arguments 1");
    tenv.assertLt(2, 1, "Two is not less than one!");

    tenv.beginTest("assertLt with printable arguments 2");
    tenv.assertLt('A', 'Z', "A is not less than Z!");

    tenv.beginTest("assertLt with printable arguments 4");
    tenv.assertLt(3, 2.5);

    tenv.beginTest("assertLt with non-printable arguments");
    tenv.assertLt(comp_not_print_2, comp_not_print_1);

    tenv.beginTest("assertLt with arguments with custom print operation");
    tenv.assertLt(comp_and_print_2, comp_and_print_1);

    return tenv;
}