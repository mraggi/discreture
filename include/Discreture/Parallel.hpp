#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#include "TimeHelpers.hpp"

namespace discreture
{

template <class RAIter>
std::vector<RAIter> divide_work_in_equal_parts(RAIter first,
                                               RAIter last,
                                               size_t num_processors)
{
    auto n = std::distance(first, last);

    size_t block_size = n/num_processors;

    std::vector<RAIter> result;
    result.reserve(num_processors + 1);

    for (size_t i = 0; i < num_processors; ++i)
    {
        result.emplace_back(first);
        std::advance(first, block_size);
    }
    result.emplace_back(last);
    return result;
}

template <class Container>
auto divide_work_in_equal_parts(const Container& C, size_t num_processors)
  -> std::vector<typename Container::iterator>
{
    return divide_work_in_equal_parts(C.begin(), C.end(), num_processors);
}

template <class RAIter, class Function>
void parallel_for_each(RAIter first, RAIter last, Function f, size_t num_processors)
{
    Chronometer C;
    auto work = divide_work_in_equal_parts(first, last, num_processors);

    std::vector<std::thread> threads;
    threads.reserve(num_processors);

    for (size_t i = 0; i < num_processors; ++i)
    {
        threads.emplace_back(std::thread([&work, &f, i]() {
            auto local_first = work[i];
            auto local_last = work[i + 1];
            for (; local_first != local_last; ++local_first)
            {
                f(*local_first);
            }
        }));
    }

    for (auto& t : threads)
    {
        t.join();
    }
}

template <class Container, class Function>
void parallel_for_each(Container& C, Function f, size_t num_processors)
{
    parallel_for_each(C.begin(), C.end(), f, num_processors);
}

} // namespace discreture
