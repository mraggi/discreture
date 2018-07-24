#include "SetPartitions.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <set>

using namespace std;
using namespace discreture;

void check_set_partition(const set_partitions::set_partition& x, int n)
{
    vector<int> all;
    for (auto&& u : x)
    {
        all.insert(all.end(), u.begin(), u.end());
    }
    ASSERT_EQ(all.size(), n);
    std::sort(all.begin(), all.end());

    for (int i = 0; i < n; ++i)
    {
        ASSERT_EQ(i, all[i]);
    }
}

TEST(SetPartitions, ForwardIteration)
{
    for (int n = 0; n < 8; ++n)
    {
        set_partitions X(n);
        set<set_partitions::set_partition> S(X.begin(), X.end());
        ASSERT_EQ(X.size(), S.size()); // check if all dyck paths are different

        for (const auto& x : X)
        {
            check_set_partition(x, n);
        }
    }
}

TEST(SetPartitions, WithSpecifiedNumParts)
{
    for (int n = 0; n < 8; ++n)
    {
        for (int k = 1; k <= n; ++k)
        {
            set_partitions X(n, k);
            set<set_partitions::set_partition> S(X.begin(), X.end());
            ASSERT_EQ(X.size(),
                      S.size()); // check if all motzkin paths are different

            for (const auto& x : X)
            {
                check_set_partition(x, n);
                ASSERT_EQ(x.size(), k);
            }
        }
    }
}

TEST(SetPartitions, WithRangeNumParts)
{
    for (int n = 1; n < 7; ++n)
    {
        for (int k = 1; k <= n; ++k)
        {
            for (int m = k; m <= n; ++m)
            {
                set_partitions X(n, k, m);
                set<set_partitions::set_partition> S(X.begin(), X.end());
                ASSERT_EQ(X.size(), S.size()); // check if all are different

                for (const auto& x : X)
                {
                    check_set_partition(x, n);
                    ASSERT_GE(x.size(), k);
                    ASSERT_LE(x.size(), m);
                }
            }
        }
    }
}
