#include "Partitions.hpp"
#include "SetPartitions.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "external_benches.hpp"

using std::cout;
using std::endl;

void bench_partitions()
{
    constexpr int npart = 75;
    auto PT = dscr::partitions(npart);
    auto PTF = dscr::partitions_stack(npart);

    cout << ProduceRowForward("Partitions", PT);
    cout << ProduceRowForward("Partitions Stack", PTF);
    cout << ProduceRowReverse("Partitions", PT);
    cout << ProduceRowReverse("Partitions Stack", PTF);
}

void bench_set_partitions()
{
    const int nsetpart = 13;
    auto SPT = dscr::set_partitions(nsetpart);
    cout << ProduceRowForward("Set Partitions", SPT);
}
