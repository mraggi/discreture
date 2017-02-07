#include "permutations_test.hpp"
#include "TimeHelpers.hpp"

using namespace dscr;

bool testPermutations()
{
	std::cout << "========== Testing Permutations ==========" << '\n';

	std::cout << " Use test: " << '\n';
	permutations X(4);
	size_t i = 0;

	for (const auto& x : X)
	{
		std::cout << "\t" << i << " = " << X.get_index(x) << " -> " << x << '\n';

		if (i != X.get_index(x))
		{
			return false;
		}

		++i;
	}

	std::cout << " Reverse use test: " << '\n';
	basic_permutations<lluint> Y(5);
	i = 0;

	for (auto it = Y.rbegin(); it != Y.rend(); ++it, ++i)
	{
		std::cout << "\t" << i << " -> " << *it << " == " << Y[Y.size() - i - 1] << '\n';

		if (*it != Y[Y.size() - i - 1])
		{
			return false;
		}
	}

	std::cout << "Edge case test: " << '\n';
	basic_permutations<unsigned char> Z(0);

	for (const auto& z : Z)
	{
		std::cout << z << '\n';
	}

	return true;
}



void testPermutationsSpeed(int n)
{
	Chronometer C;
	permutations X(n);

	lluint i = 0;

	for (const auto& x : X)
	{
		if (x[0] == 3)
		{
			++i;
		}
	}

// 	std::cout << "i = " << i << '\n';
	std::cout << "Time taken to see all " << n << "! = " << X.size() << " permutations: " << C.Reset() << "s" << '\n';


}