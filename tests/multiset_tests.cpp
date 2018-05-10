#include "Multisets.hpp"
#include "Probability.hpp"
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

    std::generate(
      result.begin(), result.end(), []() { return random::random_int(0, 3); });

    return result;
}

template <class Iter>
void dumb_advance(Iter& it, int m)
{
    while (m > 0)
    {
        ++it;
        --m;
    }

    while (m < 0)
    {
        --it;
        ++m;
    }
}

TEST(Multisets, ForwardIteration)
{
    for (int n = 0; n < 12; ++n)
    {
        auto total = get_random_multiset(n);
        multisets X(total);
        set<multisets::multiset> S(X.begin(), X.end());
        ASSERT_EQ(X.size(), S.size()); // check if all multisets are different

        long i = 0;
        for (const auto& x : X)
        {
            check_multiset(x, total);
            ASSERT_EQ(X.get_index(x), i);
            // 			cout << "all good: " << x << endl;
            // 			cout << "Lets see: " << X[i] << endl;
            ASSERT_EQ(X[i], x);
            ++i;
        }
    }
}

TEST(Multisets, ReverseIteration)
{
    for (int n = 0; n < 12; ++n)
    {
        auto total = get_random_multiset(n);
        multisets X(total);
        set<multisets::multiset> S(X.rbegin(), X.rend());
        ASSERT_EQ(X.size(), S.size()); // check if all multisets are different

        for (auto it = X.rbegin(); it != X.rend(); ++it)
        {
            check_multiset(*it, total);
        }
    }
}

TEST(Multisets, Bidirectional)
{
    for (int n = 0; n < 8; ++n)
    {
        auto total = get_random_multiset(n);
        multisets X(total);
        if (X.size() < 2)
            continue;
        auto it = X.begin();
        int start = dscr::random::random_int<int>(0, X.size()/2);
        dumb_advance(it, start);
        auto x = *it;
        ASSERT_EQ(*it, X[start]);
        int adv = random::random_int<int>(0, X.size()/2);
        dumb_advance(it, adv);
        ASSERT_EQ(*it, X[start + adv]);
        dumb_advance(it, -adv);

        ASSERT_EQ(*it, x);
    }
}

TEST(Multisets, RandomAccess)
{
    for (int n = 0; n < 8; ++n)
    {
        auto total = get_random_multiset(n);
        multisets X(total);
        if (X.size() < 2)
            continue;
        auto it = X.begin();
        int start = dscr::random::random_int<int>(0, X.size()/2);
        std::advance(it, start);
        auto x = *it;
        int adv = random::random_int<int>(0, X.size()/2);
        std::advance(it, adv);
        ASSERT_EQ(*it, X[start + adv]);
        std::advance(it, -adv);

        ASSERT_EQ(*it, x);
    }
}

TEST(Multisets, PartitionPoint)
{
    multisets::multiset total(55, 1);
    total[0] = 2;
    total.back() = 2;
    multisets X(total);

    auto t = *std::partition_point(
      X.begin(), X.end(), [](const auto& x) { return x.back() < 2; });

    multisets::multiset correct(55, 0);
    correct.back() = 2;
    check_multiset(t, total);

    ASSERT_EQ(t, correct);
}
