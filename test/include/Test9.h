#ifndef TEST9_H
#define TEST9_H

#include <vector>

#include "yUnit.h"

SUITE(firstSuite,
{
    TEST(threeFourFive,
    {
        assert(3*3 + 4*4 == 5*5, "3^2 + 4^2 does not equal 5^2!");
    })

    TEST(sinPi,
    {
        assert(std::cos(0) == 1, "Cos(0) is not 1!");
    })

    TEST(twoPlusTwoEqualsFive,
    {
        beginTest("2+2=5?");
        assert(2 + 2 == 5, "Two plus two does not equal five!");
    })

})

SUITE(secondSuite,
{

    TEST(trueIsTrue,
    {
        assert(true, "True is false!");
    })

    TEST(onePlusOne,
    {
        beginTest("1=1?");
        assert(1 == 1, "One does not equal one!");
    })
})

SUITE(thirdSuite,
{
    TEST(assertionWithoutMessage,
    {
        assert(false);
    })

    TEST(warIsPeace,
    {
        assert(std::string("War") == std::string("Peace"), "War is not Peace!");
    })
})

#endif