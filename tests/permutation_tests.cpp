#include "Permutations.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace dscr;

void check_permutation(Permutations<int>::permutation x)
{
    std::sort(x.begin(), x.end());
    for (auto i : indices(x))
    {
        ASSERT_EQ(x[i], i);
    }
}

void check_permutation_index(const Permutations<int>& X,
                             const Permutations<int>::permutation& x,
                             int i)
{
    ASSERT_EQ(i, X.get_index(x));
    ASSERT_EQ(x, X[i]);
}

TEST(Permutations, ForwardIteration)
{
    for (int n = 0; n < 7; ++n)
    {
        Permutations<int> X(n);
        long i = 0;

        for (const auto& x : X)
        {
            check_permutation(x);
            check_permutation_index(X, x, i);
            ++i;
        }
    }
}

TEST(Permutations, ReverseIteration)
{
    for (int n = 0; n < 7; ++n)
    {
        Permutations<int> X(n);
        long i = 0;

        for (auto it = X.rbegin(); it != X.rend(); ++it)
        {
            check_permutation(*it);
            check_permutation_index(X, *it, X.size() - i - 1);
            ++i;
        }
    }
}

TEST(Permutations, RandomAccess)
{
    // combined test
    int n = 6;
    Permutations<int> X(n);
    int i = 25;
    auto it = X.begin() + i;

    do
    {
        check_permutation(*it);
        check_permutation_index(X, *it, i);
        ++it;
        ++i;
    } while (it != X.end());
}

TEST(Permutations, Bidirectional)
{
    long n = 16L;
    long r = 10000000000L;

    Permutations<int> X(n);
    ASSERT_EQ(X.size(), 20922789888000LL);

    auto t = X.begin() + r;

    auto s = t;

    ++t;
    --t;
    check_permutation(*t);
    ASSERT_EQ(*t, *s);

    t += 500;
    --t;
    std::advance(t, -489);
    std::advance(t, -10);

    check_permutation(*t);
    ASSERT_EQ(*t, *s);

    t -= 250;
    ++t;
    ++t;
    s -= 248;
    check_permutation(*t);
    ASSERT_EQ(*t, *s);
}

TEST(Permutations, PartitionPoint)
{
    int n = 20;
    Permutations<int> X(n);
    auto perm = *std::partition_point(
      X.begin(), X.end(), [](const Permutations<int>::permutation& x) {
          return x.front() < 17;
      });

    // perm should be == to {17,0,1,2,...,16,18,19}

    check_permutation(perm);
    ASSERT_EQ(perm[0], 17);
    ASSERT_TRUE(std::is_sorted(perm.begin() + 1, perm.end()));

    auto rperm = *std::partition_point(
      X.rbegin(), X.rend(), [](const Permutations<int>::permutation& x) {
          return x.front() > 5;
      });

    // rperm should be == to {5,19,18,...,0}

    check_permutation(rperm);
    ASSERT_EQ(rperm[0], 5);
    ASSERT_TRUE(
      std::is_sorted(rperm.begin() + 1, rperm.end(), std::greater<int>()));
}
