#include "dyck_test.hpp"
#include "TimeHelpers.hpp"
using namespace std;
using namespace dscr;




bool testDyckPaths()
{
	dyck_paths X(3);

	for (const auto& x : X)
	{
		std::cout << x << '\n';

		if (!dyckpathiscorrect(x))
		{
			return false;
		}
	}

	for (const auto& x : X)
	{
		std::cout << dyck_paths::to_string(x, "()") << '\n';


	}

	dyck_paths Y(0);

	for (const auto& x : Y)
	{
		std::cout << x << '\n';

	}

	return true;
}


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
