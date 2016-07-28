#pragma once
#include <vector>
#include <algorithm>
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
	
	
	template <class IntType>
	long InterpretBaseK(long k, const vector<IntType>& bla)
	{
		long suma = 0;
		long power = 1;
		for (auto it = bla.rbegin(); it != bla.rend(); ++it)
		{
			suma += power*static_cast<IntType>(*it);
			power *= k;
		}
		return suma;
	}

	inline vector<unsigned char> NumberBaseB(unsigned n, unsigned char b)
	{
		vector<unsigned char> toReturn;
		while (n)
		{
			toReturn.push_back(n%b);
			n /= b;
		}
		std::reverse(toReturn.begin(), toReturn.end());
		return toReturn;
	}

};
