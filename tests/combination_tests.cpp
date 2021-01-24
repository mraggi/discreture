#include "Discreture/Combinations.hpp"
#include "Discreture/IntegerInterval.hpp"
#include "common_tests.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace discreture;

template <class combinations>
void check_combination(const combinations& X,
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

TEST(Combinations, FullIterationTests)
{
    for (int n = 0; n < 14; ++n)
    {
        long total = 0;
        for (short k = 0; k <= n + 1; ++k) // even k+1
        {
            auto X = combinations(n, k);
            test_container_full(X, [&X, n, k](const auto& x) {
                check_combination(X, x, n, k);
            });
            total += X.size();
        }
        ASSERT_EQ(total, 1 << n);
    }
}

TEST(Combinations, ForEach)
{
    for (int n = 0; n < 10; ++n)
    {
        for (int k = 0; k <= n; ++k)
        {
            auto X = combinations(n, k);
            test_container_foreach(X);
        }
    }

    for (int n = 10; n < 23; ++n)
    {
        for (int k = n - 3; k <= n; ++k)
        {
            auto X = combinations(n, k);
            test_container_foreach(X);
        }
    }
}

TEST(Combinations, CorrectOrder)
{
    for (int n = 0; n < 10; ++n)
    {
        for (int k = 0; k <= n; ++k)
        {
            auto X = combinations(n, k);
            for (auto it = X.begin(); it != X.end(); ++it)
            {
                auto itnext = it + 1;

                if (itnext == X.end())
                    break;

                ASSERT_TRUE(X.compare(*it, *itnext));
                ASSERT_FALSE(X.compare(*itnext, *it));
            }
        }
    }
}

TEST(Combinations, EdgeCases)
{
    Combinations<char> Z(5, 8);

    for (const auto& z : Z)
    {
        ASSERT_TRUE(false);
        UNUSED(z);
    }
}

TEST(Combinations, FindIf)
{
    auto W = combinations(20, 6);

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

TEST(Combinations, PartitionPoint)
{
    int n = 60;
    int k = 30;
    auto X = combinations(n, k);
    auto comb = *std::partition_point(X.begin(), X.end(), [](const auto& x) {
        return x.back() < 56;
    });

    // comb should be == to {0,1,2,...,28,56}

    ASSERT_EQ(comb[k - 1], 56);
    ASSERT_EQ(comb[k - 2], k - 2);
    check_combination(X, comb, n, k);

    auto rcomb = *std::partition_point(X.rbegin(), X.rend(), [](const auto& x) {
        return x.back() > 47;
    });

    // rcomb should be == to {18, 19, ..., 46, 47}
    check_combination(X, rcomb, n, k);
    ASSERT_EQ(rcomb.back(), 47);
    ASSERT_EQ(rcomb.front(), 18);
}

TEST(Combinations, next_combination)
{
    int n = 10;
    int k = 6;
    std::vector<int> A(k);
    std::iota(A.begin(), A.end(), 0);
    std::vector<int> B = A;
    std::vector<int> C = A;
    std::ptrdiff_t hintB = k;
    std::ptrdiff_t hintC = k;

    int i = 0;
    do
    {
        ASSERT_EQ(A, B);
        ASSERT_EQ(B, C);
        discreture::Combinations<int>::next_combination(n, B, hintB);
        discreture::Combinations<int>::next_combination(n, C, hintC, k - 1);

        discreture::Combinations<int>::iterator it(A);
        ASSERT_EQ(it.ID(), i);
        ++i;
    } while (discreture::Combinations<int>::next_combination(n, A));
}
