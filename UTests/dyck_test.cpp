#include "dyck_test.hpp"
#include "TimeHelpers.hpp"
using namespace std;
using namespace dscr;




bool testDyckPaths()
{
	std::cout << "============= Testing Dyck Paths ============" << std::endl;

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
