#include <gtest/gtest.h>
#include <iostream>

#include "LexCombinations.hpp"
#include "common_tests.hpp"

using namespace std;
using namespace discreture;

template <class combinations>
void check_lex_combinations(const combinations& X,
                            const typename combinations::combination& x,
                            int n,
                            int k)
{
    ASSERT_TRUE(std::is_sorted(x.begin(), x.end()));
    ASSERT_EQ(x.size(), k);
    if (k > 0)
    {
        ASSERT_TRUE(x.front() >= 0);
        ASSERT_TRUE(x.back() < n);
    }

    auto index = X.get_index(x);
    ASSERT_EQ(x, X[index]);
    ASSERT_EQ(X.get_iterator(x), X.begin() + index);
    ASSERT_EQ(*X.get_iterator(x), x);
}

TEST(LexCombinations, FullIterationTests)
{
    for (int n = 0; n < 14; ++n)
    {
        long total = 0;
        for (short k = 0; k <= n + 1; ++k) // even k+1
        {
            auto X = lex_combinations(n, k);
            test_container_full(X, [&X, n, k](const auto& x) {
                check_lex_combinations(X, x, n, k);
            });
            total += X.size();
        }
        ASSERT_EQ(total, 1 << n);
    }
}

TEST(LexCombinations, ForEach)
{
    for (int n = 0; n < 10; ++n)
    {
        for (int k = 0; k <= n; ++k)
        {
            auto X = lex_combinations(n, k);
            test_container_foreach(X);
        }
    }

    for (int n = 10; n < 23; ++n)
    {
        for (int k = n - 3; k <= n; ++k)
        {
            auto X = lex_combinations(n, k);
            test_container_foreach(X);
        }
    }
}

TEST(LexCombinations, CorrectOrder)
{
    for (int n = 0; n < 10; ++n)
    {
        for (int k = 0; k <= n; ++k)
        {
            auto X = lex_combinations(n, k);
            for (auto it = X.begin(); it != X.end(); ++it)
            {
                auto itnext = it + 1;

                if (itnext == X.end())
                    break;

                ASSERT_TRUE(X.compare(*it, *itnext));
            }
        }
    }
}

TEST(LexCombinations, EdgeCases)
{
    LexCombinations<char> Z(5, 8);

    for (const auto& z : Z)
    {
        ASSERT_TRUE(false);
    }
}

TEST(LexCombinations, FindIf)
{
    auto W = lex_combinations(20, 6);

    auto predicate1 = [](const decltype(W)::combination& comb) -> bool {
        for (size_t i = 0; i < comb.size() - 1; ++i)
        {
            if (2*comb[i] + 1 > comb[i + 1])
                return false;
        }

        return true;
    };

    auto predicate2 = [](const decltype(W)::combination& comb) -> bool {
        for (size_t i = 0; i < comb.size() - 1; ++i)
        {
            if (comb[i] + 3 < comb[i + 1])
                return false;

            if (comb[i] + 1 == comb[i + 1])
                return false;
        }

        return true;
    };

    auto iter = W.find_if(predicate1);

    if (iter != W.end())
    {
        ASSERT_TRUE(predicate1(*iter));
    }
    else
    {
        // verify that indeed no combination satisfies the predicate
        if (W.get_n() < 30)
        {
            for (const auto& w : W)
            {
                ASSERT_FALSE(predicate1(w));
            }
        }
    }

    // 	return true;

    auto T = W.find_all(predicate2);

    size_t numpred2 = 0;
    for (auto& t : T)
    {
        ASSERT_TRUE(predicate2(t));
        ++numpred2;
    }

    if (W.get_n() < 30)
    {
        size_t numpred = 0;
        for (const auto& w : W)
        {
            if (predicate2(w))
            {
                ++numpred;
            }
        }
        ASSERT_EQ(numpred, numpred2);
    }
}

TEST(LexCombinations, PartitionPoint)
{
    int n = 60;
    int k = 30;
    auto X = lex_combinations(n, k);
    auto comb = *std::partition_point(X.begin(), X.end(), [](const auto& x) {
        return x.front() < 26;
    });

    // comb should be == to {26,27,...,55}

    ASSERT_EQ(comb.back(), 55);
    ASSERT_EQ(comb.front(), 26);
    check_lex_combinations(X, comb, n, k);

    auto rcomb = *std::partition_point(X.rbegin(), X.rend(), [](const auto& x) {
        return x.front() > 0;
    });

    // rcomb should be {0, 31,... , 59}

    check_lex_combinations(X, rcomb, n, k);
    ASSERT_EQ(rcomb[0], 0);
    ASSERT_EQ(rcomb[1], 31);
    ASSERT_EQ(rcomb.back(), 59);
}
