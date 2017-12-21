#pragma once

#include "Multisets.hpp"
#include "do_not_optimize.hpp"
#include "Probability.hpp"

inline void BM_MultisetFWD()
{
	dscr::multisets X({2, 2, 1, 3, 4, 2, 3, 3, 2, 3, 4, 4, 5, 0, 0, 1, 0, 2, 2});
	for (auto& x : X)
	{
		DoNotOptimize(x);
	}
}

inline std::vector<int> get_random_multiset(int n)
{
	std::vector<int> result(n);
	
	
	std::generate(result.begin(), result.end(), []()
	{
		return dscr::random::random_int(0,5);
	});
	
	
	return result;
}
