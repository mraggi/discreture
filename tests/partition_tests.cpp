#include "Discreture/Partitions.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <numeric>
#include <set>

using namespace std;
using namespace discreture;

void check_partition(const partitions::partition& x, int n)
{
    int suma = std::accumulate(x.begin(), x.end(), 0);

    ASSERT_EQ(suma, n);

    ASSERT_TRUE(std::is_sorted(x.begin(),
                               x.end(),
                               std::greater<partitions::partition::value_type>()));
}

TEST(Partitions, ForwardIteration)
{
    for (int n = 0; n < 8; ++n)
    {
        partitions X(n);
        set<partitions::partition> S(X.begin(), X.end());
        ASSERT_EQ(X.size(), S.size()); // check if all are different

        for (const auto& x : X)
        {
            check_partition(x, n);
        }
    }
}

TEST(Partitions, ReverseIteration)
{
    for (int n = 0; n < 11; ++n)
    {
        partitions X(n);
        std::vector<partitions::partition> R(X.rbegin(), X.rend());
        std::reverse(R.begin(), R.end());
        ASSERT_EQ(X.size(), R.size());
        long i = 0;
        for (auto&& x : X)
        {
            ASSERT_EQ(x, R[i]);
            ++i;
        }

        for (int a = 1; a <= n; ++a)
        {
            for (int b = a; b <= n; ++b)
            {
                partitions X(n, a, b);
                std::vector<partitions::partition> R(X.rbegin(), X.rend());
                std::reverse(R.begin(), R.end());
                ASSERT_EQ(X.size(), R.size());
                long i = 0;
                for (auto&& x : X)
                {
                    ASSERT_EQ(x, R[i]);
                    ++i;
                }
            }
        }
    }
}

TEST(Partitions, ForEach)
{
    for (int n = 0; n < 22; ++n)
    {
        auto P = partitions(n);
        auto part = P.begin();

        using partition = partitions::partition;
        P.for_each([&part](const partition& p) {
            ASSERT_EQ(*part, p);
            ++part;
        });
    }
}

TEST(Partitions, WithSpecifiedNumParts)
{
    for (int n = 1; n < 10; ++n)
    {
        for (int k = 1; k <= n; ++k)
        {
            partitions X(n, k);
            set<partitions::partition> S(X.begin(), X.end());
            ASSERT_EQ(X.size(), S.size()); // check if all are different

            for (const auto& x : X)
            {
                check_partition(x, n);
                ASSERT_EQ(x.size(), k);
            }
        }
    }
}

TEST(Partitions, WithRangeNumParts)
{
    for (int n = 1; n < 10; ++n)
    {
        for (int k = 1; k <= n; ++k)
        {
            for (int m = k; m <= n; ++m)
            {
                partitions X(n, k, m);
                set<partitions::partition> S(X.begin(), X.end());
                ASSERT_EQ(X.size(), S.size()); // check if all are different

                for (const auto& x : X)
                {
                    check_partition(x, n);
                    ASSERT_GE(x.size(), k);
                    ASSERT_LE(x.size(), m);
                }
            }
        }
    }
}
