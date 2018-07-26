#include "discreture.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <set>

using namespace std;
using namespace discreture;

template <class Container>
void check_reversed_iterator(const Container& original)
{
    ASSERT_EQ(original.size(), reversed(original).size());

    auto rit = original.rbegin();

    for (auto&& x : reversed(original))
    {
        ASSERT_EQ(x, *rit);
        ++rit;
    }
    ASSERT_EQ(rit, original.rend());
}

template <class Container>
void check_reversed_manual(const Container& original)
{
    using value_type = typename Container::value_type;
    std::vector<value_type> O(original.begin(), original.end());
    auto R = O;
    std::reverse(R.begin(), R.end());

    std::vector<value_type> RO(reversed(original).begin(),
                               reversed(original).end());

    int i = 0;
    for (auto&& x : reversed(O))
    {
        ASSERT_EQ(R[i], x);
        ASSERT_EQ(R[i], RO[i]);
        ++i;
    }
    ASSERT_EQ(i, original.size());
}

template <class Container>
void check_reversed(const Container& original)
{
    check_reversed_iterator(original);
    check_reversed_manual(original);
}

TEST(Reversed, Vector)
{
    std::vector<int> A = {1, 4, 3, 6, 5, 4, 8};
    check_reversed(A);

    std::vector<int> empty;
    check_reversed(empty);
}

TEST(Reversed, String)
{
    std::string A = "Hello World!";
    check_reversed(A);

    std::string empty;
    check_reversed(empty);
}

TEST(Reversed, DiscretureContainers)
{
    check_reversed(discreture::combinations(6, 2));
    check_reversed(discreture::lex_combinations(6, 2));
    check_reversed(discreture::permutations(5));
    check_reversed(discreture::multisets(5, 2));
    check_reversed(discreture::partitions(8));
    check_reversed(discreture::integer_interval(2, 7));
    check_reversed(discreture::arithmetic_progression(40, 10, -3));
    check_reversed(discreture::arithmetic_progression(40, 70, 2));
    check_reversed(discreture::arithmetic_progression(40, 70, 200));
}
