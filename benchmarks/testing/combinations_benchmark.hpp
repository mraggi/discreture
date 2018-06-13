#pragma once

#include "Combinations.hpp"
#include "Probability.hpp"
#include "do_not_optimize.hpp"

inline void BM_CombinationsNAP(int n, int k)
{
    dscr::Combinations<int>::combination comb(k);
    dscr::Combinations<int>::size_type hint = k;
    dscr::Combinations<int>::combination::value_type last = k - 1;
    std::iota(comb.begin(), comb.end(), 0);
    do
    {
        DoNotOptimize(comb);
    } while (dscr::Combinations<int>::next_combination(n, comb, hint, last));
}

inline void BM_combinationsIterator(int n, int k, std::int64_t size)
{
    UNUSED(size);
    auto X = dscr::combinations(n, k);
    auto first = X.begin();
    auto last = X.end();
    for (; first != last; ++first)
    {
        DoNotOptimize(*first);
    }
}

template <class Iter>
void BM_typeSizeIter(int n, int k, std::int64_t size)
{
    auto first = Iter(n, k);
    auto last = Iter(size);
    for (; first != last; ++first)
    {
        DoNotOptimize(*first);
    }
}
