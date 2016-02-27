#include "discreture.hpp"
#include "Tests.hpp"

using namespace std;

/**
 * @brief Discreture is a library designed to make it easy to iterate efficiently over common combinatorial objects such as combinations, permutations, subsets, multisets, partitions, dyck paths, motzkin paths
 **/
int main(int argc, char **argv) 
{	
	using namespace dscr;
	
	
	cout << "\n================ Starting Correctness Tests ================" << endl;
	testCorrectness();
	cout << "\n================ Starting Speed Tests ================" << endl;
	testSpeed();
	
	cout << "Total Time taken = " << dscr::TimeFromStart() << "s" << endl;
	return 0;
	
}











