#include "NumberRange.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace dscr;

TEST(NumberRange, ForwardIteration)
{
    for (int n = 0; n < 10; ++n)
    {
        for (int m = 0; m < n; ++m)
        {
            number_range R(n, m, -1);
            set<number_range::value_type> S(R.begin(), R.end());
            ASSERT_EQ(R.size(),
                      S.size()); // This checks everything is different.
            ASSERT_EQ(R.size(), n - m);
            ASSERT_TRUE(
              std::is_sorted(R.begin(), R.end(), std::greater<int>()));
            ASSERT_EQ(*R.begin(), n);
            ASSERT_EQ(*(R.end() - 1), m + 1);
        }

        for (int m = n; m < 15; ++m)
        {
            number_range R(n, m);
            set<number_range::value_type> S(R.begin(), R.end());
            ASSERT_EQ(R.size(),
                      S.size()); // This checks everything is different.
            ASSERT_EQ(R.size(), m - n);
            ASSERT_TRUE(std::is_sorted(R.begin(), R.end()));
            ASSERT_EQ(*R.begin(), n);
            ASSERT_EQ(*(R.end() - 1), m - 1);
        }
    }
}

TEST(NumberRange, RandomAccess)
{
    basic_number_range<long> A(5, 16, 2);
    ASSERT_EQ(A[0], 5);
    ASSERT_EQ(A[1], 7);
    ASSERT_EQ(A[2], 9);
    ASSERT_EQ(A[3], 11);
    ASSERT_EQ(A[4], 13);
    ASSERT_EQ(A[5], 15);
    ASSERT_EQ(A.size(), 6);

    basic_number_range<short> B(5, 11, 2);
    ASSERT_EQ(B[0], 5);
    ASSERT_EQ(B[1], 7);
    ASSERT_EQ(B[2], 9);
    ASSERT_EQ(B.size(), 3);
}

TEST(NumberRange, PartitionPoint)
{
    big_number_range A(-3700LL, 1000000000000LL);
    auto n = A.partition_point([](auto t) { return t < 5000; });
    ASSERT_EQ(n, 5000);
}

TEST(NumberRange, NegativeStepTest)
{
    basic_number_range<long> A(16, 9, -2);
    auto it = A.begin();
    ASSERT_EQ(*it, 16);
    ++it;
    ASSERT_EQ(*it, 14);
    ++it;
    ASSERT_EQ(*it, 12);
    ++it;
    ASSERT_EQ(*it, 10);

    ASSERT_EQ(*A.end(), 8);
    ASSERT_EQ(A.size(), 4);

    basic_number_range<short> B(16, 10, -2);
    auto it2 = B.begin();
    ASSERT_EQ(*it2, 16);
    ++it2;
    ASSERT_EQ(*it2, 14);
    ++it2;
    ASSERT_EQ(*it2, 12);

    ASSERT_EQ(*B.end(), 10);
    ASSERT_EQ(B.size(), 3);
}

TEST(NumberRange, PositiveStepTest)
{
    basic_number_range<long> A(5, 13, 3);
    ASSERT_EQ(A.size(), 3);
    auto it = A.begin();
    ASSERT_EQ(*it, 5);
    ++it;
    ASSERT_EQ(*it, 8);
    ++it;
    ASSERT_EQ(*it, 11);
    ASSERT_EQ(*A.end(), 14);

    basic_number_range<short> B(5, 14, 3);
    ASSERT_EQ(B.size(), 3);
    auto it2 = B.begin();
    ASSERT_EQ(*it2, 5);
    ++it2;
    ASSERT_EQ(*it2, 8);
    ++it2;
    ASSERT_EQ(*it2, 11);
    ASSERT_EQ(*B.end(), 14);
}
