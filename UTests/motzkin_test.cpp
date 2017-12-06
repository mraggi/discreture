#include "motzkin_test.hpp"
#include "TimeHelpers.hpp"
#include "dyck_test.hpp"
using namespace dscr;

bool testMotzkin()
{
	std::cout << "============= Testing Motzkin Paths ============" << '\n';
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
