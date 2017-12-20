#pragma once

#include "Combinations.hpp"
#include "do_not_optimize.hpp"
#include "Probability.hpp"

inline void BM_CombinationsConstruct(int n, int k, int numtimes)
{
	dscr::combinations X(n, k);

	for (int i = 0; i < numtimes; ++i)
	{
		auto t = dscr::random::random_int<long>(0,X.size());
		DoNotOptimize(X[t]);
	}
}

#include "combinations_pureforward_iterator.hpp"

inline void BM_CombinationsLA(int n,int k)
{
	auto end = combination_iterator_pureforward<int>();

	for (auto it = combination_iterator_pureforward<int>(n, k); it != end; ++it)
	{
		DoNotOptimize(*it);
	}
}

inline void BM_CombinationsNAP(int n, int k)
{
	dscr::combinations::combination comb(k);
	dscr::combinations::combination::value_type hint = k;
	std::iota(comb.begin(), comb.end(), 0);
// 	int count = 0;
	do
	{
		DoNotOptimize(comb);
// 		++count;
// 		DoNotOptimize(count);
	} while(dscr::combinations::next_combination(comb,hint,n));
}


