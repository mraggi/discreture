#pragma once
#include <algorithm>
#include <numeric>

#include "../IntegerInterval.hpp"
#include "../Misc.hpp"
#include "../VectorHelpers.hpp"

namespace discreture
{

namespace detail
{
    template <class combination, int _size>
    struct for_each_combination
    {
        using idx = typename combination::value_type;

        template <class Func>
        static void apply(idx n, Func f)
        {
            combination x(_size);
            for_loop(x, n, f);
        }

        template <class Func>
        static void for_loop(combination& x, idx n, Func f)
        {
            constexpr auto i = _size - 1;
            for (x[i] = i; x[i] < n; ++x[i])
            {
                for_each_combination<combination, i>::for_loop(x, x[i], f);
            }
        }
    };

    template <class combination>
    struct for_each_combination<combination, 0>
    {
        using idx = typename combination::value_type;

        template <class Func>
        static void apply(idx n, Func f)
        {
            combination x(0);
            for_loop(x, n, f);
        }

        template <class idx, class Func>
        static void for_loop(combination& x, idx n, Func f)
        {
            UNUSED(n); // for the 0 specialization
            f(x);
        }
    };
} // namespace detail

} // namespace discreture
