#include "Discreture/ArithmeticProgression.hpp"
#include "Discreture/IntegerInterval.hpp"
#include "Discreture/Probability.hpp"
#include "common_tests.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace discreture;

TEST(ArithmeticProgression, ForwardIteration)
{
    for (int n = 0; n < 10; ++n)
    {
        for (int m = 0; m < n; ++m)
        {
            arithmetic_progression R(n, m, -1);
            test_container_full(R, [n, m](int i) { return i <= n && i > m; });
            set<arithmetic_progression::value_type> S(R.begin(), R.end());
            // This checks everything is different.
            ASSERT_EQ(R.size(), S.size());
            ASSERT_EQ(R.size(), n - m);
            ASSERT_TRUE(std::is_sorted(R.begin(), R.end(), std::greater<int>()));
            ASSERT_EQ(*R.begin(), n);
            ASSERT_EQ(*(R.end() - 1), m + 1);
        }
    }
}

TEST(ArithmeticProgression, RandomAccess)
{
    ArithmeticProgression<long> A(5, 16, 2);
    ASSERT_EQ(A[0], 5);
    ASSERT_EQ(A[1], 7);
    ASSERT_EQ(A[2], 9);
    ASSERT_EQ(A[3], 11);
    ASSERT_EQ(A[4], 13);
    ASSERT_EQ(A[5], 15);
    ASSERT_EQ(A.size(), 6);

    ArithmeticProgression<short> B(5, 11, 2);
    ASSERT_EQ(B[0], 5);
    ASSERT_EQ(B[1], 7);
    ASSERT_EQ(B[2], 9);
    ASSERT_EQ(B.size(), 3);
}

TEST(ArithmeticProgression, Empty)
{
    for (int i = 0; i < 100; ++i)
    {
        int a = discreture::random::random_int(0, 100);
        int b = discreture::random::random_int(0, 100);
        int t = discreture::random::random_int(-100, 100);
        if (t == 0)
            continue;
        if (t > 0 && a < b)
            continue;
        if (t < 0 && a > b)
            continue;
        auto X = arithmetic_progression(a, b, t);
        ASSERT_EQ(X.size(), 0);
        for (auto x : X)
        {
            discreture::UNUSED(x);
            ASSERT_FALSE(true);
        }
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
    ArithmeticProgression<long> A(16, 9, -2);
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

    ArithmeticProgression<short> B(16, 10, -2);
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
    ArithmeticProgression<long> A(5, 13, 3);
    ASSERT_EQ(A.size(), 3);
    auto it = A.begin();
    ASSERT_EQ(*it, 5);
    ++it;
    ASSERT_EQ(*it, 8);
    ++it;
    ASSERT_EQ(*it, 11);
    ASSERT_EQ(*A.end(), 14);

    ArithmeticProgression<short> B(5, 14, 3);
    ASSERT_EQ(B.size(), 3);
    auto it2 = B.begin();
    ASSERT_EQ(*it2, 5);
    ++it2;
    ASSERT_EQ(*it2, 8);
    ++it2;
    ASSERT_EQ(*it2, 11);
    ASSERT_EQ(*B.end(), 14);
}
