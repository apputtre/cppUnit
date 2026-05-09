#ifndef TEST11_H
#define TEST11_H

#include "yUnit.h"

// Entire suite should be reported as skipped
SUITE(skipSuite,
{
    skip();

    TEST(test_1,
    {
        assertEq(2+2, 5, "Two plus two does not equal five!");
    })
})

// Only test_2 should be skipped
SUITE(skipTest,
{
    TEST(test_1,
    {
        assertEq(std::string("War"), std::string("Peace"), "War is not peace!");
    })

    skip();

    // Should be reported as skipped
    TEST(test_2,
    {
        assert(false, "False is false!");
    })
})

#endif