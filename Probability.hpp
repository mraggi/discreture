#pragma once

#include "Misc.hpp"
#include <ctime>
#include <random>
namespace dscr
{
	bool probability_of_true(double p);

	
	void randomize();
	
// 	inline void SetSeedWithTime() { Randomize(); } // for compatibility purposes!
	inline void set_seed_with_time() { srand(std::time(NULL)); }
	std::default_random_engine & random_engine();

	template <class IntType>
	IntType random_int( IntType from, IntType thru )
	{
		static std::uniform_int_distribution<IntType> d{};
		using parm_t = typename decltype(d)::param_type;
		return d( random_engine(), parm_t{from, thru-1} );
	}
	
	
	double random_real( double from, double upto );
	
	double random_real();
}
