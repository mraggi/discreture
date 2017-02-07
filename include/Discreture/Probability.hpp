#pragma once

#include "Misc.hpp"
#include <ctime>
#include <random>
namespace dscr
{
// Who came up with the dumb C++11 way of getting random stuff?
// It's obviously missing some utility functions. Here they are.

/**
 * @brief Just a helper function to get the default random engine
 */
inline std::default_random_engine& random_engine()
{
	static std::default_random_engine e {};
	return e;
}

/**
 * @brief Returns true with probability p and false with probability 1-p
 * @return true or false according to probability p, which must be a number between 0 and 1.
 */
inline bool probability_of_true(double p)
{
	static std::bernoulli_distribution d(p);
	return d(random_engine());
}

/**
 * @brief The modern way of setting a random seed.
 */
inline void randomize()
{
	srand(time(nullptr));
	static std::random_device rd {};
	random_engine().seed(rd());
}


/**
 * @brief "I just wanted a random integer!
 * @return A random integer in the range [from,thru), with uniform probability distribution
 */
template <class IntType = int>
IntType random_int(IntType from, IntType thru)
{
	static std::uniform_int_distribution<IntType> d {};
	using parm_t = typename decltype(d)::param_type;
	return d(random_engine(), parm_t {from, thru - 1});
}

/**
 * @brief "I just wanted a random integer!
 * @return A random integer in the range [from,thru), with uniform probability distribution
 */
template <class FloatType = double>
FloatType random_real(FloatType from, FloatType upto)
{
	static std::uniform_real_distribution<> d {};
	using parm_t = decltype(d)::param_type;
	return d(random_engine(), parm_t {from, upto});
}
}
