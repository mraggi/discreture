#include "Multisets.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "external_benches.hpp"

using std::cout;

void bench_multisets()
{
    constexpr int construct = 1000000;
    auto ms = {4, 2, 3, 1, 0, 1, 5, 0, 5, 4, 0, 1, 1, 5, 2, 0, 2, 1};
    auto MS = discreture::multisets(discreture::multisets::multiset{ms});
    auto MSF =
      discreture::multisets_stack(discreture::multisets_stack::multiset{ms});

    cout << ProduceRowForEach("Multisets", MS);
    cout << ProduceRowForEach("Multisets Stack", MSF);
    cout << ProduceRowForward("Multisets", MS);
    cout << ProduceRowForward("Multisets Stack", MSF);
    cout << ProduceRowReverse("Multisets", MS);
    cout << ProduceRowReverse("Multisets Stack", MSF);
    cout << ProduceRowConstruct("Multisets", MS, construct);
    cout << ProduceRowConstruct("Multisets Stack", MSF, construct);
}
