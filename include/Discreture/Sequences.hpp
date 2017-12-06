#pragma once
#include <vector>
#include <iostream>
#include "Misc.hpp"
namespace dscr
{
using llint = long long int;


//////////////////////////////
/// \brief n!
/// \param n is a (small) nonnegative integer.
/// \return n!
//////////////////////////////
inline llint factorial(llint n);

//////////////////////////////
/// \brief The number of subsets of size r chosen from a set of size n
/// \param n is a (small) nonnegative integer
/// \param r is a small integer between 0 and n (inclusive)
/// \return n!/(r!*(n-r)!)
//////////////////////////////
inline llint binomial(llint n, llint r);

//////////////////////////////
/// \brief The n-th catalan number
/// \param n is a (small) nonnegative integer
/// \return binomial(2n,n)/(n+1)
//////////////////////////////
inline llint catalan(llint n);

//////////////////////////////
/// \brief The n-th motzkin number
/// \param n is a (small) nonnegative integer
/// \return M_n
//////////////////////////////
inline llint motzkin(llint n);


//////////////////////////////
/// \brief The n-th partition number
/// \param n is a (small) nonnegative integer
/// \return P_n
//////////////////////////////
inline llint partition_number(llint n);

//////////////////////////////
/// \brief The number of partitions of n with k parts
/// \param n is a (small) nonnegative integer
/// \param k <= n is a (small) nonnegative integer
/// \return P_{n,k}
//////////////////////////////
inline llint partition_number(llint n, llint k);

//////////////////////////////
/// \brief The number of permutations of n which have exactly k cycles.
/// \param n is a (small) nonnegative integer
/// \param k <= n is a (small) nonnegative integer
/// \return The stirling number of the first kind S(n,k)
//////////////////////////////
inline llint stirling_cycle_number(llint n, llint k);

//////////////////////////////
/// \brief The number of partitions of a set of n elements with k parts
/// \param n is a (small) nonnegative integer
/// \param k <= n is a (small) nonnegative integer
/// \return P_{n,k}
//////////////////////////////
inline llint stirling_partition_number(llint n, llint k);

//////////////////////////////
/// \brief The generalized pentagonal numbers (see oeis sequence A001318)
/// \param n is a (small) nonnegative integer
/// \return p_n
//////////////////////////////
inline llint generalized_pentagonal(llint n);

inline llint factorial(llint n)
{
	llint toReturn = 1;

	if (n < 2)
		return toReturn;

	for (llint i = 2; i <= n; ++i)
		toReturn *= i;

	return toReturn;
}


inline llint binomial(llint n, llint k)
{
	if (k > n)
		return 0;

	if (k > n - k)
		k = n - k;

	static std::vector<std::vector<llint>> B = { { 1 },
		{ 1 },
		{ 1,  2 },
		{ 1,  3 },
		{ 1,  4,  6 },
		{ 1,  5,  10 },
		{ 1,  6,  15,  20 }
	};
	size_t m = B.size();

	if (n < m)
		return B[n][k];

	B.resize(n + 1, {1});

	for (; m < n + 1; ++m)
	{
		auto last = (m + 2) / 2 - 1;
		B[m].resize(last + 1);

		for (size_t r = 1; r < last; ++r)
		{
			B[m][r] = B[m - 1][r - 1] + B[m - 1][r];
		}

		if (m % 2 == 0)
			B[m][last] = 2 * B[m - 1][last - 1];
		else
			B[m][last] = B[m - 1][last] + B[m - 1][last - 1];
	}

// 		for (int i = 0; i < B.size(); ++i)
// 			cout << i << ":  " << B[i] << endl;
	return B[n][k];

}

llint catalan(llint n)
{
	static const std::vector<llint> C = {1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420, 24466267020, 91482563640, 343059613650, 1289904147324, 4861946401452};

	if (n < C.size())
		return C[n];

	return binomial(2 * n, n) / (n + 1); // May be useful someday, if decide to use gmp or something. It would be much slower.
}

inline llint motzkin(llint n)
{
	static const std::vector<llint> M = {1, 1, 2, 4, 9, 21, 51, 127, 323, 835, 2188, 5798, 15511, 41835, 113634, 310572, 853467, 2356779, 6536382, 18199284, 50852019, 142547559, 400763223, 1129760415, 3192727797, 9043402501, 25669818476, 73007772802, 208023278209, 593742784829};

	if (n < M.size())
		return M[n];

	return ((2 * n + 1) * motzkin(n - 1) + (3 * n - 3) * motzkin(n - 2)) / (n + 2); // May be useful someday
}

inline llint generalized_pentagonal(llint n)
{
	llint sign = (n%2)*2 - 1;
	n = sign*(n+1)/2;
	return (n*(3*n-1))/2;
}


inline llint partition_number(llint n)
{
	static std::vector<llint> P = {1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101 };
	
	llint oldsize = P.size();
	
	if (n < oldsize)
		return P[n];
	
	P.resize(n+1,0);
	for (llint m = oldsize; m <= n; ++m)
	{
		llint sign = 1;
		llint count = 0;
		for (llint k = 1; generalized_pentagonal(k) <= m; ++k)
		{
			P[m] += P[m-generalized_pentagonal(k)]*sign;
			++count;
			if (count == 2)
			{
				sign *= -1;
				count = 0;
			}
		}
	}
	
	return P[n];
}

inline llint partition_number(llint n, llint k)
{
	static std::vector<std::vector<llint>> PNK =
	{
		{1},
		{0, 1},
		{0, 1, 1},
		{0, 1, 1, 1},
		{0, 1, 2, 1, 1},
		{0, 1, 2, 2, 1, 1}
	};

	if (n < PNK.size())
		return PNK[n][k];

	if (k == 0 || n == 0)
		return 0;
	
	if (k == n || k == 1)
		return 1;
	
	llint oldsize = PNK.size();
	
	for (llint m = oldsize; m <= n; ++m)
	{
		PNK.emplace_back(m+1,0);
		for (llint l = 1; l <= m; ++l)
		{
			llint left = 0;
			if (m-l >= l)
				left = PNK[m-l][l];
			
			PNK[m][l] = left + PNK[m-1][l-1];
		}
	}
	

	return PNK[n][k];
}

inline llint stirling_cycle_number(llint n, llint k)
{
	static std::vector<std::vector<llint>> S1 =
	{
		{1},
		{0, 1},
		{0, 1, 1},
		{0, 2, 3, 1},
		{0, 6, 11, 6, 1}
	};
	
	llint oldsize = S1.size();
	if (n < oldsize)
		return S1[n][k];
	
	for (llint m = oldsize; m <= n; ++m)
	{
		S1.emplace_back(m+1,0);
		for (llint l = 1; l <= m; ++l)
		{
			llint left = 0;
			if (l < m)
				left = (m-1)*S1[m-1][l];
			S1[m][l] = left + S1[m-1][l-1];
		}
	}
	
	return S1[n][k];
}

inline llint stirling_partition_number(llint n, llint k)
{
	static std::vector<std::vector<llint>> S2 =
	{
		{1},
		{0, 1},
		{0, 1, 1},
		{0, 1, 3, 1},
		{0, 1, 7, 6, 1}
	};
	
	llint oldsize = S2.size();
	if (n < oldsize)
		return S2[n][k];
	
	for (llint m = oldsize; m <= n; ++m)
	{
		S2.emplace_back(m+1,0);
		for (llint l = 1; l <= m; ++l)
		{
			llint left = 0;
			if (l < m)
				left = l*S2[m-1][l];
			S2[m][l] = left + S2[m-1][l-1];
		}
	}
	
	return S2[n][k];
}
}
