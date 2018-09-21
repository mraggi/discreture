#include "Discreture/Combinations.hpp"
#include "Discreture/IndexedViewContainer.hpp"
#include "Discreture/LexCombinations.hpp"
#include "Discreture/Permutations.hpp"
#include "generate_strings.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace discreture;

template <class CompundContainer, class Objects, class Indices>
void check_indexed_view_container(const CompundContainer& U,
                                  const Objects& A,
                                  const Indices& X)
{
    ASSERT_EQ(U.size(), X.size());
    for (auto i : indices(X))
    {
        for (auto j : indices(X[i]))
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

TEST(IndexedViewContainer, CreationAndSanity)
{
    std::vector<std::string> A = {"hola", "adios", "uch", "bla"};
    std::vector<std::vector<int>> X = {{0, 1}, {1, 3}, {0, 1, 2}};
    auto U = discreture::indexed_view_container(A, X);

    check_indexed_view_container(U, A, X);
}

TEST(IndexedViewContainer, Combinations)
{
    std::vector<std::string> A = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    int n = A.size();
    for (int k = 0; k <= n; ++k)
    {
        using namespace discreture;
        auto U = combinations(A, k);
        check_indexed_view_container(U, A, discreture::combinations(n, k));
    }
}

TEST(IndexedViewContainer, LexCombinations)
{
    std::vector<std::string> A = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    int n = A.size();
    for (auto k : NN(n))
    {
        using namespace discreture;
        auto U = discreture::lex_combinations(A, k);
        check_indexed_view_container(U, A, discreture::lex_combinations(n, k));
    }
}

TEST(IndexedViewContainer, Permutations)
{
    std::vector<std::string> A = {"a", "b", "c", "d", "e"};
    int n = A.size();
    using namespace discreture;
    auto U = discreture::permutations(A);
    check_indexed_view_container(U, A, discreture::permutations(n));
}
