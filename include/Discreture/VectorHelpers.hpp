#pragma once

#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "Misc.hpp"

namespace dscr
{


////////////////////////////////////
/// \brief Converts a std::vector<U> into a std::vector<T>, provided U can be converted to T
////////////////////////////////////
template<typename T, typename U>
std::vector<T> Convert(const std::vector<U>& G)
{
	auto n = G.size();
	std::vector<T> toReturn(n);

	for (size_t i = 0; i  < n; ++i)
	{
		toReturn[i] = static_cast<T>(G[i]);
	}

	return toReturn;
}

////////////////////////////////////
/// \brief prints out a space separated std::vector.
////////////////////////////////////
template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& V)
{
	if (V.empty())
		return os;
	auto it = V.begin();
	os << *it;
	++it;
	for ( ; it != V.end(); ++it)
	{
		os << ' ' << *it;
	}

	return os;
}

////////////////////////////////////
/// \brief prints out a matrix
////////////////////////////////////
template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& V)
{
	os << std::endl;
	for (auto& v : V)
		os << v << std::endl;

	return os;
}

/////////////////////////////
/// \brief Specialization for std::vector printouts for std::vector<char>
/////////////////////////////
inline
std::ostream& operator<<(std::ostream& os, const std::vector<unsigned char>& V)
{
	if (V.empty())
		return os;
	auto it = V.begin();
	os << *it;
	++it;
	for ( ; it != V.end(); ++it)
	{
		os << ' ' << short(*it);
	}

	return os;
}

/////////////////////////////
/// \brief Specialization for std::vector printouts for std::vector<bool> so that it doesn't print out spaces
/////////////////////////////
inline
std::ostream& operator<<(std::ostream& os, const std::vector<bool>& V)
{

	for (bool v : V)
		os << v;

	return os;
}





///////////////////////////
/// \brief Function composition
///
/// \return f o g
///////////////////////////
template <class vecT, class UIntType>
vecT compose(const vecT& f, const std::vector<UIntType>& g)
{
// 		typename vecT::value_type u(0);
	vecT toReturn(g.size());

	for (size_t i = 0; i < g.size(); ++i)
	{
		assert(g[i] < f.size());
		toReturn[i] = f[g[i]];
	}

	return toReturn;
}





inline
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<bool>>& V)
{
	if (V.size() == 0)
		return os;

	size_t ncols = V.size();
	size_t nrows = V[0].size();

	for (size_t y = 0; y < nrows; ++y)
	{
		for (size_t x = 0; x < ncols; ++x)
		{
			os << V[x][y];
		}
		os << std::endl;
	}

	return os;
}

}
