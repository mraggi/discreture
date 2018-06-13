#include "../benchmarker.hpp"
#include "../benchtable.hpp"
#include "discreture.hpp"

using std::cout;
using std::endl;

constexpr int n = 45;
constexpr int k = 10;

void parallel_combinations(int num_processors)
{
    auto C = dscr::combinations(n, k);
    auto CF = dscr::combinations_stack(n, k);
    cout << ProduceRowParallelForward("Combs", C, num_processors);
    cout << ProduceRowParallelForward("Combs Stack", CF, num_processors);
}

void parallel_lex_combinations(int num_processors)
{
    auto C = dscr::lex_combinations(n, k);
    auto CF = dscr::lex_combinations_stack(n, k);
    cout << ProduceRowParallelForward("Combs Tree", C, num_processors);
    cout << ProduceRowParallelForward("Combs Tree Stack", CF, num_processors);
}

// void parallel_permutations(int num_processors)
// {
//     auto P = dscr::permutations(14);
//     cout << ProduceRowParallelForward("Permutations", P, num_processors);
// }

int main()
{
    int num_processors = 8;
    using std::cout;
    using std::endl;

    std::ios_base::sync_with_stdio(false);
    dscr::Chronometer chrono;

    cout << "|================================ Starting Speed Tests "
            "===============================|"
         << endl;

    BenchRow::print_header(cout);

    BenchRow::print_line(cout);

    parallel_combinations(num_processors);

    BenchRow::print_line(cout);

    parallel_lex_combinations(num_processors);

    BenchRow::print_line(cout);

    //     parallel_permutations(num_processors);

    cout << std::defaultfloat;
    cout << "\nTotal Time taken = " << chrono.Peek() << "s" << endl;

    return 0;
}
