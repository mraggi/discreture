#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "discreture.hpp"
#include "external_benches.hpp"

using std::cout;

void bench_dyck()
{
    const int ndyck = 18;
    auto DP = dscr::dyck_paths(ndyck);
    auto DPF = dscr::dyck_paths_stack(ndyck);

    cout << ProduceRowForward("Dyck Paths", DP);
    cout << ProduceRowForward("Dyck Paths Stack", DPF);
}

void bench_motzkin()
{
    const int nmotzkin = 20;
    auto MP = dscr::motzkin_paths(nmotzkin);
    auto MPF = dscr::motzkin_paths_stack(nmotzkin);

    cout << ProduceRowForward("Motzkin Paths", MP);
    cout << ProduceRowForward("Motzkin Paths Stack", MPF);
}
