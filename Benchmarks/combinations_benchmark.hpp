#pragma once

#include "Combinations.hpp"
#include "do_not_optimize.hpp"
#include "Probability.hpp"

inline void BM_CombinationsConstruct(int n, int k, int numtimes)
{
	dscr::combinations X(n, k);

	for (int i = 0; i < numtimes; ++i)
	{
		auto t = dscr::random_int<long>(0,X.size());
		DoNotOptimize(X[t]);
	}
}

#include "external/euler314_combination_iterator.hpp"

inline void BM_CombinationsEuler314(int n,int k)
{
	auto end = combination_iterator_minimax_order<long>();

	for (auto it = combination_iterator_minimax_order<long>(n, k); it != end; ++it)
	{
		DoNotOptimize(*it);
	}
}
