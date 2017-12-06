#include "dyck_benchmark.hpp"
#include "TimeHelpers.hpp"
using namespace std;
using namespace dscr;

void testDyckPathsSpeed(int n)
{
	Chronometer C;
	dyck_paths X(n);

	llint i = 0;

	for (const auto& x : X)
	{
		if (x[0] == 1)
		{
			++i;
		}
	}

// 	std::cout << "i = " << i << '\n';
	std::cout << "Time taken to see all " << X.size() << " dyck paths of size " << n  << ": " << C.Reset() << "s" << '\n';
}
