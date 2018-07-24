#include "Permutations.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "external_benches.hpp"

using std::cout;

void bench_permutations()
{
    constexpr int nperm = 12;
    constexpr int construct = 1000000;

    auto P = discreture::permutations(nperm);
    auto PF = discreture::permutations_stack(nperm);

    cout << ProduceRowForward("Permutations", P);
    cout << ProduceRowForward("Permutations Stack", PF);
    cout << ProduceRowReverse("Permutations", P);
    cout << ProduceRowReverse("Permutations Stack", PF);
    cout << ProduceRowConstruct("Permutations", P, construct);
    cout << ProduceRowConstruct("Permutations Stack", PF, construct);
}
