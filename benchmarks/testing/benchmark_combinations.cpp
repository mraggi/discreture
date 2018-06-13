#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "combinations_benchmark.hpp"
#include "combinations_tree_benchmark.hpp"
#include "discreture.hpp"
#include "multiset_benchmark.hpp"
#include "permutations_benchmark.hpp"

using std::cout;
using std::endl;

using dscr::binomial;
using std::operator""s;

void bench_combs()
{
    constexpr int n = 40;
    constexpr int k = 10;
    constexpr int construct = 1000000;

    auto C = dscr::combinations(n, k);
    auto CF = dscr::combinations_stack(n, k);

    auto CT = dscr::combination_tree(n, k);
    auto CTF = dscr::combination_tree_stack(n, k);

    cout << "|================================ Starting Speed Tests "
            "===============================|"
         << endl;
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
}

void bench_comb_tree() {}

int main()
{

    std::ios_base::sync_with_stdio(false);
    dscr::Chronometer chrono;

    bench_combs();
    //     cout << ProduceRowForward(
    //       "Combinations Compound",
    //       dscr::combinations("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef"s, 10));

    cout << std::defaultfloat;
    cout << "\nTotal Time taken = " << chrono.Reset() << "s\n";

    return 0;
}
