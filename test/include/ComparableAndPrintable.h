#ifndef COMPARABLEANDPRINTABLE_H
#define COMPARABLEANDPRINTABLE_H

#include "ComparableButNotPrintable.h"

struct ComparableAndPrintable : ComparableButNotPrintable {};

std::ostream& operator<<(std::ostream& os, const ComparableAndPrintable& x)
{
    os << "ComparableAndPrintable(" << x.x << ")";

    return os;
}

#endif