#include "Discreture/Partitions.hpp"
#include "Discreture/SetPartitions.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "external_benches.hpp"

using std::cout;

void bench_partitions()
{
    constexpr int npart = 70;
    auto PT = discreture::partitions(npart);
    auto PTF = discreture::partitions_stack(npart);

    cout << ProduceRowForEach("Partitions", PT);
    cout << ProduceRowForEach("Partitions Stack", PTF);
    cout << ProduceRowForward("Partitions", PT);
    cout << ProduceRowForward("Partitions Stack", PTF);
    cout << ProduceRowReverse("Partitions", PT);
    cout << ProduceRowReverse("Partitions Stack", PTF);
}

void bench_set_partitions()
{
    const int nsetpart = 13;
    auto SPT = discreture::set_partitions(nsetpart);
    cout << ProduceRowForward("Set Partitions", SPT);
}
