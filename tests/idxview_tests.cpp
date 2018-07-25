#include "Combinations.hpp"
#include "IndexedView.hpp"
#include "Permutations.hpp"
#include "generate_strings.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

template <typename IdxView, typename Container, typename IndexContainer>
void check_indexed_view(const IdxView& A,
                        const Container& T,
                        const IndexContainer& X)
{
    ASSERT_EQ(A.size(), X.size());
    for (auto i : indices(A))
    {
        ASSERT_EQ(A[i], T[X[i]]);
    }
}

TEST(IdxViews, CreationAndSanity)
{
    std::vector<int> tonto = {0, 10, 20, 30, 40, 50, 60, 70};
    std::array<int, 5> indices = {{0, 1, 5, 2, 5}};
    auto T = discreture::indexed_view(tonto, indices);
    ASSERT_EQ(T.size(), indices.size());
    check_indexed_view(T, tonto, indices);
}

TEST(IdxViews, Combinations)
{
    for (int n = 0; n < 10; ++n)
    {
        std::vector<std::string> total = generate_random_strings(n);

        for (auto&& x : discreture::combinations(n, n/2))
        {
            auto T = discreture::indexed_view(total, x);

            check_indexed_view(T, total, x);
        }
    }
}

TEST(IdxViews, Permutations)
{
    for (int n = 0; n < 9; ++n)
    {
        auto total = generate_random_strings(n);
        for (auto&& p : discreture::permutations(n))
        {
            auto T = discreture::indexed_view(total, p);

            check_indexed_view(T, total, p);
        }
    }
}
