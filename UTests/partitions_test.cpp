#include <numeric>

#include "partitions_test.hpp"
#include "TimeHelpers.hpp"

using namespace std;
using namespace dscr;

bool testPartitions()
{
	int n = 10;
	partitions X(n);

	for (const auto& x : X)
	{
		std::cout << x << '\n';

		if (std::accumulate(x.begin(), x.end(), 0) != n)
		{
			return false;
		}
	}

	basic_partitions<unsigned char> Y(8);

	for (const auto& y : Y)
	{
		std::cout << y << '\n';






	}

	return true;
}


void testPartitionsSpeed(int n)
{
	Chronometer C;
	int total = 0;
	int N = 120;
	int k = 10;
	partitions P(N, k);

	for (auto& p : P)
	{
		if (p[2] == 27)
		{
			++total;
		}
	}

	std::cout << "Time taken to see all " << P.size() << " partitions of size " << k  << ": " << C.Reset() << "s" << '\n';
	return;

	partitions X(n);

	llint i = 0;

	for (const auto& x : X)
	{
		if (x[0] == 3)
		{
			++i;
		}
	}

// 	std::cout << "i = " << i << '\n';
	std::cout << "Time taken to see all " << X.size() << " partitions of size " << n  << ": " << C.Reset() << "s" << '\n';
}


