#pragma once
#include "Basic.hpp"

namespace dscr
{
	


	//////////////////////////////////////////
	/// \brief This function of x is just the linear function from [a,b] to [u,v]
	/// \return f(x), where f:[a,b]->[u,v] is the only linear, monotone, biyective function.
	//////////////////////////////////////////
	inline double linear_convert(double x, double a, double b, double u, double v)
	{
		return (v-u)*(x-a)/(b-a)+u;
	}
	
	//////////////////////////////////////////
	/// \brief For those who hate typing fabs, labs, llabs instead of abs
	//////////////////////////////////////////
	inline long abs(long a)
	{
		return labs(a);
	}
	
	
	inline long long abs(long long a)
	{
		return llabs(a);
	}

	template <class NumType>
	inline NumType abs(NumType a)
	{
		if (a > 0)
			return a;
		return -a;
	}
	
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
		return (a+abs(a*b))%b;
	}
	
	//////////////////////////////////////////
	/// \brief Helper function to linearize tables
	//////////////////////////////////////////
	inline size_t twoD_to_oneD(unsigned x, unsigned y, unsigned width, unsigned height)
	{
		x %= width;
		y %= height;
		return (y*width+x);
	}

	//////////////////////////////////////////
	/// \brief Clamps x to be in the interval [a,b]
	//////////////////////////////////////////
	template <class T>
	inline T Clamped(T x, T a, T b)
	{
		if (a > b) { T temp = b; b = a; a = temp; }
		if (x < a) x = a;
		if (x > b) x = b;
		return x;
	}

	//////////////
	/// \brief Equivalent to x/|x| when x != 0, and 0 when x = 0
	/// \return 1 if val is positive, -1 if it's negative, and 0 if it's 0
	//////////////
	template <typename T> 
	int signof(T val) 
	{
		return (T(0) < val) - (val < T(0));
	}

}
