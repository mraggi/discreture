#pragma once

#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "Misc.hpp"

namespace dscr
{
// Typedefs
// 	typedef std::vector<bool> std::vector<bool>;
// 	typedef std::vector<char> VC;
// 	typedef std::vector<sint> VSI;
// 	typedef std::vector<int> VI;
// 	typedef std::vector<lint> VLI;
//
// 	typedef std::vector<nuint> VUI;
// 	typedef std::vector<suint> VSUI;
// 	typedef std::vector<size_t> VLUI;
// 	typedef std::vector<uchar> std::vector<unsigned char>;
//
// 	typedef std::vector<double> VR;

//////////////////////////////////////
/// \brief Bitwise and for std::vector<bool>
//////////////////////////////////////
std::vector<bool> operator&(const std::vector<bool>& A, const std::vector<bool>& B);

//////////////////////////////////////
/// \brief Bitwise or for std::vector<bool>
//////////////////////////////////////
std::vector<bool> operator|(const std::vector<bool>& A, const std::vector<bool>& B);

////////////////////////////////////
/// \brief Converts a std::vector<U> into a std::vector<T>, provided U can be converted to T
////////////////////////////////////
template<typename T, typename U>
std::vector<T> Convert(const std::vector<U>& G)
{
	auto n = G.size();
	std::vector<T> toReturn(n, 0);

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
	for (auto it = V.begin(); it != V.end(); ++it)
	{
		os << *it;
		if (it+1 != V.end())
			os << " ";
	}

	return os;
}

////////////////////////////////////
/// \brief Find the minimum value of a std::vector.
////////////////////////////////////
template <class T>
T min(const std::vector<T>& v)
{
	assert(v.size() > 0);
	T m = v[0];

	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < m)
			m = v[i];
	}

	return m;
}

////////////////////////////////////
/// \brief Find the max value of a std::vector.
////////////////////////////////////
template <class T>
T max(const std::vector<T>& v)
{
	assert(v.size() > 0);
	T m = v[0];

	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] > m)
			m = v[i];
	}

	return m;
}

////////////////////////////////////
/// \brief Find the minimum index of a std::vector.
////////////////////////////////////
template <class T>
size_t argmin(const std::vector<T>& v)
{
	assert(v.size() > 0);
	T m = v[0];
	size_t bestisofar = 0;

	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i] < m)
		{
			m = v[i];
			bestisofar = i;
		}
	}

	return bestisofar;
}

////////////////////////////////////
/// \brief Find the maximum index of a std::vector.
////////////////////////////////////
template <class T>
size_t argmax(const std::vector<T>& v)
{
	assert(v.size() > 0);
	T m = v[0];
	size_t bestisofar = 0;

	for (size_t i = 0; i < v.size(); ++i)
	{
		if (m < v[i])
		{
			m = v[i];
			bestisofar = i;
		}
	}

	return bestisofar;
}


////////////////////////////////////
/// \brief std::vector coordinate-wise addition.
////////////////////////////////////
template<class T>
inline std::vector<T> operator+(const std::vector<T>& U, const std::vector<T>& V)
{
	assert(U.size() == V.size());
	auto toReturn = U;

	for (size_t i = 0; i < U.size(); ++i)
	{
		toReturn[i] += V[i];
	}

	return toReturn;
}


////////////////////////////////////
/// \brief inplace std::vector coordinate-wise addition.
////////////////////////////////////
template<class T>
inline void operator+=(std::vector<T>& U, const std::vector<T>& V)
{
	assert(U.size() == V.size());

	for (size_t i = 0; i < U.size(); ++i)
	{
		U[i] += V[i];
	}
}

////////////////////////////////////
/// \brief inplace std::vector coordinate-wise division by a number.
////////////////////////////////////
template<class T, class NumType>
inline void operator/=(std::vector<T>& U, NumType t)
{
	//assert(U.size() == V.size());
	for (size_t i = 0; i < U.size(); ++i)
	{
		U[i] /= t;
	}
}

////////////////////////////////////
/// \brief inplace std::vector coordinate-wise multiplication by a number.
////////////////////////////////////
template<class T, class NumType>
inline void operator*=(std::vector<T>& U, NumType t)
{
	//assert(U.size() == V.size());
	for (size_t i = 0; i < U.size(); ++i)
	{
		U[i] *= t;
	}
}

