#include "multisets_test.hpp"
#include "TimeHelpers.hpp"
using namespace dscr;

bool testMultiset()
{
	std::cout << "========== Testing Multisets ==========" << std::endl;
	
	std::vector<int> h = {1, 0, 3, 1};
	multisets X(h);

	
	std::cout << "Here are all sub multisets of [" << h << "]\n";
	for (const auto& x : X)
	{
		std::cout << x << '\n';
		for (int i = 0; i < x.size(); ++i)
		{
			if (x[i] < 0 || x[i] > h[i])
				return false;
		}

	}

	return true;
}
