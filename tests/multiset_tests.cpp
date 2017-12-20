#include <gtest/gtest.h>
#include <iostream>
#include "Multisets.hpp"
#include <set>
#include "Probability.hpp"

using namespace std;
using namespace dscr;

void check_multiset(const multisets::multiset& x, const multisets::multiset& total)
{
	ASSERT_EQ(x.size(), total.size());
	for (size_t i = 0; i < x.size(); ++i)
	{
		ASSERT_LE(x[i],total[i]);
	}
}

std::vector<int> get_random_multiset(int n)
{
	std::vector<int> result(n);
	
	
	std::generate(result.begin(), result.end(), []()
	{
		return random::random_int(0,3);
	});
	
	
	return result;
}

TEST(Multisets,ForwardIteration)
{
	for (int n = 0; n < 12; ++n)
	{
		std::vector<int> total = get_random_multiset(n);
		multisets X(total);
		set<multisets::multiset> S(X.begin(),X.end());
		ASSERT_EQ(X.size(), S.size()); //check if all dyck paths are different

		for (const auto& x : X)
		{
			check_multiset(x, total);
		}
	}
}
