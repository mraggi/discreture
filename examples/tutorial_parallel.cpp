/**
 *This is a short tutorial using paralelism with discreture's containers.
 *Compile with:
 *g++ -std=c++14 tutorial_parallel.cpp -o utorial_parallel -lpthread"
 *
 *Perhaps you must add -I/path/to/discreture/include
 *
 *For more details about installing, compiling, etc. see README.md. For a basic
 *tutorial, see tutorial.cpp
 *
 *Finally, if you need help, feel free to email me at mraggi@gmail.com
 */

#include "../benchmarks/do_not_optimize.hpp"
#include "discreture.hpp" //This includes everything in discreture.
#include <iostream>
#include <string>
#include <thread>

int main()
{
    using discreture::combinations;
    using discreture::Chronometer;

    using std::cout;
    using std::endl;
    // Let's see all combinations of 40 choose 10 using 4 threads.

    int n = 40;
    int k = 10;
    size_t max_num_processors = 8;

    for (size_t num_processors = 1; num_processors <= max_num_processors;
         ++num_processors)
    {
        Chronometer C;
        auto X = combinations(n, k);
        auto work = divide_work_in_equal_parts(X.begin(), X.end(), num_processors);

        std::vector<std::thread> threads;
        threads.reserve(num_processors);

        for (size_t i = 0; i < num_processors; ++i)
        {
            threads.emplace_back(std::thread([&work, i]() {
                auto local_first = work[i];
                auto local_last = work[i + 1];
                for (; local_first != local_last; ++local_first)
                {
                    // Do something with *local_first;
                    DoNotOptimize(*local_first);
                }
            }));
        }

        for (auto& t : threads)
        {
            t.join();
        }

        cout << "Time taken to see all " << X.size() << " combinations using "
             << num_processors << " processors: " << C.Peek() << endl;
    }

    return 0;
}
