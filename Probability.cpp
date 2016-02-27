#include "Probability.hpp"

namespace dscr 
{
	std::default_random_engine & random_engine()
	{
		static std::default_random_engine e{};
		return e;
	}

	
	
	bool probability_of_true(double p)
	{
		static std::bernoulli_distribution d(p);
		return d(random_engine());
	}

	void randomize()
	{
		static std::random_device rd{};
		random_engine().seed(rd());
	}

	double random_real( double from, double upto )
	{
		static std::uniform_real_distribution<> d{};
		using parm_t = decltype(d)::param_type;
		return d( random_engine(), parm_t{from, upto} );
	}
	
// 	double random()
// 	{
// 		return random(0.0,1.0);
// 	}
}