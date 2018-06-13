#include "Multisets.hpp"
#include "Probability.hpp"
#include "common_tests.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <set>

using namespace std;
using namespace dscr;

void check_multiset(const multisets::multiset& x,
                    const multisets::multiset& total)
{
    ASSERT_EQ(x.size(), total.size());
    for (size_t i = 0; i < x.size(); ++i)
    {
        ASSERT_LE(x[i], total[i]);
        ASSERT_GE(x[i], 0);
    }
}

std::vector<int> get_random_multiset(int n)
{
    std::vector<int> result(n);

    std::generate(result.begin(), result.end(), []() {
        return random::random_int(0, 3);
    });

    return result;
}

TEST(Multisets, FullTests)
{
    for (int n = 0; n < 12; ++n)
    {
        auto total = get_random_multiset(n);
        multisets X(total);
        test_container_full(X, [&total](const auto& x) {
            check_multiset(x, total);
        });
    }
}

TEST(Multisets, ForEach)
{
    for (int n = 0; n < 12; ++n)
    {
        auto total = get_random_multiset(n);
        multisets X(total);
        test_container_foreach(X);
    }
}

TEST(Multisets, PartitionPoint)
{
    multisets::multiset total(55, 1);
    total[0] = 2;
    total.back() = 2;
    multisets X(total);

    auto t = *std::partition_point(X.begin(), X.end(), [](const auto& x) {
        return x.back() < 2;
    });

    multisets::multiset correct(55, 0);
    correct.back() = 2;
    check_multiset(t, total);

    ASSERT_EQ(t, correct);
}
