#include "combinations_benchmark.hpp"
#include "combinations_tree_benchmark.hpp"
#include "permutations_benchmark.hpp"
#include "multiset_benchmark.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "discreture.hpp"



int main()
{
	using namespace std;
	using namespace dscr;
	std::ios_base::sync_with_stdio(false);
	Chronometer C;

	cout << "|============================== Starting Speed Tests =============================|" << endl;
	
	const int n = 25;
	const int k = 15;
	const int combconstruct = 1000;
	
	const int nperm = 10;
	
	const int npart = 50;
	const int nsetpart = 10;
	const int ndyck = 14;
	const int nmotzkin = 14;

	TableRow::print_header(cout);
	TableRow::print_line(cout);
	cout << ProduceRowForward("Combinations", combinations(n,k));
	cout << ProduceRowReverse("Combinations", combinations(n,k));
	cout << ProduceRowForEach("Combinations", combinations(n,k));
	cout << TableRow("Combinations Euler314", Benchmark([](){BM_CombinationsEuler314(n,k);}), binomial(n,k));
	cout << TableRow("Combinations Construct", Benchmark([](){BM_CombinationsConstruct(n,k,combconstruct);}), combconstruct);
	
	TableRow::print_line(cout);
	cout << ProduceRowForward("Combinations Tree", combinations_tree(n,k));
	cout << ProduceRowReverse("Combinations Tree", combinations_tree(n,k));
	cout << ProduceRowForEach("Combinations Tree", combinations_tree(n,k));
	cout << TableRow("Combinations Tree Euler314", Benchmark([](){BM_CombinationsTreeEuler314(n,k);}), binomial(n,k));
#ifdef TEST_GSL_COMBINATIONS
	cout << TableRow("Combinations Tree GSL", Benchmark([](){BM_CombinationsTreeGSL(n,k);}), binomial(n,k));
#endif
	cout << TableRow("Combinations Tree Construct", Benchmark([](){BM_CombinationsTreeConstruct(n,k,combconstruct);}), combconstruct);
	
	TableRow::print_line(cout);
	cout << ProduceRowForward("Permutations", permutations(nperm));
	cout << ProduceRowReverse("Permutations", permutations(nperm));
	cout << TableRow("Permutations Construct", Benchmark([](){BM_PermutationsConstruct(nperm,combconstruct);}), combconstruct);
	
	TableRow::print_line(cout);
	cout << ProduceRowForward("Dyck Paths", dyck_paths(ndyck));
	
	TableRow::print_line(cout);
	cout << ProduceRowForward("Motzkin Paths", motzkin_paths(nmotzkin));
	
	TableRow::print_line(cout);
	cout << ProduceRowForward("Partitions", partitions(npart));
	
	TableRow::print_line(cout);
	cout << ProduceRowForward("Set Partitions", set_partitions(nsetpart));

	TableRow::print_line(cout);
	
	return 0;
	
	
	
// 	Benchmark("Combinations For Each", []()
// 	{
// 		BM_CombinationsForEach(n,k);
// 	});
// 	
// 	Benchmark("Combinations Find All", []()
// 	{
// 		BM_CombinationsFindAll(n,k);
// 	});
// 	
// 	Benchmark("Combinations Euler314", []()
// 	{
// 		BM_CombinationsEuler314(n,k);
// 	});
// 	
// 	
// 	cout << rang::fg::cyan << "\n    ****Combinations Tree****" << rang::fg::reset << endl;
// 	Benchmark("Combinations Tree Forward", []()
// 	{
// 		BM_CombinationsTreeFWD(n,k);
// 	});
// 	
// 	Benchmark("Combinations Tree Reverse", []()
// 	{
// 		BM_CombinationsTreeReverse(n,k);
// 	});
// 	
// 	Benchmark("Combinations Tree For Each", []()
// 	{
// 		BM_CombinationsTreeForEach(n,k);
// 	});
// 	
// 	Benchmark("Combinations Tree Find All", []()
// 	{
// 		BM_CombinationsTreeFindAll(n,k);
// 	});
// 	
// 	Benchmark("Combinations Tree Euler314", []()
// 	{
// 		BM_CombinationsTreeEuler314(n,k);
// 	});
// 	
// 	Benchmark("Combinations Tree GSL", []()
// 	{
// 		BM_CombinationsTreeEuler314(n,k);
// 	});
// 	
// 	
// 	cout << rang::fg::cyan << "\n    ****Permutations****" << rang::fg::reset << endl;
// 	Benchmark("Permutations Forward", []()
// 	{
// 		BM_PermutationsFWD(nperm);
// 	});
// 	
// 	Benchmark("Permutations Reverse", []()
// 	{
// 		BM_PermutationsReverse(nperm);
// 	});
// 	
// 	cout << rang::fg::cyan << "\n    ****Partitions****" << rang::fg::reset << endl;
// 	Benchmark("Partitions Forward", []()
// 	{
// 		BM_PartitionsFWD(50);
// 	});
// 	
// 	cout << rang::fg::cyan << "\n    ****Set Partitions****" << rang::fg::reset << endl;
// 	Benchmark("Set Partitions Forward", []()
// 	{
// 		BM_SetPartitionsFWD(nsetpart);
// 	});
// 	
// 	cout << rang::fg::cyan << "\n    ****Dyck Paths****" << rang::fg::reset << endl;
// 	Benchmark("Dyck Paths Forward", []()
// 	{
// 		BM_DyckPathsFWD(ndyck);
// 	});
// 	
// 	cout << rang::fg::cyan << "\n    ****Motzkin Paths****" << rang::fg::reset << endl;
// 	Benchmark("Motzkin Paths Forward", []()
// 	{
// 		BM_MotzkinFWD(nmotzkin);
// 	});
// 	
// 	
// 	cout << rang::fg::cyan << "\n    ****Multisets****" << rang::fg::reset << endl;
// 	Benchmark("Multisets Forward", []()
// 	{
// 		BM_MultisetFWD();
// 	},2);
	
	cout << "\nTotal Time taken = " << C.Reset() << "s" << endl;
	return 0;

}



