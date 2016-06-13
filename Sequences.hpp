#pragma once

#include "Basic.hpp"
 
namespace dscr
{
	//////////////////////////////
	/// \brief n!
	/// \param n is a (small) nonnegative integer.
	/// \return n!
	//////////////////////////////
	using lluint = long long unsigned int;
	using llint = long long int;
	
	constexpr lluint factorial(lluint n)
	{
		lluint toReturn = 1;
		if (n < 2)
			return toReturn;
		for (lluint i = 2; i < n+1; ++i)
			toReturn *= i;
		return toReturn;
	}

	//////////////////////////////
	/// \brief The number of subsets of size r chosen from a set of size n
	/// \param n is a (small) nonnegative integer
	/// \param r is a small integer between 0 and n (inclusive)
	/// \return n!/(r!*(n-r)!)
	//////////////////////////////
	lluint binomial(lluint n, lluint r);
	
	//////////////////////////////
	/// \brief The n-th catalan number
	/// \param n is a (small) nonnegative integer
	/// \return binomial(2n,n)/(n+1)
	//////////////////////////////
	lluint catalan(lluint n);
	
	//////////////////////////////
	/// \brief The n-th motzkin number
	/// \param n is a (small) nonnegative integer
	/// \return M_n
	//////////////////////////////
	lluint motzkin(lluint n);
	
	
	//////////////////////////////
	/// \brief The n-th partition number
	/// \param n is a (small) nonnegative integer
	/// \return P_n
	//////////////////////////////
	lluint partition_number(lluint n);
	
	//////////////////////////////
	/// \brief The number of partitions of n with k parts
	/// \param n is a (small) nonnegative integer
	/// \param k <= n is a (small) nonnegative integer
	/// \return P_{n,k}
	//////////////////////////////
	lluint partition_number(lluint n,lluint k);
	
	//////////////////////////////
	/// \brief The number of permutations of n which have exactly k cycles.
	/// \param n is a (small) nonnegative integer
	/// \param k <= n is a (small) nonnegative integer
	/// \return The stirling number of the first kind S(n,k)
	//////////////////////////////
	lluint stirling1(lluint n,lluint k);
	
	//////////////////////////////
	/// \brief The number of partitions of a set of n elements with k parts
	/// \param n is a (small) nonnegative integer
	/// \param k <= n is a (small) nonnegative integer
	/// \return P_{n,k}
	//////////////////////////////
	llint stirling2(lluint n,lluint k);
}
