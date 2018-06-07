#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "combinations_benchmark.hpp"
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
    dscr::Chronometer chrono;

    cout << "|================================ Starting Speed Tests "
            "===============================|"
         << endl;

    // slow, real tests
    const int n = 40;
    const int k = 10;
    const int construct = 1000000;
    const int nperm = 12;

    const int npart = 75;
    const int nsetpart = 13;
    const int ndyck = 18;
    const int nmotzkin = 20;
    // 	const int nmultiset = 19;

    auto C = dscr::combinations(n, k);
    auto CF = dscr::combinations_stack(n, k);

    auto CT = dscr::combination_tree(n, k);
    auto CTF = dscr::combination_tree_stack(n, k);

    auto P = dscr::permutations(nperm);
    auto PF = dscr::permutations_stack(nperm);

    auto DP = dscr::dyck_paths(ndyck);
    auto DPF = dscr::dyck_paths_stack(ndyck);

    auto MP = dscr::motzkin_paths(nmotzkin);
    auto MPF = dscr::motzkin_paths_stack(nmotzkin);

    auto PT = dscr::partitions(npart);
    auto PTF = dscr::partitions_stack(npart);

    auto SPT = dscr::set_partitions(nsetpart);

    auto ms = {4, 2, 3, 1, 0, 1, 5, 0, 5, 4, 0, 1, 1, 5, 2, 0, 2, 1};
    auto MS = dscr::multisets(dscr::multisets::multiset{ms});
    auto MSF = dscr::multisets_stack(dscr::multisets_stack::multiset{ms});

    BenchRow::print_header(cout);
    BenchRow::print_line(cout);
    using namespace std;
    using namespace dscr;
    cout << ProduceRowForwardCopy("Combinations compund", combinations("ABCDEFGHIJKLMNOPQRSTUVWXYZab"s, 14));
    cout << ProduceRowForEach("Combinations", C);
    cout << ProduceRowForEach("Combinations Stack", CF);
    cout << ProduceRowForward("Combinations", C);
    cout << ProduceRowForward("Combinations Stack", CF);
    cout << ProduceRowReverse("Combinations", C);
    cout << ProduceRowReverse("Combinations Stack", CF);
    cout << ProduceRowConstruct("Combinations", C, construct);
    cout << ProduceRowConstruct("Combinations Stack", CF, construct);

    
    BenchRow::print_line(cout);
    cout << ProduceRowForEach("Combinations Tree", CT);
    cout << ProduceRowForEach("Combinations Tree Stack", CTF);
    cout << ProduceRowForward("Combinations Tree", CT);
    cout << ProduceRowForward("Combinations Tree Stack", CTF);
    cout << ProduceRowReverse("Combinations Tree", CT);
    cout << ProduceRowReverse("Combinations Tree Stack", CTF);
#ifdef TEST_GSL_COMBINATIONS
    cout << BenchRow("Combinations Tree GSL",
                     Benchmark([]() { BM_CombinationTreeGSL(n, k); }),
                     binomial<std::int64_t>(n, k));
#endif
    cout << ProduceRowConstruct("Combinations Tree", CT, construct);
    cout << ProduceRowConstruct("Combinations Tree Stack", CTF, construct);

    BenchRow::print_line(cout);
    cout << ProduceRowForward("Permutations", P);
    cout << ProduceRowForward("Permutations Stack", PF);
    cout << ProduceRowReverse("Permutations", P);
    cout << ProduceRowReverse("Permutations Stack", PF);
    cout << ProduceRowConstruct("Permutations", P, construct);
    cout << ProduceRowConstruct("Permutations Stack", PF, construct);

    BenchRow::print_line(cout);
    cout << ProduceRowForward("Multisets", MS);
    cout << ProduceRowForward("Multisets Stack", MSF);
    cout << ProduceRowReverse("Multisets", MS);
    cout << ProduceRowReverse("Multisets Stack", MSF);
    cout << ProduceRowConstruct("Multisets", MS, construct);
    cout << ProduceRowConstruct("Multisets Stack", MSF, construct);

    BenchRow::print_line(cout);
    cout << ProduceRowForward("Dyck Paths", DP);
    cout << ProduceRowForward("Dyck Paths Stack", DPF);

    // 	BenchRow::print_line(cout);
    cout << ProduceRowForward("Motzkin Paths", MP);
    cout << ProduceRowForward("Motzkin Paths Stack", MPF);

    BenchRow::print_line(cout);
    cout << ProduceRowForward("Partitions", PT);
    cout << ProduceRowForward("Partitions Stack", PTF);
    cout << ProduceRowReverse("Partitions", PT);
    cout << ProduceRowReverse("Partitions Stack", PTF);

    BenchRow::print_line(cout);
    cout << ProduceRowForward("Set Partitions", SPT);

    BenchRow::print_line(cout);
    cout << std::defaultfloat;
    cout << "\nTotal Time taken = " << chrono.Reset() << "s" << endl;
    return 0;
}
