#include <gtest/gtest.h>
#include <iostream>
#include "Sequences.hpp"
#include <set>
#include "Probability.hpp"

using namespace std;
using namespace dscr;

TEST(Sequences,Binomial)
{
	ASSERT_EQ(binomial(20,6),38760);
	ASSERT_EQ(binomial(17,13),2380);
	ASSERT_EQ(binomial(100,105),0);
	ASSERT_EQ(binomial(4,-8),0);
	ASSERT_EQ(binomial(3462346256256,1),3462346256256);
	ASSERT_EQ(binomial(10000,10000),1);
	ASSERT_EQ(binomial(10000,9999),10000);
	ASSERT_EQ(binomial(1000,3),166167000L);
	ASSERT_EQ(binomial(98,8),157366449604L);
	
	for (int i = 0; i < 100; ++i)
	{
		int n = random_int(0,50);
		int k = random_int(0,n+1);
		if (n == 0 && k == 0)
			continue;
		ASSERT_EQ(binomial(n,k),binomial(n-1,k)+binomial(n-1,k-1));
	}
}

TEST(Sequences,Factorial)
{
	ASSERT_EQ(factorial(0),1);
	ASSERT_EQ(factorial(1),1);
	ASSERT_EQ(factorial(2),2);
	ASSERT_EQ(factorial(3),6);
	ASSERT_EQ(factorial(4),24);
	ASSERT_EQ(factorial(5),120);
	ASSERT_EQ(factorial(6),720);
	ASSERT_EQ(factorial(15),1307674368000LL);
}

TEST(Sequences,MotzkinNumbers)
{
	ASSERT_EQ(motzkin(0),1);
	ASSERT_EQ(motzkin(1),1);
	ASSERT_EQ(motzkin(3),4);
	ASSERT_EQ(motzkin(8),323);
	ASSERT_EQ(motzkin(9),835);
	ASSERT_EQ(motzkin(10),2188);
	ASSERT_EQ(motzkin(11),5798);
	ASSERT_EQ(motzkin(17),2356779);
}

TEST(Sequences,PartitionNumbers)
{
	std::vector<long> FromOEIS = {1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101, 135, 176, 231, 297, 385, 490, 627, 792, 1002, 1255, 1575, 1958, 2436, 3010, 3718, 4565, 5604, 6842, 8349, 10143, 12310, 14883, 17977, 21637, 26015, 31185, 37338, 44583, 53174, 63261, 75175, 89134, 105558, 124754, 147273, 173525};
	
	for (int i = 0; i < FromOEIS.size(); ++i)
	{
		ASSERT_EQ(partition_number(i),FromOEIS[i]);
	}
	
}

TEST(Sequences,PartitionNumbersWithSpecifiedParts)
{
	ASSERT_EQ(partition_number(9,5),5);
	ASSERT_EQ(partition_number(10,10),1);
	ASSERT_EQ(partition_number(100,1),1);
	ASSERT_EQ(partition_number(100,2),50);
	ASSERT_EQ(partition_number(95,95),1);
	ASSERT_EQ(partition_number(37,36),1);
	ASSERT_EQ(partition_number(8,4),5);
}

TEST(Sequences,StirlingCycle)
{
	//From Wikipedia
// 	n \ k	0	1	2	3	4	5	6	7	8	9
// 	0	1
// 	1	0	1
// 	2	0	1	1
// 	3	0	2	3	1
// 	4	0	6	11	6	1
// 	5	0	24	50	35	10	1
// 	6	0	120	274	225	85	15	1
// 	7	0	720	1764	1624	735	175	21	1
// 	8	0	5040	13068	13132	6769	1960	322	28	1
// 	9	0	40320	109584	118124	67284	22449	4536	546	36	1
	ASSERT_EQ(stirling_cycle_number(15,15),1);
	ASSERT_EQ(stirling_cycle_number(8,0),0);
	ASSERT_EQ(stirling_cycle_number(9,1),40320);
	ASSERT_EQ(stirling_cycle_number(9,4),67284);
	ASSERT_EQ(stirling_cycle_number(8,3),13132);

}

TEST(Sequences,StirlingPartition)
{
// 	n \ k	0	1	2	3	4	5	6	7	8	9	10
// 	0	1
// 	1	0	1
// 	2	0	1	1
// 	3	0	1	3	1
// 	4	0	1	7	6	1
// 	5	0	1	15	25	10	1
// 	6	0	1	31	90	65	15	1
// 	7	0	1	63	301	350	140	21	1
// 	8	0	1	127	966	1701	1050	266	28	1
// 	9	0	1	255	3025	7770	6951	2646	462	36	1
// 	10	0	1	511	9330	34105	42525	22827	5880	750	45	1

	ASSERT_EQ(stirling_partition_number(0,0),1);
	ASSERT_EQ(stirling_partition_number(15,15),1);
	ASSERT_EQ(stirling_partition_number(6,3),90);
	ASSERT_EQ(stirling_partition_number(8,4),1701);
	ASSERT_EQ(stirling_partition_number(10,5),42525);
}
