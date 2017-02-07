#include "combinations_test.hpp"
//#include <gsl/gsl_combination.h> // uncomment to test GSL combinations
#include "TimeHelpers.hpp"

using namespace dscr;

bool testCombinations()
{
	std::cout << "========== Testing Combinations ==========" << std::endl;

	std::cout << " Use test: " << std::endl;
	int n = 6;

	for (int r = 0; r <= n; ++r)
	{
		std::cout << " with r = " << r << std::endl;
		combinations X(n, r);
		size_t i = 0;

		for (const auto& x : X)
		{
			std::cout << "\t" << i << " == " << X.get_index(x) << " -> " << x << std::endl;

			if (i != X.get_index(x))
			{
				return false;
			}

			if (x != X[i])
			{
				return false;
			}

			++i;
		}
	}

	std::cout << "Large test" << std::endl;
	combinations X(10, 4);
	size_t i = 0;

	for (const auto& x : X)
	{
		std::cout << "\t" << i << " == " << X.get_index(x) << " -> " << x << std::endl;

		if (i != X.get_index(x))
		{
			return false;
		}

		++i;
	}

	// iterator operator tests
	std::cout << " Iterator operator tests" << std::endl;
	auto myIter = X.begin();
	std::cout << *(myIter + 23) << " == ";
	myIter += 46;
	std::cout << *(myIter - 23) << std::endl;
	int d = 76;
	std::cout << d << " == " << (myIter + d) - myIter << std::endl;


	// Checking correct order
	std::cout << " Correct order test: " << std::endl;

	for (auto it = X.begin(); it != X.end(); ++it)
	{
		auto itnext = it + 1;

		if (itnext == X.end())
			break;

		if (!X.compare(*it, *itnext))
			return false;
	}

	std::cout << "Reverse use test: " << std::endl;

	for (int r = 0; r <= n; ++r)
	{
		std::cout << "Starting with r = " << r << std::endl;
		basic_combinations<lluint> Y(n, r);
		i = 0;

		for (auto it = Y.rbegin(); it != Y.rend(); ++it, ++i)
		{
			std::cout << "\t" << i << " -> " << *it << " == " << Y[Y.size() - i - 1] << std::endl;

			if (*it != Y[Y.size() - i - 1])
				return false;
		}
	}

	std::cout << " Edge case test: " << std::endl;
	basic_combinations<unsigned char> Z(5, 8);

	for (const auto& z : Z)
	{
		std::cout << z << std::endl;
		return false;
	}

	std::cout << " find_if test: " << std::endl;
	combinations W(20, 6);

	auto predicate1 = [](const std::vector<int>& comb) -> bool
	{
		for (size_t i = 0; i < comb.size() - 1; ++i)
		{
			if (2 * comb[i] + 1 > comb[i + 1])
				return false;
		}

		return true;
	};
	auto predicate2 = [](const std::vector<int>& comb) -> bool
	{
		for (size_t i = 0; i < comb.size() - 1; ++i)
		{
			if (comb[i] + 3 < comb[i + 1])
				return false;

			if (comb[i] + 1 == comb[i + 1])
				return false;
		}

		return true;
	};

	auto iter = W.find_if(predicate1);

	if (iter != W.end())
	{
		std::cout << "Found this one: " << *iter << std::endl;

		if (!predicate1(*iter))
		{
			std::cout << "But it does NOT satisfy the predicate!" << std::endl;
			return false;
		}


	}
	else
	{

		std::cout << "No combination satisfies the condition" << std::endl;

		// verify that indeed no combination satisfies the predicate
		if (W.get_n() < 30)
		{
			for (const auto& w : W)
			{
				if (predicate1(w))
					return false;
			}

			std::cout << " and it checks out!!" << std::endl;
		}
		else
		{
			std::cout << "\tbut this W is too large to actually check one by one." << std::endl;
		}
	}

// 	return true;

	std::cout << "These are the combinations that satisfy the predicate: " << std::endl;
	auto T = W.find_all(predicate2);

	for (const auto& t : T)
		std::cout << t << std::endl;

	std::cout << "Checking one by one: " << std::endl;
	size_t numpred = 0;

	if (W.get_n() < 30)
	{
		for (const auto& w : W)
		{
			if (predicate2(w))
			{
				std::cout << w << std::endl;

				++numpred;
			}
		}

// 		if (numpred != T.size())
// 		{
// 			std::cout << "Error in find_all: a one-by-one check found a different number than a find_all check" << std::endl;
// 			return false;
// 		}
	}
	else
	{
		std::cout << "\tbut this W is too large to actually check one by one." << std::endl;
	}

	return true;
}

std::vector<int> differences(const std::vector<int>& x)
{
	std::vector<int> toReturn;
	toReturn.push_back(x[0]);

	for (size_t i = 0; i+1 < x.size(); ++i)
		toReturn.push_back(x[i + 1] - x[i] - 1);

	return toReturn;
}

