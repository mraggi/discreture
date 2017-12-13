#include "set_partitions_benchmark.hpp"
#include "TimeHelpers.hpp"
using namespace dscr;

void testSetPartitionSpeed(int n)
{
	Chronometer C;
	set_partitions X(n);

	llint i = 0;

	for (const auto& x : X)
	{
		if (x[0][1] == 3)
		{
			++i;
		}
	}

// 	std::cout << "i = " << i << '\n';
	std::cout << "Time taken to see all " << X.size() << " set partitions of size " << n  << ": " << C.Reset() << "s" << '\n';

	set_partitions Y(n + 2, 4);

	i = 0;

	for (const auto& y : Y)
	{
		if (y[0][1] == 3)
		{
			++i;
		}
	}

// 	std::cout << "i = " << i << '\n';
	std::cout << "Time taken to see all " << Y.size() << " set partitions a set of " << n + 2 << " elements with " << 4 << " parts: " << C.Reset() << "s" << '\n';

	set_partitions Z(2 * n, 2);

	for (auto& z : Z)
	{
		if (z[0][0] == 3)
		{
			++i;
		}
	}

	std::cout << "Time taken to see all " << Z.size() << " set partitions a set of " << 2 * n << " elements with " << 2 << " parts: " << C.Reset() << "s" << '\n';
}

