#pragma once

#include "Combinations.hpp"
#include "do_not_optimize.hpp"

inline void BM_CombinationsTreeNAP(int n, int k)
{
	dscr::combinations_tree::combination comb(k);
	std::iota(comb.begin(), comb.end(), 0);
	int count = 0;
	auto size = dscr::binomial<long>(n,k);
	for ( ; count < size; ++count)
	{
		DoNotOptimize(comb);
		dscr::combinations_tree::next_combination(comb,n);
	}
}

inline long BM_CombinationsTreeFindAll(int n, int k)
{
	dscr::combinations_tree W(n, k);
	auto T = W.find_all([](const dscr::combinations_tree::combination & A)
	{
		if (A.size() < 2)
			return true;

		long k = A.size();
		return A[k - 1] > A[k - 2] + 2;
	});
	
	long size = 0;
	for (auto& t : T)
	{
		DoNotOptimize(t);
		++size;
	}
	return size;
}

inline void BM_CombinationsTreeConstruct(int n, int k, int numtimes)
{
	dscr::combinations_tree X(n, k);

	for (int i = 0; i < numtimes; ++i)
	{
		auto t = dscr::random::random_int<long>(0,X.size());
		DoNotOptimize(X[t]);
	}
}

#include "external/euler314_combination_iterator.hpp"

inline void BM_CombinationsTreeEuler314(int n,int k)
{
	auto end = combination_iterator<long>();

	for (auto it = combination_iterator<long>(n, k); it != end; ++it)
	{
		DoNotOptimize(*it);
	}
}


#ifdef TEST_GSL_COMBINATIONS
#include <gsl/gsl_combination.h>
inline void BM_CombinationsTreeGSL(int n, int k)
{
	gsl_combination* c;

	c = gsl_combination_calloc(n, k);

	do
	{
		DoNotOptimize(*c);
	}
	while (gsl_combination_next(c) == GSL_SUCCESS);

	gsl_combination_free(c);
}
#endif