bool testCombinationsTree()
{
	std::cout << "========== Testing Combination TREE ==========" << std::endl;

	std::cout << " Use test: " << std::endl;
	int n = 6;

	for (int r = 0; r <= n; ++r)
	{
		std::cout << " with r = " << r << std::endl;
		combinations_tree X(n, r);
		size_t i = 0;

		for (const auto& x : X)
		{
			std::cout << "\t" << i << " == " << X.get_index(x) << " -> " << x << std::endl;

			if (i != X.get_index(x))
				return false;

			if (x != X[i])
				return false;

			++i;
		}
	}

	std::cout << "Large test" << std::endl;
	combinations_tree X(10, 4);
	size_t i = 0;

	for (const auto& x : X)
	{
		std::cout << "\t" << i << " == " << X.get_index(x) << " -> " << x << std::endl;

		if (i != X.get_index(x))
			return false;

		++i;
	}

	// iterator operator tests
	std::cout << " Iterator operator tests" << std::endl;
	auto myIter = X.begin();
	std::cout << *(myIter + 23) << " == ";
	myIter += 46;
	std::cout << *(myIter - 23) << std::endl;
	int d = 76;
	std::cout << d << " == " << (myIter + d) - myIter << std::endl;


	// Checking correct order
	std::cout << " Correct order test: " << std::endl;

	for (auto it = X.begin(); it != X.end(); ++it)
	{
		auto itnext = it + 1;

		if (itnext == X.end())
			break;

		if (!X.compare(*it, *itnext))
			return false;
	}

	std::cout << "Reverse use test: " << std::endl;

	for (int r = 0; r <= n; ++r)
	{
		std::cout << "Starting with r = " << r << std::endl;
		basic_combinations_tree<lluint> Y(n, r);
		i = 0;

		for (auto it = Y.rbegin(); it != Y.rend(); ++it, ++i)
		{
			std::cout << "\t" << i << " -> " << *it << " == " << Y[Y.size() - i - 1] << std::endl;

			if (*it != Y[Y.size() - i - 1])
				return false;
		}
	}

	std::cout << " Edge case test: " << std::endl;
	basic_combinations_tree<unsigned char> Z(5, 8);

	for (const auto& z : Z)
	{
		std::cout << z << std::endl;
		return false;
	}

	combinations W(30, 3);
	auto T = W.find_all([](const std::vector<int>& A)
	{
		if (A.size() < 2)
			return true;

		int k = A.size();

		if (A[k - 2] == 0)
			return false;

		return A[k - 1] % A[k - 2] == 0;
	});
	std::cout << "Testing findall: " << std::endl;

	for (auto& t : T)
		std::cout << "t = " << t << std::endl;

// 	auto T2 = W.find_all_old([](const std::vector<int>& A)
// 	{
// 		if (A.size() < 2)
// 			return true;
// 		int k = A.size();
// 		if (A[k-2] == 0) return false;
// 		return A[k-1]%A[k-2] == 0;
// 	});
// 	std::cout << "Testing findall: " << std::endl;
// 	for (auto& t : T2)
// 		std::cout << "t2 = " << t << std::endl;



	return true;
}

void testCombinationsSpeed(int n, int k)
{
	Chronometer C;
	lluint i = 0;
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

	combinations Z(24, 12);
	size_t zi = 0;

	for (auto& z : Z)
	{
		if (z[3] == 1)
			++zi;
	}

	combinations W(100, 5);

	std::cout << "Time taken to see all (" << 24 << " choose " << 12 << ") = " << Z.size() << " combinations: " << C.Reset() << "s" <<  std::endl;

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


void testCombinationsTreeSpeed(int n, int k)
{
	Chronometer C;
	lluint i = 0;
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
}

void testManualCombinations()
{
	int i = 0;
	int n = 33;
	++n;
	--n;

	for (volatile int a00 = 0; a00 < n - 15; ++a00)
	for (volatile int a01 = a00 + 1; a01 < n - 14; ++a01)
	for (volatile int a02 = a01 + 1; a02 < n - 13; ++a02)
	for (volatile int a03 = a02 + 1; a03 < n - 12; ++a03)
	for (volatile int a04 = a03 + 1; a04 < n - 11; ++a04)
	for (volatile int a05 = a04 + 1; a05 < n - 10; ++a05)
	for (volatile int a06 = a05 + 1; a06 < n - 9; ++a06)
	for (volatile int a07 = a06 + 1; a07 < n - 8; ++a07)
	for (volatile int a08 = a07 + 1; a08 < n - 7; ++a08)
	for (volatile int a09 = a08 + 1; a09 < n - 6; ++a09)
	for (volatile int a10 = a09 + 1; a10 < n - 5; ++a10)
	for (volatile int a11 = a10 + 1; a11 < n - 4; ++a11)
	for (volatile int a12 = a11 + 1; a12 < n - 3; ++a12)
	for (volatile int a13 = a12 + 1; a13 < n - 2; ++a13)
	for (volatile int a14 = a13 + 1; a14 < n - 1; ++a14)
	for (volatile int a15 = a14 + 1; a15 < n; ++a15)
	{
		++n;

		if (a15 == 25 || n > 454)
			++i;

		--n;
	}

	std::cout << "total num: " << i << std::endl;
}


// void testGSLComb()
// {
// 	gsl_combination * c;
// 	size_t i = 0;
//
// 	for (int n = 8; n < 34; n += 1)
// 	{
// 		c = gsl_combination_calloc (n, n/2);
// 		do
// 		{
// 			if (gsl_combination_get(c,3) == 1)
// 				++i;
// 		}
// 		while (gsl_combination_next (c) == GSL_SUCCESS);
// 		gsl_combination_free (c);
//
// 		std::std::cout << "time for gsl combinations " << n << " choose " << n/2 <<  " = " << dscr::C.Reset() << std::std::endl;
// 	}
// }
