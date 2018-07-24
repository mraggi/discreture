#include "Permutations.hpp"
#include "common_tests.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace discreture;

template <class permutation>
bool is_permutation(permutation x)
{
    std::sort(x.begin(), x.end());
    for (auto i : indices(x))
    {
        if (x[i] != i)
            return false;
    }
    return true;
}

template <class permutations>
void check_permutation(const permutations& P,
                       typename permutations::permutation const& p)
{
    ASSERT_TRUE(is_permutation(p));
    int index = P.get_index(p);
    auto it = P.get_iterator(p);
    ASSERT_EQ(*it, p);
    ASSERT_EQ(p, P[index]);
    ASSERT_EQ(it, P.begin() + index);
}

TEST(Permutations, FullTests)
{
    for (int n = 0; n < 7; ++n)
    {
        auto P = permutations(n);
        test_container_full(P, [&P](auto& p) { check_permutation(P, p); });
    }
}

TEST(Permutations, PartitionPoint)
{
    int n = 20;
    Permutations<int> X(n);
    auto perm =
      *std::partition_point(X.begin(),
                            X.end(),
                            [](const Permutations<int>::permutation& x) {
                                return x.front() < 17;
                            });

    // perm should be == to {17,0,1,2,...,16,18,19}

    //     check_permutation(perm);
    ASSERT_EQ(perm[0], 17);
    ASSERT_TRUE(std::is_sorted(perm.begin() + 1, perm.end()));

    auto rperm =
      *std::partition_point(X.rbegin(),
                            X.rend(),
                            [](const Permutations<int>::permutation& x) {
                                return x.front() > 5;
                            });

    // rperm should be == to {5,19,18,...,0}

    //     check_permutation(rperm);
    ASSERT_EQ(rperm[0], 5);
    ASSERT_TRUE(
      std::is_sorted(rperm.begin() + 1, rperm.end(), std::greater<int>()));
}
