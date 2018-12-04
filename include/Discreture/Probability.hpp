#pragma once

#include "Misc.hpp"
#include <ctime>
#include <random>
namespace discreture
{
namespace random
{
    // You'll want to use something else, probably.

    /**
     *@brief Just a helper function to get the default random engine
     */
    inline std::default_random_engine& random_engine()
    {
        using RE = std::default_random_engine;
        using rt = RE::result_type;
        static std::default_random_engine eng(static_cast<rt>(time(nullptr)));
        return eng;
    }

    /**
     *@brief Returns true with probability p and false with probability 1-p
     *@return true or false according to probability p, which must be a number
     *between 0 and 1.
     */
    inline bool probability_of_true(double p)
    {
        std::bernoulli_distribution d(p);
        return d(random_engine());
    }

    /**
     *@brief "I just wanted a random integer!
     *@return A random integer in the range [from,upto), with uniform
     *probability distribution
     */
    template <class IntType = int>
    IntType random_int(IntType from, IntType upto)
    {
        static std::uniform_int_distribution<IntType> d{};
        using parm_t = typename decltype(d)::param_type;
        return d(random_engine(), parm_t{from, --upto});
    }

    /**
     *@brief "I just wanted a random float!
     *@return A random float number in the range [from,upto), with uniform
     *probability distribution
     */
    template <class FloatType = double>
    FloatType random_real(FloatType from, FloatType upto)
    {
        static std::uniform_real_distribution<> d{};
        using parm_t = typename decltype(d)::param_type;
        return d(random_engine(), parm_t{from, upto});
    }

} // namespace random
} // namespace discreture
