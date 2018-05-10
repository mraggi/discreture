#include "Arrangement.hpp"
#include "Combinations.hpp"
#include "Permutations.hpp"
#include "generate_strings.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

template <typename Arrangement, typename Container, typename IndexContainer>
void check_arrangement(const Arrangement& A,
                       const Container& T,
                       const IndexContainer& X)
{
    ASSERT_EQ(A.size(), X.size());
    for (int i = 0; i < A.size(); ++i)
    {
        ASSERT_EQ(A[i], T[X[i]]);
    }
}

TEST(Arrangements, CreationAndSanity)
{
    std::vector<int> tonto = {0, 10, 20, 30, 40, 50, 60, 70};
    std::array<int, 5> indices = {{0, 1, 5, 2, 5}};
    auto T = dscr::make_arrangement(tonto, indices);
    ASSERT_EQ(T.size(), indices.size());
    check_arrangement(T, tonto, indices);
}

TEST(Arrangements, Combinations)
{
    for (int n = 0; n < 10; ++n)
    {
        std::vector<std::string> total = generate_random_strings(n);
        dscr::combinations X(n, n/2);

        for (auto& x : X)
        {
            auto T = dscr::make_arrangement(total, x);

            check_arrangement(T, total, x);
        }
    }
}

TEST(Arrangements, Permutations)
{
    for (int n = 0; n < 9; ++n)
    {
        auto total = generate_random_strings(n);
        dscr::permutations P(n);
        for (auto& p : P)
        {
            auto T = dscr::make_arrangement(total, p);

            check_arrangement(T, total, p);
        }
    }
}
