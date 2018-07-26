#pragma once

#include "Parallel.hpp"
#include "Probability.hpp"
#include "Reversed.hpp"
#include "TimeHelpers.hpp"
#include "do_not_optimize.hpp"
#include "external/rang.hpp"
#include <iomanip>
#include <iostream>
#include <string>

template <class Func>
double Benchmark(Func f, int numtimes = 1)
{
    // 	f(); //warm up
    discreture::Chronometer C;
    for (int i = 0; i < numtimes; ++i)
    {
        f();
    }
    double avg = C.Reset()/numtimes;

    return avg;
}

template <class Container>
double FWIterationBenchmark(const Container& A)
{
    return Benchmark([&A]() {
        for (auto&& a : A)
        {
            DoNotOptimize(a);
        }
    });
}

template <class Container>
double ParallelBenchmark(const Container& X, int num_processors)
{
    return Benchmark([&X, num_processors]() {
        auto work = discreture::divide_work_in_equal_parts(X.begin(), X.end(), num_processors);

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

        for (auto&& t : threads)
        {
            t.join();
        }
    });
}

template <class Container>
double ReverseIterationBenchmark(const Container& A)
{
    return Benchmark([&A]() {
        for (auto&& a : reversed(A))
        {
            DoNotOptimize(a);
        }
    });
}

template <class Container>
double ForEachBenchmark(const Container& A)
{
    return Benchmark(
      [&A]() { A.for_each([](const auto& a) { DoNotOptimize(a); }); });
}

template <class Container>
double ConstructionBenchmark(const Container& A, int numtimes)
{
    return Benchmark([&A, numtimes]() {
        for (int i = 0; i < numtimes; ++i)
        {
            auto t = discreture::random::random_int<std::int64_t>(0, A.size());
            DoNotOptimize(A[t]);
        }
    });
}
