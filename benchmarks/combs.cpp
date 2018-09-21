// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Combinations.hpp"
#include "LexCombinations.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "external_benches.hpp"

using std::cout;

constexpr int n = 40;
constexpr int k = 10;
constexpr int construct = 1000000;

void bench_combinations()
{
    auto C = discreture::combinations(n, k);
    auto CF = discreture::combinations_stack(n, k);

    cout << ProduceRowForEach("Combinations", C);
    cout << ProduceRowForEach("Combinations Stack", CF);
    cout << ProduceRowForward("Combinations", C);
    cout << ProduceRowForward("Combinations Stack", CF);
    cout << ProduceRowReverse("Combinations", C);
    cout << ProduceRowReverse("Combinations Stack", CF);
    cout << ProduceRowConstruct("Combinations", C, construct);
    cout << ProduceRowConstruct("Combinations Stack", CF, construct);
}

void bench_lex_combs()
{
    auto CT = discreture::lex_combinations(n, k);
    auto CTF = discreture::lex_combinations_stack(n, k);

    cout << ProduceRowForEach("Lex Combinations", CT);
    cout << ProduceRowForEach("Lex Combinations Stack", CTF);
    cout << ProduceRowForward("Lex Combinations", CT);
    cout << ProduceRowForward("Lex Combinations Stack", CTF);
    cout << ProduceRowReverse("Lex Combinations", CT);
    cout << ProduceRowReverse("Lex Combinations Stack", CTF);
#ifdef TEST_GSL_COMBINATIONS
    cout << BenchRow("Lex Combinations GSL",
                     Benchmark([]() { BM_LexCombinationsGSL(n, k); }),
                     discreture::binomial<std::int64_t>(n, k));
#endif
    cout << ProduceRowConstruct("Lex Combinations", CT, construct);
    cout << ProduceRowConstruct("Lex Combinations Stack", CTF, construct);
}
