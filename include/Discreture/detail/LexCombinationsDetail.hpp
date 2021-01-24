#pragma once

#include "../Misc.hpp"
#include "../VectorHelpers.hpp"

namespace discreture
{

namespace detail
{
    template <class combination, int _size>
    struct for_each_lex_combinations
    {
        using idx = typename combination::value_type;

        template <class Func>
        static void apply(idx n, Func f)
        {
            combination x(_size);
            for_loop(x, 0, 0, n - _size + 1, f);
        }

        template <class Func>
        static void for_loop(combination& x, idx i, idx a, idx b, Func f)
        {
            for (x[i] = a; x[i] < b; ++x[i])
            {
                for_each_lex_combinations<combination, _size - 1>::for_loop(
                  x, i + 1, x[i] + 1, b + 1, f);
            }
        }
    };

    template <class combination>
    struct for_each_lex_combinations<combination, 0>
    {
        using idx = typename combination::value_type;

        template <class Func>
        static void apply(idx n, Func f)
        {
            combination x(0);
            for_loop(x, 0, 0, n, f);
        }

        template <class Func>
        static void for_loop(combination& x, idx i, idx a, idx b, Func f)
        {
            UNUSED(i);
            UNUSED(a);
            UNUSED(b);
            f(x);
        }
    };
} // namespace detail

} // namespace discreture
