#pragma once
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/container/vector.hpp>

namespace dscr
{

//////////////////////////////////////////
/// \brief This is what operator % should be but isn't (!).
///
/// C++ modulo operator % is dumb for negative integers: (-7)%3 returns -1, instead of 2.
/// This fixes it.
/// \return an integer in [0,b)
//////////////////////////////////////////
template <class IntType>
inline IntType modulo(IntType a, IntType b)
{
	IntType r = a%b;
	if (r < 0)
		r += b;
	return r;
}

template <class T>
inline T pow(T a, unsigned long n)
{
	T r = 1;

	while (n > 0)
	{
		if (n & 1) // if odd
			r *= a;

		n /= 2;
		a *= a;
	}

	return r;
}

}
