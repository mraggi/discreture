#include "misc_test.hpp"
#include "TimeHelpers.hpp"

using namespace dscr;
using namespace std;

void testVectorHelpers()
{
	vector<float> A = {0.2, 0.3, 0.8};
	auto B = A / 8.0;
	std::cout << B << '\n';
}



bool testNumberTheory()
{
	if (gcd<int>({{100, 155, 100, 1000, 1005}}) != 5)
	{
		return false;
	}

	if (lcm<int>({{1, 2, 3, 6, 10, 15, 30}}) != 30)
	{
		return false;
	}
	return true;
}


void testNumberTheorySpeed(int n)
{
	std::vector<int> A(n, 0);

	for (int i = 0; i < n; ++i)
	{
		A[i] = rand() % 20000 + 5700;
	}

	Chronometer C;
	auto a = gcd(A);

	if (a < 0)
	{
		std::cout << "WHAAAT?" << '\n';
// 	std::cout << "gcd: " << a << '\n';

	}

	std::cout << "Time taken for gcd of " << n << " numbers: " << C.Peek() << '\n';
}
