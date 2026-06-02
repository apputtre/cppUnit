#ifndef COMPARABLEBUTNOTPRINTABLE_H
#define COMPARABLEBUTNOTPRINTABLE_H

#include <ostream>

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

    bool operator>=(const ComparableButNotPrintable& other) const
    {
        return x >= other.x;
    }

    bool operator<=(const ComparableButNotPrintable& other) const
    {
        return x <= other.x;
    }

    static_assert(std::totally_ordered<ComparableButNotPrintable>);
};

#endif