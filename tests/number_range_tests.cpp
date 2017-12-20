#include <gtest/gtest.h>
#include <iostream>
#include "NumberRange.hpp"

using namespace std;
using namespace dscr;

TEST(NumberRange,ForwardIteration)
{
	for (int n = 0; n < 10; ++n)
	{
		for (int m = n; m < 15; ++m)
		{
			number_range R(n,m);
			set<number_range::value_type> S(R.begin(), R.end());
			ASSERT_EQ(R.size(), S.size()); //This checks everything is different.
			ASSERT_EQ(R.size(), m-n);
			ASSERT_TRUE(std::is_sorted(R.begin(), R.end()));
			ASSERT_EQ(*R.begin(),n);
			ASSERT_EQ(*(R.end()-1),m-1);
		}
	}
}


TEST(NumberRange,RandomAccess)
{
	basic_number_range<long> A(5,16,2);
	ASSERT_EQ(A[0], 5);
	ASSERT_EQ(A[1], 7);
	ASSERT_EQ(A[2], 9);
	ASSERT_EQ(A[3], 11);
	ASSERT_EQ(A[4], 13);
	ASSERT_EQ(A[5], 15);
	ASSERT_EQ(A.size(),6);
}

TEST(NumberRange,NegativeStepTest)
{
	basic_number_range<long> A(16,9,-2);
	auto it = A.begin();
	ASSERT_EQ(*it,16);
	++it;
	ASSERT_EQ(*it,14);
	++it;
	ASSERT_EQ(*it,12);
	++it;
	ASSERT_EQ(*it,10);
	
	ASSERT_EQ(*A.end(),8);
	
}


TEST(NumberRange,PositiveStepTest)
{
	basic_number_range<long> A(5,14,3);
	ASSERT_EQ(A.size(),3);
	auto it = A.begin();
	ASSERT_EQ(*it,5);
	++it;
	ASSERT_EQ(*it,8);
	++it;
	ASSERT_EQ(*it,11);
	
	
	ASSERT_EQ(*A.end(),14);
	
}

