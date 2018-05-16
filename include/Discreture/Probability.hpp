#pragma once

#include "Misc.hpp"
#include <ctime>
#include <random>
namespace dscr
{
namespace random
{
    // Who came up with the dumb C++11 way of getting random stuff?
    // It's obviously missing some utility functions. Here they are.

    /**
     *@brief Just a helper function to get the default random engine
     */
    inline std::default_random_engine& random_engine()
    {
        using RE = std::default_random_engine;
        using result_type = RE::result_type;
        static std::default_random_engine e(
          static_cast<result_type>(time(nullptr)));
        return e;
    }

    /**
     *@brief Returns true with probability p and false with probability 1-p
     *@return true or false according to probability p, which must be a number
     *between 0 and 1.
     */
    inline bool probability_of_true(double p)
    {
        static std::bernoulli_distribution d(p);
        return d(random_engine());
    }

    /**
     *@brief "I just wanted a random integer!
     *@return A random integer in the range [from,thru), with uniform
     *probability distribution
     */
    template <class IntType = int>
    IntType random_int(IntType from, IntType thru)
    {
        static std::uniform_int_distribution<IntType> d{};
        using parm_t = typename decltype(d)::param_type;
        return d(random_engine(), parm_t{from, --thru});
    }

    /**
     *@brief "I just wanted a random float!
     *@return A random float number in the range [from,thru), with uniform
     *probability distribution
     */
    template <class FloatType = double>
    FloatType random_real(FloatType from, FloatType upto)
    {
        static std::uniform_real_distribution<> d{};
        using parm_t = decltype(d)::param_type;
        return d(random_engine(), parm_t{from, upto});
    }

} // namespace random
} // namespace dscr
