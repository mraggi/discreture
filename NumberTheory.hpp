#pragma once
#include <vector>

namespace dscr
{
	using std::vector;
	using std::size_t;

	template <class T>
	T gcd(T a,T b)
	{
		if (b == 0) return a;
		return gcd(b,a%b);
	}

	template <class T>
	T lcm(T a, T b)
	{
		return a*b/gcd(a,b);
	}

	template <class T>
	T gcd(const vector<T>& A)
	{
		auto a = A.front();
		
		for (size_t i = 1; i < A.size(); ++i)
		{
			a = gcd(a, A[i]);
		}
		return a;
	}

	template <class T>
	T lcm(const vector<T>& A)
	{
		auto a = A.front();
		
		for (size_t i = 1; i < A.size(); ++i)
		{
			a = lcm(a, A[i]);
		}
		return a;
	} 
};
