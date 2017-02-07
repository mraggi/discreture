#include "motzkin_test.hpp"
#include "dyck_test.hpp"
#include "TimeHelpers.hpp"
using namespace dscr;

bool testMotzkin()
{
	motzkin_paths X(4);

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
		std::cout << motzkin_paths::to_string(x) << '\n';


	}

	return true;
}



void testMotzkinSpeed(int n)
{
	Chronometer C;
	motzkin_paths X(n);

	lluint i = 0;

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
