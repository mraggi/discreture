#pragma once

#include "Basic.hpp"
 
namespace dscr
{
	//////////////////////////////
	/// \brief A class to help store known and constant sequences, such as the factorial sequence.
	//////////////////////////////
	class Sequence
	{
	private:
		static vector<lluint> factorial; 
		static vector<vector<lluint>> binomial;
		static vector<lluint> catalan;
		static vector<lluint> motzkin;
		static vector<lluint> partitionNumbers;
		
		friend lluint factorial(suint n);
		friend lluint binomial(lluint n, lluint r);
		friend lluint catalan(suint n);
		friend lluint motzkin(suint n);
		friend lluint partition_number(suint n);
	};

	//////////////////////////////
	/// \brief n!
	/// \param n is a (small) nonnegative integer.
	/// \return n!
	//////////////////////////////
	lluint factorial(suint n);

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
	lluint catalan(suint n);
	
	//////////////////////////////
	/// \brief The n-th motzkin number
	/// \param n is a (small) nonnegative integer
	/// \return M_n
	//////////////////////////////
	lluint motzkin(suint n);
	
	lluint partition_number(suint n);
}
