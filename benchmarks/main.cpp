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

    dscr::combinations C(n, k);
    dscr::basic_combinations<int, boost::container::static_vector<int, k>> CF(
      n, k);
    dscr::combinations_tree CT(n, k);
    dscr::basic_combinations_tree<int, boost::container::static_vector<int, k>>
      CTF(n, k);

    dscr::permutations P(nperm);
    dscr::basic_permutations<int, boost::container::static_vector<int, nperm>>
      PF(nperm);

    dscr::dyck_paths DP(ndyck);
    dscr::basic_dyck_paths<int, boost::container::static_vector<int, 2*ndyck>>
      DPF(ndyck);
    dscr::motzkin_paths MP(nmotzkin);
    dscr::basic_motzkin_paths<int,
                              boost::container::static_vector<int, nmotzkin>>
      MPF(nmotzkin);

    dscr::partitions PT(npart);
    dscr::basic_partitions<int, boost::container::static_vector<int, npart + 1>>
      PTF(npart);
    dscr::set_partitions SPT(nsetpart);

    auto ms = {4, 2, 3, 1, 0, 1, 5, 0, 5, 4, 0, 1, 1, 5, 2, 0, 2, 1};
    dscr::multisets MS(dscr::multisets::multiset{ms});
    dscr::multisets_fast MSF(dscr::multisets_fast::multiset{ms});

    BenchRow::print_header(cout);
    BenchRow::print_line(cout);
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
                     Benchmark([]() { BM_CombinationsTreeGSL(n, k); }),
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
