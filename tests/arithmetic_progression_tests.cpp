#include "ArithmeticProgression.hpp"
#include "IntegerInterval.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace dscr;

TEST(ArithmeticProgression, ForwardIteration)
{
    for (int n = 0; n < 10; ++n)
    {
        for (int m = 0; m < n; ++m)
        {
            arithmetic_progression R(n, m, -1);
            set<arithmetic_progression::value_type> S(R.begin(), R.end());
            ASSERT_EQ(R.size(),
                      S.size()); // This checks everything is different.
            ASSERT_EQ(R.size(), n - m);
            ASSERT_TRUE(
              std::is_sorted(R.begin(), R.end(), std::greater<int>()));
            ASSERT_EQ(*R.begin(), n);
            ASSERT_EQ(*(R.end() - 1), m + 1);
        }
    }
}

TEST(ArithmeticProgression, RandomAccess)
{
    basic_arithmetic_progression<long> A(5, 16, 2);
    ASSERT_EQ(A[0], 5);
    ASSERT_EQ(A[1], 7);
    ASSERT_EQ(A[2], 9);
    ASSERT_EQ(A[3], 11);
    ASSERT_EQ(A[4], 13);
    ASSERT_EQ(A[5], 15);
    ASSERT_EQ(A.size(), 6);

    basic_arithmetic_progression<short> B(5, 11, 2);
    ASSERT_EQ(B[0], 5);
    ASSERT_EQ(B[1], 7);
    ASSERT_EQ(B[2], 9);
    ASSERT_EQ(B.size(), 3);
}

TEST(ArithmeticProgression, Empty)
{
    basic_arithmetic_progression<int> A(5, 3, 2);

    ASSERT_EQ(A.size(), 0);
    for (auto a : A)
    {
        ASSERT_FALSE(true);
    }

    basic_arithmetic_progression<int> B(5, 8, -2);
    ASSERT_EQ(B.size(), 0);
    for (auto b : B)
    {
        ASSERT_FALSE(true);
    }

    basic_arithmetic_progression<int> C(5, 5, 1);
    ASSERT_EQ(C.size(), 0);
    for (auto c : C)
    {
        ASSERT_FALSE(true);
    }
}

TEST(ArithmeticProgression, PartitionPoint)
{
    big_arithmetic_progression A(-3700LL, 1000000000000LL, 5);
    auto n = A.partition_point([](auto t) { return t < 5000; });
    ASSERT_EQ(n, 5000);

    long first = 136;
    long last = 1000000000000LL;
    long step = 59;

    big_arithmetic_progression B(first, last, step);
    auto m = B.partition_point([](auto t) { return t < 5000; });
    ASSERT_GE(m, 5000);
    ASSERT_TRUE(m%step == first%step);
}

TEST(ArithmeticProgression, NegativeStepTest)
{
    basic_arithmetic_progression<long> A(16, 9, -2);
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

    basic_arithmetic_progression<short> B(16, 10, -2);
    auto it2 = B.begin();
    ASSERT_EQ(*it2, 16);
    ++it2;
    ASSERT_EQ(*it2, 14);
    ++it2;
    ASSERT_EQ(*it2, 12);

    ASSERT_EQ(*B.end(), 10);
    ASSERT_EQ(B.size(), 3);
}

TEST(ArithmeticProgression, PositiveStepTest)
{
    basic_arithmetic_progression<long> A(5, 13, 3);
    ASSERT_EQ(A.size(), 3);
    auto it = A.begin();
    ASSERT_EQ(*it, 5);
    ++it;
    ASSERT_EQ(*it, 8);
    ++it;
    ASSERT_EQ(*it, 11);
    ASSERT_EQ(*A.end(), 14);

    basic_arithmetic_progression<short> B(5, 14, 3);
    ASSERT_EQ(B.size(), 3);
    auto it2 = B.begin();
    ASSERT_EQ(*it2, 5);
    ++it2;
    ASSERT_EQ(*it2, 8);
    ++it2;
    ASSERT_EQ(*it2, 11);
    ASSERT_EQ(*B.end(), 14);
}
