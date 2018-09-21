// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Partitions.hpp"
#include "SetPartitions.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "external_benches.hpp"

using std::cout;

void bench_partitions()
{
    constexpr int npart = 75;
    auto PT = discreture::partitions(npart);
    auto PTF = discreture::partitions_stack(npart);

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
