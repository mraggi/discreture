#include <gtest/gtest.h>
#include <iostream>
#include "DyckPaths.hpp"
#include <set>

using namespace std;
using namespace dscr;

void check_dyck_path(const dyck_paths::dyck_path& x)
{
	int suma = 0;

	for (auto u : x)
	{
		ASSERT_TRUE(u == 1 || u == -1);
		suma += u;

		ASSERT_GE(suma,0);
	}

	ASSERT_EQ(suma,0);
}

TEST(DyckPaths,ForwardIteration)
{
	for (int n = 0; n < 8; ++n)
	{
		dyck_paths X(n);
		set<dyck_paths::dyck_path> S(X.begin(),X.end());
		ASSERT_EQ(X.size(), S.size()); //check if all dyck paths are different

		for (const auto& x : X)
		{
			check_dyck_path(x);
		}
	}
}
