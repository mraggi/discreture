#include "Combinations.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace dscr;

template <class Combination>
void check_combination(const Combination& x, int n, int k)
{
    ASSERT_TRUE(std::is_sorted(x.begin(), x.end()));
    ASSERT_EQ(x.size(), k);
    if (k > 0)
    {
        ASSERT_TRUE(x.front() >= 0);
        ASSERT_TRUE(x.back() < n);
    }
}

void check_combination_index(const combinations& X,
                             const combinations::combination& x,
                             int i)
{
    ASSERT_EQ(i, X.get_index(x));
    ASSERT_EQ(x, X[i]);
}

TEST(Combinations, ForwardIteration)
{
    for (int n = 0; n < 10; ++n)
    {
        long total = 0;
        for (int k = 0; k <= n + 1; ++k) // even k+1
        {
            combinations X(n, k);
            set<combinations::combination> S(X.begin(), X.end());
            ASSERT_EQ(X.size(),
                      S.size()); // This checks everything is different.

            long i = 0;

            for (const auto& x : X)
            {
                check_combination(x, n, k);
                check_combination_index(X, x, i);
                ++i;
                ++total;
            }
        }
        ASSERT_EQ(total, 1 << n);
    }
}

TEST(Combinations, ReverseIteration)
{
    for (int n = 0; n < 10; ++n)
    {
        long total = 0;
        for (int k = 0; k <= n + 1; ++k) // even k+1
        {
            combinations X(n, k);
            long i = 0;

            for (auto it = X.rbegin(); it != X.rend(); ++it, --it, ++it)
            {
                auto x = *it;
                check_combination(x, n, k);
                check_combination_index(X, x, X.size() - i - 1);
                ++i;
                ++total;
            }
        }
        ASSERT_EQ(total, 1 << n);
    }
}

TEST(Combinations, RandomAccess)
{
    // combined test
    int n = 10;
    int k = 5;
    combinations X(n, k);
    int i = 25;
    auto it = X.begin() + i;

    do
    {
        check_combination(*it, n, k);
        check_combination_index(X, *it, i);
        ++it;
        ++i;
    } while (it != X.end());
}

TEST(Combinations, Bidirectional)
{
    long n = 38L;
    long k = 16L;
    long r = 10000000000L;

    combinations X(n, k);
    ASSERT_EQ(X.size(), 22239974430LL);

    auto t = X.begin() + r;

    auto s = t;

    ++t;
    --t;
    check_combination(*t, n, k);
    ASSERT_EQ(*t, *s);

    t += 500;
    --t;
    t -= 499;

    check_combination(*t, n, k);
    ASSERT_EQ(*t, *s);

    t -= 250;
    std::advance(t, 3);
    std::advance(t, 3);
    std::advance(t, -3);
    --t;
    s -= 248;
    check_combination(*t, n, k);
    ASSERT_EQ(*t, *s);
}

TEST(Combinations, ForEach)
{
    for (int n = 0; n < 20; ++n)
    {
        for (int k = 0; k <= n; ++k)
        {
            combinations X(n, k);
            auto it = X.begin();
            X.for_each([&it](const combinations::combination& x) {
                ASSERT_EQ(x, *it);
                ++it;
            });
        }
    }
}

TEST(Combinations, CorrectOrder)
{
    for (int n = 0; n < 10; ++n)
    {
        for (int k = 0; k <= n; ++k)
        {
            combinations X(n, k);
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
    basic_combinations<char> Z(5, 8);

    for (const auto& z : Z)
    {
        ASSERT_TRUE(false);
        UNUSED(z);
    }
}

TEST(Combinations, FindIf)
{
    combinations W(20, 6);

    auto predicate1 = [](const combinations::combination& comb) -> bool {
        for (size_t i = 0; i < comb.size() - 1; ++i)
        {
            if (2*comb[i] + 1 > comb[i + 1])
                return false;
        }

        return true;
    };

    auto predicate2 = [](const combinations::combination& comb) -> bool {
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
        check_combination(t, W.get_n(), W.get_k());
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
    combinations X(n, k);
    auto comb = *std::partition_point(
      X.begin(), X.end(), [](const auto& x) { return x.back() < 56; });

    // comb should be == to {0,1,2,...,28,56}

    ASSERT_EQ(comb[k - 1], 56);
    ASSERT_EQ(comb[k - 2], k - 2);
    check_combination(comb, n, k);

    auto rcomb = *std::partition_point(
      X.rbegin(), X.rend(), [](const auto& x) { return x.back() > 47; });

    // rcomb should be == to {18, 19, ..., 46, 47}
    check_combination(rcomb, n, k);
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
    long long hintB = k;
    long long hintC = k;

    int i = 0;
    do
    {
        ASSERT_EQ(A, B);
        ASSERT_EQ(B, C);
        dscr::combinations::next_combination(n, B, hintB);
        dscr::combinations::next_combination(n, C, hintC, k - 1);

        dscr::combinations::iterator it(A);
        ASSERT_EQ(it.ID(), i);
        ++i;
    } while (dscr::combinations::next_combination(n, A));
}
