#include "../benchmarker.hpp"
#include "../benchtable.hpp"
#include "discreture.hpp"

using std::cout;
using std::endl;

constexpr int n = 45;
constexpr int k = 10;

void parallel_combinations(int num_processors)
{
    auto C = discreture::combinations(n, k);
    cout << ProduceRowParallelForward("Combs", C, num_processors);
}

void parallel_lex_combinations(int num_processors)
{
    auto C = discreture::lex_combinations(n, k);
    cout << ProduceRowParallelForward("Lex Combs", C, num_processors);
}

void parallel_permutations(int num_processors)
{
    auto C = discreture::permutations(12);
    cout << ProduceRowParallelForward("Perms", C, num_processors);
}

void parallel_multisets(int num_processors)
{
    auto C = discreture::multisets(31, 1);
    cout << ProduceRowParallelForward("Multisets", C, num_processors);
}

// void parallel_permutations(int num_processors)
// {
//     auto P = discreture::permutations(14);
//     cout << ProduceRowParallelForward("Permutations", P, num_processors);
// }

int main(int argc, char *argv[])
{
    int num_processors = std::thread::hardware_concurrency();
    if (argc > 1)
    {
        try
        {
            std::string np = argv[1];
            num_processors = std::stoi(np);
        } catch(...)
        {
            std::cerr << "Incorrect format for number of processors." << std::endl;
            return 1;
        }
    }
    using std::cout;
    using std::endl;

    std::ios_base::sync_with_stdio(false);
    discreture::Chronometer chrono;

    cout << "|================================ Starting Speed Tests "
            "===============================|"
         << endl;

    BenchRow::print_header(cout);

    BenchRow::print_line(cout);

    parallel_combinations(num_processors);

    parallel_lex_combinations(num_processors);

    parallel_permutations(num_processors);

    parallel_multisets(num_processors);

    BenchRow::print_line(cout);

    //     parallel_permutations(num_processors);

    cout << std::defaultfloat;
    cout << "\nTotal Time taken = " << chrono.Peek() << "s\n";

    return 0;
}
