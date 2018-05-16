#include "motzkin_benchmark.hpp"
#include "../do_not_optimize.hpp"
#include "TimeHelpers.hpp"
#include "dyck_benchmark.hpp"

using namespace dscr;

void testMotzkinSpeed(int n)
{
    Chronometer C;
    motzkin_paths X(n);

    for (const auto& x : X)
    {
        DoNotOptimize(x);
    }

    // 	std::cout << "i = " << i << '\n';
    std::cout << "Time taken to see all " << X.size()
              << " motzkin paths of size " << n << ": " << C.Reset() << "s"
              << '\n';
}