////////////////////////////////////
/// \brief coordinate-wise multiplication by a number.
////////////////////////////////////
template<class T, class NumType>
inline std::vector<T> operator*(std::vector<T> U, NumType t)
{
	//assert(U.size() == V.size());
	U *= t;
	return U;
}

////////////////////////////////////
/// \brief coordinate-wise division by a number.
////////////////////////////////////
template<class T, class NumType>
inline std::vector<T> operator/(std::vector<T> U, NumType t)
{
	//assert(U.size() == V.size());
	U /= t;
	return U;
}

//////////////////////////
/// \brief returns a std::vector W such that for each coordinate i, W[i] = min(V[i],U[i])
//////////////////////////
template<class T>
inline std::vector<T> mincac(const std::vector<T>& U, const std::vector<T>& V)
{
	assert(U.size() == V.size());
	std::vector<T> toReturn(U.size());

	for (size_t i = 0; i < U.size(); ++i)
	{
		toReturn[i] = std::min(U[i], V[i]);
	}

	return toReturn;
}

//////////////////////////
/// \brief returns a std::vector W such that for each coordinate i, W[i] = max(V[i],U[i])
//////////////////////////
template<class T>
inline std::vector<T> maxcac(const std::vector<T>& U, const std::vector<T>& V)
{
	assert(U.size() == V.size());
	std::vector<T> toReturn(U.size());

	for (size_t i = 0; i < U.size(); ++i)
	{
		toReturn[i] = std::max(U[i], V[i]);
	}

	return toReturn;
}

// 	std::ostream& operator<<(std::ostream& os, const VUI& V);
// 	std::ostream& operator<<(std::ostream& os, const VSUI& V);

/////////////////////////////
/// \brief Specialization for std::vector printouts for std::vector<unsigned char>
/////////////////////////////
inline std::ostream& operator<<(std::ostream& os, const std::vector<unsigned char>& V);

/////////////////////////////
/// \brief Specialization for std::vector printouts for std::vector<bool> so that it doesn't print out spaces
/////////////////////////////
inline std::ostream& operator<<(std::ostream& os, const std::vector<bool>& V);




///////////////////////////
/// \brief Given a subset S, written in combination form (1,2,4), returns the same subset written in subset form (01101)
///////////////////////////
template <class T>
std::vector<bool> CombinationToSubset(const std::vector<T>& C, size_t size)
{
	std::vector<bool> toReturn(size, 0);

	for (size_t i = 0; i < C.size(); ++i)
	{
		assert(C[i] < size);
		toReturn[C[i]] = 1;
	}

	return toReturn;
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

template <class T>
bool AreTheyAllDifferent(const std::vector<T>& G)
{
	std::vector<T> copyG = G;
	std::sort(copyG.begin(), copyG.end());

	for (size_t i = 0; i < copyG.size() - 1; ++i)
	{
		if (G[i] == G[i + 1])
		{
			return false;
		}
	}

	return true;
}

inline
std::vector<bool> operator&(const std::vector<bool>& A, const std::vector<bool>& B)
{
	size_t size = std::min(A.size(), B.size());
	std::vector<bool> G;

	for (size_t i = 0; i < size; i++)
		G.push_back(A[i] && B[i]);

	return G;
}

inline
std::vector<bool> operator|(const std::vector<bool>& A, const std::vector<bool>& B)
{
	size_t size = std::min(A.size(), B.size());
	std::vector<bool> G;

	for (size_t i = 0; i < size; i++)
		G.push_back(A[i] || B[i]);

	return G;
}

inline
std::ostream& operator<<(std::ostream& os, const std::vector<unsigned>& V)
{
	for (size_t i = 0; i < V.size(); ++i)
		os << V[i] << " ";

	return os;
}

inline
std::ostream& operator<<(std::ostream& os, const std::vector<unsigned char>& V)
{
	for (size_t i = 0; i < V.size(); ++i)
		os << short(V[i]) << " ";

	return os;
}

inline
std::ostream& operator<<(std::ostream& os, const std::vector<bool>& V)
{

	for (size_t i = 0; i < V.size(); ++i)
		os << V[i];

	return os;
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
			os << V[x][y] << " ";
		}
	}

	return os;
}

}
