#include "test_all.hpp"
#include "TimeHelpers.hpp"

using namespace std;
using namespace dscr;

bool testCorrectness()
{
	if (
		testCombinations() 	&&
		testCombinationsTree() &&
		testPermutations() 	&&
		testNumberTheory()	&&
		testPartitions()	&&
		testMultiset()		&&
		testDyckPaths()		&&
		testSetPartitions()		&&
		testMotzkin()
	)
	{
		std::cout << "\n\n All tests PASSED!" << '\n';
		return true;
	}

	std::cout << "SOME TESTS FAILED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << '\n';
	return false;
}




void testSpeed()
{
	testCombinationsSpeed(32, 16);
	cout << flush;
	testCombinationsTreeSpeed(32, 16);
	cout << flush;
	testPermutationsSpeed(11);
	cout << flush;
	testPartitionsSpeed(45);
	cout << flush;
	testMultisetSpeed();
	cout << flush;
	testDyckPathsSpeed(18);
	cout << flush;
	testMotzkinSpeed(20);
	cout << flush;
	testSetPartitionSpeed(13);
	cout << flush;
	testNumberTheorySpeed(1000);
	cout << flush;
	testPrimeSpeed();
	cout << flush;
}

/**
 * @brief Discreture is a library designed to make it easy to iterate efficiently over common combinatorial objects such as combinations, permutations, subsets, multisets, partitions, dyck paths, motzkin paths, set partitions
 **/
int main()
{
	
// 	for (int n = 0; n < 20; ++n)
// 	{
// 		for (int k = 0; k <= n; ++k)
// 		{
// 			std::cout << stirling_partition_number(n,k) << ' ';
// 		}
// 		std::cout << std::endl;
// 	}
// 	std::cout << endl;
// 	
// 	
// 	
// 	
// 	return 0;
	
	Chronometer C;

	cout << "\n================ Starting Correctness Tests ================" << endl;

	if (!testCorrectness())
	{
		return 1; //error!!
	}

// 	cout << "\n================ Starting Speed Tests ================" << endl;
// 	testSpeed();

	cout << "Total Time taken = " << C.Reset() << "s" << endl;
	return 0;

}



