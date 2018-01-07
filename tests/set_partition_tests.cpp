#include <gtest/gtest.h>
#include <iostream>
#include "SetPartitions.hpp"
#include <set>

using namespace std;
using namespace dscr;

void check_set_partition(const set_partitions::set_partition& x)
{
	vector<int> all;
	for (auto& u : x)
	{
		all.insert(all.end(),u.begin(), u.end());
	}
	std::sort(all.begin(),all.end());
	
	const int n = all.size();
	for (int i = 0; i < n; ++i)
	{
		ASSERT_EQ(i,all[i]);
	}
	
}

TEST(SetPartitions,ForwardIteration)
{
	for (int n = 0; n < 8; ++n)
	{
		set_partitions X(n);
		set<set_partitions::set_partition> S(X.begin(),X.end());
		ASSERT_EQ(X.size(), S.size()); //check if all dyck paths are different

		for (const auto& x : X)
		{
			check_set_partition(x);
		}
	}
}


TEST(SetPartitions,WithSpecifiedNumParts)
{
	for (int n = 0; n < 8; ++n)
	{
		for (int k = 1; k <= n; ++k)
		{
			set_partitions X(n,k);
			set<set_partitions::set_partition> S(X.begin(),X.end());
			ASSERT_EQ(X.size(), S.size()); //check if all motzkin paths are different

			for (const auto& x : X)
			{
				check_set_partition(x);
				ASSERT_EQ(x.size(),k);
			}
		}
	}
}
