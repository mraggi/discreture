#include <algorithm>
#include <numeric>
#include "combinations_benchmark.hpp"
#include "TimeHelpers.hpp"
#include "do_not_optimize.hpp"

using namespace dscr;

void testCombinationsSpeed(int n, int k)
{
	Chronometer C;
	llint i = 0;
	combinations X(n, k);

	for (auto& x : X)
	{
		if (x[0] == 1)
			++i;
	}

	std::cout << "Time taken to see all (" << n << " choose " << k << ") = " << X.size() << " combinations: " << C.Reset() << "s" <<  std::endl;

	i = 0;

	for (auto it = X.rbegin(); it != X.rend(); ++it)
	{
		if ((*it)[0] == 1)
			++i;
	}

	std::cout << "Time taken to see all (" << n << " choose " << k << ") = " << X.size() << " combinations in reverse order: " << C.Reset() << "s" <<  std::endl;

	i = 0;
	X.for_each([&i](const combinations::combination& x)
	{
		DoNotOptimize(x);
	});
	
	std::cout << "Time taken to apply a function to all (" << n << " choose " << k << ") = " << X.size() << " combinations: " << C.Reset() << "s" <<  std::endl;
	
	combinations Z(24, 12);
	size_t zi = 0;

	for (auto& z : Z)
	{
		if (z[0] == 1)
			++i;
	}


	std::cout << "Time taken to see all (" << Z.get_n() << " choose " << Z.get_k() << ") = " << Z.size() << " combinations: " << C.Reset() << "s" <<  std::endl;

	combinations W(100, 5);
	auto T = W.find_all([](const std::vector<int>& A)
	{
		if (A.size() < 2)
			return true;

		int k = A.size();
		return A[k - 1] > A[k - 2] + 2;
	});
	int num = 0;

	for (auto& t : T)
	{
		if (t[0] == 0)
			++num;
	}

	std::cout << "Time taken find all " << num << " combinations satisfying a predicate: " << C.Reset() << "s" <<  std::endl;

	auto T2 = W.get_all([](const std::vector<int>& A)
	{
		if (A.size() < 2)
			return true;

		int k = A.size();
		return A[k - 1] > A[k - 2] + 2;
	});
	int num2 = 0;

	for (auto& t2 : T2)
	{
		if (t2[0] == 0)
			++num2;
	}

	std::cout << "Time taken to find all " << num2 << " combinations satisfying a predicate old: " << C.Reset() << "s" <<  std::endl;
// 	throw;
}

#ifdef TEST_GSL_COMBINATIONS
#include <gsl/gsl_combination.h>
void testGSLComb(int n, int k)
{
	gsl_combination * c;
	size_t i = 0;

	Chronometer C;
// 	for (int n = 8; n < 34; n += 1)
// 	{
		c = gsl_combination_calloc (n, k);
		do
		{
			if (gsl_combination_get(c,0) == 1)
				++i;
		}
		while (gsl_combination_next (c) == GSL_SUCCESS);
		gsl_combination_free (c);

		std::cout << "Time taken to see all (" << n << " choose " << k << ") = " << binomial(n,k) << " combinations with GNU Scientific Library (GSL): " << C.Reset() << "s" <<  std::endl;
// 	}
}
#endif


void testCombinationsTreeSpeed(int n, int k)
{
	Chronometer C;
	llint i = 0;
	combinations_tree X(n, k);

	for (auto& x : X)
	{
		if (x[0] == 1)
			++i;
	}

	std::cout << "Time taken to see all (" << n << " choose " << k << ") = " << X.size() << " combinations in TREE ORDER: " << C.Reset() << "s" <<  std::endl;

	i = 0;

	for (auto it = X.rbegin(); it != X.rend(); ++it)
	{
		if ((*it)[0] == 1)
			++i;
	}

	std::cout << "Time taken to see all (" << n << " choose " << k << ") = " << X.size() << " combinations in REVERSE TREE ORDER: " << C.Reset() << "s" <<  std::endl;
	
	
#ifdef TEST_GSL_COMBINATIONS
	testGSLComb(n,k);
#endif
}

