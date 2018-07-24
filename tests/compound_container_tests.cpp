#include "Combinations.hpp"
#include "CompoundContainer.hpp"
#include "LexCombinations.hpp"
#include "Permutations.hpp"
#include "generate_strings.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace discreture;

template <class CompundContainer, class Objects, class Indices>
void check_compound_container(const CompundContainer& U,
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

TEST(CompoundContainer, CreationAndSanity)
{
    std::vector<std::string> A = {"hola", "adios", "uch", "bla"};
    std::vector<std::vector<int>> X = {{0, 1}, {1, 3}, {0, 1, 2}};
    auto U = discreture::compound_container(A, X);

    check_compound_container(U, A, X);
}

TEST(CompoundContainer, Combinations)
{
    std::vector<std::string> A = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    int n = A.size();
    for (int k = 0; k <= n; ++k)
    {
        using namespace discreture;
        auto U = combinations(A, k);
        check_compound_container(U, A, discreture::combinations(n, k));
    }
}

TEST(CompoundContainer, LexCombinations)
{
    std::vector<std::string> A = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    int n = A.size();
    for (auto k : NN(n))
    {
        using namespace discreture;
        auto U = discreture::lex_combinations(A, k);
        check_compound_container(U, A, discreture::lex_combinations(n, k));
    }
}

TEST(CompoundContainer, Permutations)
{
    std::vector<std::string> A = {"a", "b", "c", "d", "e"};
    int n = A.size();
    using namespace discreture;
    auto U = discreture::permutations(A);
    check_compound_container(U, A, discreture::permutations(n));
}
