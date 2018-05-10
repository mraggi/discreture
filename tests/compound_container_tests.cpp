#include "Combinations.hpp"
#include "CombinationsTree.hpp"
#include "CompoundContainer.hpp"
#include "Permutations.hpp"
#include "generate_strings.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace dscr;

template <class CompundContainer, class Objects, class Indices>
void check_compound_container(const CompundContainer& U,
                              const Objects& A,
                              const Indices& X)
{
    ASSERT_EQ(U.size(), X.size());
    for (size_t i = 0; i < X.size(); ++i)
    {
        for (size_t j = 0; j < X[i].size(); ++j)
        {
            ASSERT_EQ(U[i][j], A[X[i][j]]);
        }
    }

    size_t i = 0;
    for (auto u : U)
    {
        size_t j = 0;
        for (auto w : u)
        {
            ASSERT_EQ(w, A[X[i][j]]);
            ++j;
        }
        ++i;
    }
}

TEST(CompoundContainer, CreationAndSanity)
{
    std::vector<std::string> A = {"hola", "adios", "uch", "bla"};
    std::vector<std::vector<int>> X = {{0, 1}, {1, 3}, {0, 1, 2}};
    auto U = dscr::make_compound_container(A, X);

    check_compound_container(U, A, X);
}

TEST(CompoundContainer, Combinations)
{
    std::vector<std::string> A = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    int n = A.size();
    for (int k = 0; k <= n; ++k)
    {
        using namespace dscr;
        auto U = dscr::compound_combinations(A, k);
        check_compound_container(U, A, dscr::combinations(n, k));
    }
}

TEST(CompoundContainer, CombinationsTree)
{
    std::vector<std::string> A = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    int n = A.size();
    for (int k = 0; k <= n; ++k)
    {
        using namespace dscr;
        auto U = dscr::compound_combinations_tree(A, k);
        check_compound_container(U, A, dscr::combinations_tree(n, k));
    }
}

TEST(CompoundContainer, Permutations)
{
    std::vector<std::string> A = {"a", "b", "c", "d", "e"};
    int n = A.size();
    for (int k = 0; k <= n; ++k)
    {
        using namespace dscr;
        auto U = dscr::compound_permutations(A);
        check_compound_container(U, A, dscr::permutations(n));
    }
}
