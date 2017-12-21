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
	using dscr::combinations_fast;
	using dscr::combinations_tree_fast;
	using dscr::partitions_fast;
	using dscr::set_partitions;
	using dscr::permutations_fast;
	using dscr::motzkin_paths_fast;
	using dscr::dyck_paths_fast;
	using dscr::multisets_fast;
	using dscr::binomial;
	std::ios_base::sync_with_stdio(false);
	dscr::Chronometer C;

	cout << "|============================== Starting Speed Tests =============================|" << endl;
	
	//slow, real tests
	const int n = 34;
	const int k = 17;
	const int construct = 10000;
	
	const int nperm = 12;
	
	const int npart = 60;
	const int nsetpart = 13;
	const int ndyck = 18;
	const int nmotzkin = 20;
	const int nmultiset = 19;
	
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
	cout << ProduceRowForEach("Combinations", combinations_fast(n,k));
	cout << BenchRow("Combinations (No iterator)", Benchmark([](){BM_CombinationsNAP(n,k);}), binomial(n,k));
	cout << ProduceRowForward("Combinations", combinations_fast(n,k));
	cout << ProduceRowReverse("Combinations", combinations_fast(n,k));
	cout << BenchRow("Combinations Construct", Benchmark([](){BM_CombinationsConstruct(n,k,construct);}), construct);
	
	BenchRow::print_line(cout);
	cout << ProduceRowForEach("Combinations Tree", combinations_tree_fast(n,k));
	cout << BenchRow("Combinations Tree (No iterator)", Benchmark([](){BM_CombinationsTreeNAP(n,k);}), binomial(n,k));
	cout << ProduceRowForward("Combinations Tree", combinations_tree_fast(n,k));
	cout << ProduceRowReverse("Combinations Tree", combinations_tree_fast(n,k));
#ifdef TEST_GSL_COMBINATIONS
	cout << BenchRow("Combinations Tree GSL", Benchmark([](){BM_CombinationsTreeGSL(n,k);}), binomial(n,k));
#endif
	cout << BenchRow("Combinations Tree Construct", Benchmark([](){BM_CombinationsTreeConstruct(n,k,construct);}), construct);
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Permutations", permutations_fast(nperm));
	cout << ProduceRowReverse("Permutations", permutations_fast(nperm));
	cout << BenchRow("Permutations Construct", Benchmark([](){BM_PermutationsConstruct(nperm,construct);}), construct);
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Multisets", multisets_fast({4,2,3,1,0,1,5,0,5,4,0,1,1,5,2,0,2}));
	
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Dyck Paths", dyck_paths_fast(ndyck));
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Motzkin Paths", motzkin_paths_fast(nmotzkin));
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Partitions", partitions_fast(npart));
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Set Partitions", set_partitions(nsetpart));

	BenchRow::print_line(cout);
	
	cout << "\nTotal Time taken = " << C.Reset() << "s" << endl;
	return 0;

}



