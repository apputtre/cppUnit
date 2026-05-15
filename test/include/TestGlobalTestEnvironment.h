#ifndef TESTGLOBALTESTENVIRONMENT_H
#define TESTGLOBALTESTENVIRONMENT_H

#include "yUnit.h"

TEST(testGlobalTestEnvironment)
{
    assertEq(2+2, 5, "Two plus two does not equal five!");
}

TestEnvironment testGlobalTestEnvironment()
{
    yUnit::impl::runTests();
    return yUnit::getGlobalTestEnvironment();
}

#endif