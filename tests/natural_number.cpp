#include "NaturalNumber.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace dscr;

TEST(NaturalNumber, ForwardIteration)
{
    for (int n = 0; n < 10; ++n)
    {
        natural_number R(n);
        set<natural_number::value_type> S(R.begin(), R.end());
        ASSERT_EQ(R.size(), S.size()); // This checks everything is different.
        ASSERT_EQ(R.size(), n);
        ASSERT_TRUE(std::is_sorted(R.begin(), R.end()));
        ASSERT_EQ(*R.begin(), 0);
        ASSERT_EQ(*R.end(), n);
    }
}

TEST(NaturalNumber, PartitionPoint)
{
    big_natural_number A(1000000000000LL);
    auto n = A.partition_point([](auto t) { return t < 50811; });
    ASSERT_EQ(n, 50811);
}

TEST(NaturalNumber, Indices)
{
    std::vector<int> A(10);
    int j = 0;
    for (auto i : indices(A))
    {
        ASSERT_EQ(i, j);
        ++j;
    }
}
