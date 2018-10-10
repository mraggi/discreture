#pragma once

#include "../Misc.hpp"
#include "../VectorHelpers.hpp"

namespace discreture
{
namespace detail
{
    template <class multiset, int _size>
    struct for_each_multiset
    {
        using idx = typename multiset::value_type;

        template <class Func>
        static void apply(const multiset& total, Func f)
        {
            multiset x(_size);
            for_loop(x, total, _size - 1, f);
        }

        template <class Func>
        static void for_loop(multiset& x, const multiset& total, idx i, Func f)
        {
            for (x[i] = 0; x[i] <= total[i]; ++x[i])
            {
                for_each_multiset<multiset, _size - 1>::for_loop(x, total, i - 1, f);
            }
        }
    };

    template <class multiset>
    struct for_each_multiset<multiset, 0>
    {
        using idx = typename multiset::value_type;

        template <class Func>
        static void apply(const multiset& total, Func f)
        {
            multiset x(0);
            for_loop(x, total, 0, f);
        }

        template <class Func>
        static void for_loop(multiset& x, const multiset& total, idx i, Func f)
        {
            f(x);
            UNUSED(total);
            UNUSED(i);
        }
    };
} // namespace detail

} // namespace discreture
