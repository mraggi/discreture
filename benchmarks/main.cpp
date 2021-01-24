#include "bench_declarations.hpp"
#include "benchmarker.hpp"
#include "benchtable.hpp"
#include "external_benches.hpp"

// WARNING: I'm probably suffering from alignment issues, so I'm not sure how
// valid these benchmarks are. That is: if I add or remove functions that have
// nothing to do with the benchmarks, the benchmarks change considerably!! Very
// strange!

using std::cout;
using std::endl;

int main()
{
    using discreture::binomial;
    using std::operator""s;
    std::ios_base::sync_with_stdio(false);
    discreture::Chronometer chrono;

    cout << "|================================ Starting Speed Tests "
            "===============================|"
         << endl;

    BenchRow::print_header(cout);
    BenchRow::print_line(cout);

    bench_combinations();

    BenchRow::print_line(cout);

    bench_lex_combs();

    BenchRow::print_line(cout);

    bench_multisets();

    BenchRow::print_line(cout);

    bench_permutations();

    BenchRow::print_line(cout);

    bench_partitions();

    BenchRow::print_line(cout);

    bench_set_partitions();

    BenchRow::print_line(cout);

    bench_dyck();

    BenchRow::print_line(cout);

    bench_motzkin();

    BenchRow::print_line(cout);

    cout << std::defaultfloat;
    cout << "\nTotal Time taken = " << chrono.Peek() << "s" << endl;

    return 0;
}
