#include <numeric>

#include "partitions_test.hpp"
#include "TimeHelpers.hpp"

using namespace std;
using namespace dscr;

bool testPartitions()
{
	std::cout << "============= Testing Partitions ============" << '\n';

	int n = 10;
	partitions X(n);

	std::cout << "Here are all partitions of " << n << std::endl;
	for (const auto& x : X)
	{
		std::cout << x << '\n';

		if (std::accumulate(x.begin(), x.end(), 0) != n)
		{
			return false;
		}
	}

	return true;
}


