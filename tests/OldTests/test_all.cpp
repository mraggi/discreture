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
		testPartitions()	&&
		testMultiset()		&&
		testDyckPaths()		&&
		testSetPartitions()	&&
		testMotzkin()
	)
	{
		std::cout << "\n\n All tests PASSED!" << std::endl;
		return true;
	}

	std::cout << "SOME TESTS FAILED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	return false;
}





/**
 * @brief Discreture is a library designed to make it easy to iterate efficiently over common combinatorial objects such as combinations, permutations, subsets, multisets, partitions, dyck paths, motzkin paths, set partitions
 **/
int main()
{
	Chronometer C;

	cout << "\n================ Starting Correctness Tests ================" << endl;

	if (!testCorrectness()) //TODO(mraggi): switch to google test, probably.
	{
		return 1; //error!!
	}

	cout << "Total Time taken = " << C.Reset() << "s" << endl;
	return 0;

}



