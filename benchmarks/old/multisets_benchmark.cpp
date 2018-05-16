#include "multisets_benchmark.hpp"
#include "../do_not_optimize.hpp"
#include "TimeHelpers.hpp"

void testMultisetSpeed()
{
    using namespace dscr;
    Chronometer C;
    multisets X({2, 2, 1, 3, 4, 2, 3, 3, 2, 3, 4, 4, 5, 0, 0, 1, 0, 2, 2});
    size_t i = 0;

    for (const auto& x : X)
    {
        DoNotOptimize(x);
    }

    std::cout << "Time taken to see all " << X.size()
              << " multisets: " << C.Reset() << "s" << '\n';
}
