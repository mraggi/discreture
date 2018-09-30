#pragma once

#include <gtest/gtest.h>
#include <iostream>

#include "Discreture/IntegerInterval.hpp"
#include "Discreture/Misc.hpp"
#include "Discreture/Probability.hpp"
#include "Discreture/Reversed.hpp"

template <class Container, class CheckElement>
void test_forward_iteration(const Container& C, CheckElement check_elem)
{
    int i = 0;
    for (auto&& c : C)
    {
        check_elem(c);
        ASSERT_EQ(c, C[i]);
        ++i;
    }
    ASSERT_EQ(C.size(), i);

    using elem_type = typename Container::value_type;
    std::set<elem_type> S(C.begin(), C.end());
    ASSERT_EQ(S.size(), C.size());
}

template <class Container, class CheckElement>
void test_reverse_iteration(const Container& C, CheckElement check_elem)
{
    int i = C.size() - 1;
    for (auto&& c : reversed(C))
    {
        check_elem(c);
        ASSERT_EQ(c, C[i]);
        --i;
    }
    ASSERT_EQ(i, -1);
    i = 0;
    for (auto&& c : reversed(reversed(C)))
    {
        ASSERT_EQ(c, C[i]);
        ++i;
    }
    ASSERT_EQ(i, C.size());

    using elem_type = typename Container::value_type;
    std::set<elem_type> S(C.rbegin(), C.rend());
    ASSERT_EQ(S.size(), C.size());
}

template <class Iter, class difference_type>
void dumb_advance(Iter& it, difference_type distance)
{
    while (distance > 0)
    {
        ++it;
        --distance;
    }
    while (distance < 0)
    {
        --it;
        ++distance;
    }
}

template <class Container, class CheckElement>
void test_advance_iterator(const Container& C, CheckElement check_elem)
{
    int n = C.size();

    if (n <= 0)
        return;

    int num_times = 2*n;

    auto it = C.begin();
    int current = 0;
    for (auto _ : discreture::NN(num_times))
    {
        discreture::UNUSED(_);
        int target = discreture::random::random_int(0, n);
        int distance = target - current;

        if (discreture::random::probability_of_true(0.5))
            std::advance(it, distance);
        else
            dumb_advance(it, distance);
        current = target;
        check_elem(*it);
        ASSERT_EQ(*it, C[current]);
        ASSERT_EQ(*it, *(C.begin() + current));
    }
}

template <class Container, class CheckElement>
void test_advance_reverse_iterator(const Container& C, CheckElement check_elem)
{
    int n = C.size();

    if (n <= 0)
        return;

    int num_times = 2*n;

    auto rit = C.rbegin();
    int current = 0;

    for (auto _ : discreture::NN(num_times))
    {
        discreture::UNUSED(_);
        int target = discreture::random::random_int(0, n);
        int distance = target - current;

        if (discreture::random::probability_of_true(0.5))
            std::advance(rit, distance);
        else
            dumb_advance(rit, distance);
        current = target;
        check_elem(*rit);
        ASSERT_EQ(*rit, C[C.size() - 1 - current]);
        ASSERT_EQ(*rit, *(C.rbegin() + current));
    }
}

template <class Container, class CheckElement>
void test_container_full(const Container& C, CheckElement check_elem)
{
    test_forward_iteration(C, check_elem);

    test_reverse_iteration(C, check_elem);

    test_advance_iterator(C, check_elem);
    test_advance_reverse_iterator(C, check_elem);
}

template <class Container>
void test_container_foreach(const Container& X)
{
    auto it = X.begin();
    size_t size = 0;
    X.for_each([&it, &size](const auto& x) {
        ASSERT_EQ(x, *it);
        ++it;
        ++size;
    });
    ASSERT_EQ(size, X.size());
}
