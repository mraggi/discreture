#pragma once

#include "Multisets.hpp"
#include "Probability.hpp"
#include "do_not_optimize.hpp"

inline void BM_MultisetFWD()
{
    discreture::multisets X(
      {2, 2, 1, 3, 4, 2, 3, 3, 2, 3, 4, 4, 5, 0, 0, 1, 0, 2, 2});
    for (auto&& x : X)
    {
        DoNotOptimize(x);
    }
}

inline void BM_MultisetReverse()
{
    discreture::multisets X(
      {2, 2, 1, 3, 4, 2, 3, 3, 2, 3, 4, 4, 5, 0, 0, 1, 0, 2, 2});
    for (auto it = X.rbegin(); it != X.rend(); ++it)
    {
        DoNotOptimize(*it);
    }
}

inline std::vector<int> get_random_multiset(int n)
{
    std::vector<int> result(n);

    std::generate(result.begin(), result.end(), []() {
        return discreture::random::random_int(0, 5);
    });

    return result;
}
