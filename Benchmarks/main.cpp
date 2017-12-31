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

	using dscr::binomial;
	std::ios_base::sync_with_stdio(false);
	dscr::Chronometer C;

	cout << "|============================== Starting Speed Tests =============================|" << endl;
	
	//slow, real tests
	const int n = 40;
	const int k = 10;
	const auto combs_size = binomial<long long>(n,k);
	const int construct = 100000;
	
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
	cout << ProduceRowForEach("Combinations", dscr::combinations(n,k));
	cout << ProduceRowForEach("Combinations Stack", dscr::combinations_fast(n,k));
	cout << BenchRow("Combinations (No iterator)", Benchmark([](){BM_CombinationsNAP(n,k);}), combs_size);
	cout << ProduceRowForward("Combinations", dscr::combinations(n,k));	
	cout << ProduceRowForward("Combinations Stack", dscr::combinations_fast(n,k));	
	cout << ProduceRowReverse("Combinations", dscr::combinations(n,k));
	cout << BenchRow("Combinations Construct", Benchmark([](){BM_CombinationsConstruct(n,k,construct);}), construct);
	
	BenchRow::print_line(cout);
	cout << ProduceRowForEach("Combinations Tree", dscr::combinations_tree(n,k));
	cout << ProduceRowForEach("Combinations Tree Stack", dscr::combinations_tree_fast(n,k));
	cout << BenchRow("Combinations Tree (No iterator)", Benchmark([](){BM_CombinationsTreeNAP(n,k);}), combs_size);
	cout << ProduceRowForward("Combinations Tree", dscr::combinations_tree(n,k));
	cout << ProduceRowForward("Combinations Tree Stack", dscr::combinations_tree_fast(n,k));
	cout << ProduceRowReverse("Combinations Tree", dscr::combinations_tree(n,k));
#ifdef TEST_GSL_COMBINATIONS
	cout << BenchRow("Combinations Tree GSL", Benchmark([](){BM_CombinationsTreeGSL(n,k);}), combs_size);
#endif
	cout << BenchRow("Combinations Tree Construct", Benchmark([](){BM_CombinationsTreeConstruct(n,k,construct);}), construct);
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Permutations", dscr::permutations_fast(nperm));
	cout << ProduceRowReverse("Permutations", dscr::permutations_fast(nperm));
	cout << BenchRow("Permutations Construct", Benchmark([](){BM_PermutationsConstruct(nperm,construct);}), construct);
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Multisets", dscr::multisets_fast({4,2,3,1,0,1,5,0,5,4,0,1,1,5,2,0,2}));
	
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Dyck Paths", dscr::dyck_paths_fast(ndyck));
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Motzkin Paths", dscr::motzkin_paths_fast(nmotzkin));
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Partitions", dscr::partitions_fast(npart));
	
	BenchRow::print_line(cout);
	cout << ProduceRowForward("Set Partitions", dscr::set_partitions(nsetpart));

	BenchRow::print_line(cout);
	
	cout << "\nTotal Time taken = " << C.Reset() << "s" << endl;
	return 0;

}



