#include "discreture.hpp"
#include "Tests.hpp"

using namespace std;

/**
 * @brief Discreture is a library designed to make it easy to iterate efficiently over common combinatorial objects such as combinations, permutations, subsets, multisets, partitions, dyck paths, motzkin paths
 **/
int main(int argc, char **argv) 
{	
	using namespace dscr;
// 	using combination = combinations::combination; 
// 
// 	// 8,233,430,727,600 combinaciones
// 	combinations X(46,23); 
// 
// 	auto it = std::partition_point(X.begin(), X.end(), 
// 		[](const combination& x){
// 		if (x.back() < 36)
// 			return true;
// 		return false;
// 	});
// 	cout << *it << endl;
// 	return 0;
	
	Chronometer();
	testManualCombinations();
	
// 	lluint i = 0;
// 	combinations X(33,16);
// 	for (auto& x : X)
// 	{
// 		if (x.back() == 25)
// 			++i;
// 	}
// 	cout << "ttnum= " << i << endl;
// 	cout << "\n================ Starting Correctness Tests ================" << endl;
// 	testCorrectness();
// 	cout << "\n================ Starting Speed Tests ================" << endl;
// 	testSpeed();
	
	cout << "Total Time taken = " << dscr::TimeFromStart() << "s" << endl;
	return 0;
	
}



