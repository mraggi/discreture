#include "Misc.hpp"
#include "Vectorhelpers.hpp"

namespace dscr
{
	luint factorial(luint n)
	{
		luint f = 1;
		for (luint i = 1; i < n+1; ++i)
			f *= i;
		return f;
	}
	
	
	luint binomial(nuint n, nuint r)
	{
		if (n < r)
			return 0;
		
		if (2*r > n)
			r = n-r;
		
		if (r == 0)
			return 1;
		
		if (r == 1)
			return n;
		
		return (n*binomial(n-1,r-1))/r;
	}
}