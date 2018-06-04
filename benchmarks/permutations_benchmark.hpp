#pragma once

#include "Permutations.hpp"
#include "Probability.hpp"
#include "do_not_optimize.hpp"

inline void BM_PermutationsRandom(int n, int numtimes)
{
    auto X = dscr::permutations(n);

    for (int i = 0; i < numtimes; ++i)
    {
        DoNotOptimize(X.random());
    }
}
