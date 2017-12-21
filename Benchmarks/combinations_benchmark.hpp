#pragma once

#include "Combinations.hpp"
#include "do_not_optimize.hpp"
#include "Probability.hpp"

inline void BM_CombinationsConstruct(int n, int k, int numtimes)
{
	dscr::combinations_fast X(n, k);

	for (int i = 0; i < numtimes; ++i)
	{
		auto t = dscr::random::random_int<long>(0,X.size());
		DoNotOptimize(X[t]);
	}
}

inline void BM_CombinationsNAP(int n, int k)
{
	dscr::combinations_fast::combination comb(k);
	dscr::combinations_fast::combination::value_type hint = k;
	std::iota(comb.begin(), comb.end(), 0);
// 	int count = 0;
	do
	{
		DoNotOptimize(comb);
// 		++count;
// 		DoNotOptimize(count);
	} while(dscr::combinations_fast::next_combination(comb,hint,n));
}


