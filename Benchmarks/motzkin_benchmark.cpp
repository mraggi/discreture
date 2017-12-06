#include "motzkin_benchmark.hpp"
#include "dyck_benchmark.hpp"
#include "TimeHelpers.hpp"
using namespace dscr;

void testMotzkinSpeed(int n)
{
	Chronometer C;
	motzkin_paths X(n);

	llint i = 0;

	for (const auto& x : X)
	{
		if (x[0] == 1)
		{
			++i;
		}
	}

// 	std::cout << "i = " << i << '\n';
	std::cout << "Time taken to see all " << X.size() << " motzkin paths of size " << n  << ": " << C.Reset() << "s" << '\n';
}
