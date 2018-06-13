#include "CombinationTree.hpp"
#include "Combinations.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "external_benches.hpp"

using std::cout;
using std::endl;

using dscr::binomial;
using std::operator""s;

void bench_combinations()
{
    constexpr int n = 40;
    constexpr int k = 10;
    constexpr int construct = 1000000;

    auto CF = dscr::combinations_stack(n, k);
    auto C = dscr::combinations(n, k);

    cout << ProduceRowForEach("Combinations", C);
    cout << ProduceRowForEach("Combinations Stack", CF);
    cout << ProduceRowForward("Combinations", C);
    cout << ProduceRowForward("Combinations Stack", CF);
    cout << ProduceRowReverse("Combinations", C);
    cout << ProduceRowReverse("Combinations Stack", CF);
    cout << ProduceRowConstruct("Combinations", C, construct);
    cout << ProduceRowConstruct("Combinations Stack", CF, construct);
}

void bench_comb_tree()
{
    constexpr int n = 40;
    constexpr int k = 10;
    constexpr int construct = 1000000;

    auto CT = dscr::combination_tree(n, k);
    auto CTF = dscr::combination_tree_stack(n, k);

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
}
