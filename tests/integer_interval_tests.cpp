#include "Discreture/IntegerInterval.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace discreture;

TEST(IntegerInterval, ForwardIteration)
{
    for (int n = 0; n < 10; ++n)
    {
        integer_interval R(n);
        set<integer_interval::value_type> S(R.begin(), R.end());
        ASSERT_EQ(R.size(), S.size()); // This checks everything is different.
        ASSERT_EQ(R.size(), n);
        ASSERT_TRUE(std::is_sorted(R.begin(), R.end()));
        ASSERT_EQ(*R.begin(), 0);
        ASSERT_EQ(*R.end(), n);

        for (int m = n; m < 15; ++m)
        {
            integer_interval R(n, m);
            set<integer_interval::value_type> S(R.begin(), R.end());

            ASSERT_EQ(R.size(), S.size());
            ASSERT_EQ(R.size(), m - n);

            ASSERT_TRUE(std::is_sorted(R.begin(), R.end()));

            ASSERT_EQ(*R.begin(), n);

            ASSERT_EQ(*(R.end() - 1), m - 1);
        }
    }
}

TEST(IntegerInterval, Empty)
{
    auto I = integer_interval(5, 4);
    ASSERT_EQ(I.size(), 0);
    for (auto i : I)
        ASSERT_FALSE(true);

    auto J = integer_interval(-8);
    ASSERT_EQ(J.size(), 0);
    for (auto i : J)
        ASSERT_FALSE(true);
}

TEST(IntegerInterval, PartitionPoint)
{
    big_integer_interval A(1000000000000LL);
    auto n = A.partition_point([](auto t) { return t < 50811; });
    ASSERT_EQ(n, 50811);
}

TEST(IntegerInterval, Indices)
{
    std::vector<int> A(10);
    int j = 0;
    for (auto i : indices(A))
    {
        ASSERT_EQ(i, j);
        ++j;
    }
}
