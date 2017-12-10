#include <gtest/gtest.h>
#include <iostream>
#include "Partitions.hpp"
#include <set>
#include <numeric>

using namespace std;
using namespace dscr;

void check_partition(const partitions::partition& x, int n)
{
	int suma = std::accumulate(x.begin(), x.end(), 0);
		
	ASSERT_EQ(suma,n);
	
	ASSERT_TRUE(std::is_sorted(x.begin(), x.end(), std::greater<int>()));

}

TEST(Partitions,ForwardIteration)
{
	for (int n = 0; n < 8; ++n)
	{
		partitions X(n);
		set<partitions::partition> S(X.begin(),X.end());
		ASSERT_EQ(X.size(), S.size()); //check if all motzkin paths are different

		for (const auto& x : X)
		{
			check_partition(x,n);
		}
	}
}

TEST(Partitions,WithSpecifiedNumParts)
{
	for (int n = 0; n < 8; ++n)
	{
		for (int k = 1; k <= n; ++k)
		{
			partitions X(n,k);
			set<partitions::partition> S(X.begin(),X.end());
			ASSERT_EQ(X.size(), S.size()); //check if all motzkin paths are different

			for (const auto& x : X)
			{
				check_partition(x,n);
				ASSERT_EQ(x.size(),k);
			}
		}
	}
}
