#include "discreture.hpp"
#include "Tests.hpp"

using namespace std;
using namespace dscr;

/**
 * @brief Discreture is a library designed to make it easy to iterate efficiently over common combinatorial objects such as combinations, permutations, subsets, multisets, partitions, dyck paths, motzkin paths, set partitions
 **/
int main() 
{

	dscr::Chronometer C;
	cout << "\n================ Starting Correctness Tests ================" << endl;
	testCorrectness();
	cout << "\n================ Starting Speed Tests ================" << endl;
	testSpeed();
	
	cout << "Total Time taken = " << C.Reset() << "s" << endl;
	return 0;
	
}



