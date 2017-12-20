#include <gtest/gtest.h>
#include <iostream>
#include "NaturalNumber.hpp"

using namespace std;
using namespace dscr;

TEST(NaturalNumber,ForwardIteration)
{
	for (int n = 0; n < 10; ++n)
	{
		natural_number R(n);
		set<natural_number::value_type> S(R.begin(), R.end());
		ASSERT_EQ(R.size(), S.size()); //This checks everything is different.
		ASSERT_EQ(R.size(), n);
		ASSERT_TRUE(std::is_sorted(R.begin(), R.end()));
		ASSERT_EQ(*R.begin(),0);
		ASSERT_EQ(*(R.end()-1),n-1);
	}
}


