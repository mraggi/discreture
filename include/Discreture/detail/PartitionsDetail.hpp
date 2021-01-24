#pragma once

#include "../IntegerInterval.hpp"
#include "../Misc.hpp"
#include "../Sequences.hpp"
#include "../VectorHelpers.hpp"

namespace discreture
{
namespace detail
{
    template <class partition, int _size>
    struct for_each_partition
    {
        using idx = typename partition::value_type;
        static_assert(std::is_integral<idx>::value,
                      "Partition must be a container of integers");
        static_assert(std::is_signed<idx>::value, "Never use unsigned integers");

        template <class Func>
        static void apply(idx n, Func f)
        {
            partition x(_size);

            for_loop(x, n, 0, n, f);
        }

        template <class Func>
        static void for_loop(partition& x, idx n, idx i, idx upper, Func f)
        {
            idx a = minimum(n, _size);
            idx b = maximum(n, _size, upper);
            for (x[i] = b; x[i] >= a; --x[i])
            {
                for_each_partition<partition, _size - 1>::for_loop(x,
                                                                   n - x[i],
                                                                   i + 1,
                                                                   x[i],
                                                                   f);
            }
        }

    private:
        static idx maximum(idx total, idx num_parts, idx upper_bound)
        {
            return std::min(upper_bound, total - num_parts + 1);
        }

        static idx minimum(idx total, idx num_parts)
        {
            auto quot_rem = std::div(total, num_parts);
            idx result = quot_rem.quot;
            if (quot_rem.rem > 0)
                ++result;
            return result;
        }
    };

    template <class partition>
    struct for_each_partition<partition, 0>
    {
        using idx = typename partition::value_type;

        template <class Func>
        static void apply(idx n, Func f)
        {
            partition x(0);
            for_loop(x, 0, 0, n, f);
        }

        template <class Func>
        static void for_loop(partition& x, idx n, idx i, idx upper, Func f)
        {
            UNUSED(n);
            UNUSED(i);
            UNUSED(upper);
            assert(n == 0 && i == x.size() && upper >= 1);
            f(x);
        }
    };

} // namespace detail
} // namespace discreture
