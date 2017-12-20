#include "combinations_benchmark.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "combinations_tree_benchmark.hpp"
#include "discreture.hpp"
#include "multiset_benchmark.hpp"
#include "permutations_benchmark.hpp"



int main()
{
	using std::cout;
	using std::endl;
	using dscr::combinations;
	using dscr::combinations_tree;
	using dscr::partitions;
	using dscr::set_partitions;
	using dscr::permutations;
	using dscr::motzkin_paths;
	using dscr::dyck_paths;
	using dscr::binomial;
	std::ios_base::sync_with_stdio(false);
	dscr::Chronometer C;

	cout << "|============================== Starting Speed Tests =============================|" << endl;
	
	//slow, real tests
	const int n = 34;
	const int k = 17;
	const int combconstruct = 10000;
	
	const int nperm = 12;
	
	const int npart = 50;
	const int nsetpart = 12;
	const int ndyck = 18;
	const int nmotzkin = 20;
	
	//fast tests
// 	const int n = 25;
// 	const int k = 12;
// 	const int combconstruct = 1000;
// 	
// 	const int nperm = 9;
// 	
// 	const int npart = 20;
// 	const int nsetpart = 7;
// 	const int ndyck = 10;
// 	const int nmotzkin = 10;

	BenchRow::print_header(cout);
	BenchRow::print_line(cout);
	cout << ProduceRowForEach("Combinations", combinations(n,k));
	cout << BenchRow("Combinations (No iterator)", Benchmark([](){BM_CombinationsNAP(n,k);}), binomial(n,k));
	cout << ProduceRowForward("Combinations", combinations(n,k));
	cout << ProduceRowReverse("Combinations", combinations(n,k));
	cout << BenchRow("Combinations Construct", Benchmark([](){BM_CombinationsConstruct(n,k,combconstruct);}), combconstruct);
	
	BenchRow::print_line(cout);
	cout << ProduceRowForEach("Combinations Tree", combinations_tree(n,k));
	cout << BenchRow("Combinations Tree (No iterator)", Benchmark([](){BM_CombinationsTreeNAP(n,k);}), binomial(n,k));
	cout << ProduceRowForward("Combinations Tree", combinations_tree(n,k));
	cout << ProduceRowReverse("Combinations Tree", combinations_tree(n,k));
#ifdef TEST_GSL_COMBINATIONS
	cout << BenchRow("Combinations Tree GSL", Benchmark([](){BM_CombinationsTreeGSL(n,k);}), binomial(n,k));
#endif
	cout << BenchRow("Combinations Tree Construct", Benchmark([](){BM_CombinationsTreeConstruct(n,k,combconstruct);}), combconstruct);
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Permutations", permutations(nperm));
	cout << ProduceRowReverse("Permutations", permutations(nperm));
	cout << BenchRow("Permutations Construct", Benchmark([](){BM_PermutationsConstruct(nperm,combconstruct);}), combconstruct);
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Dyck Paths", dyck_paths(ndyck));
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Motzkin Paths", motzkin_paths(nmotzkin));
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Partitions", partitions(npart));
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Set Partitions", set_partitions(nsetpart));

	BenchRow::print_line(cout);
	
	cout << "\nTotal Time taken = " << C.Reset() << "s" << endl;
	return 0;

}



