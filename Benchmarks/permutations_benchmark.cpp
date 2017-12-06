#include "permutations_benchmark.hpp"
#include "TimeHelpers.hpp"

using namespace dscr;

void testPermutationsSpeed(int n)
{
	Chronometer C;
	permutations X(n);

	llint i = 0;

	for (const auto& x : X)
	{
		if (x[0] == 3)
		{
			++i;
		}
	}

// 	std::cout << "i = " << i << '\n';
	std::cout << "Time taken to see all " << n << "! = " << X.size() << " permutations: " << C.Reset() << "s" << '\n';


}
