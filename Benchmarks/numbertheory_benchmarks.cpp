#include <iostream>
#include <vector>
#include <algorithm>
#include "NumberTheory.hpp"
#include "VectorHelpers.hpp"
#include "TimeHelpers.hpp"

using namespace std;
using namespace dscr;


bool testPrimeSpeed()
{
	cout << "Starting prime factorization speed" << endl;
	PrimeFactorizer P(500000);
	
	Chronometer C;
	int numtimes = 1;
	
	for (int i = 0; i < numtimes; ++i)
	{
		long numtofactor = (long(rand())+1)*(long(rand())+1)+1;
		auto T = P.prime_factorization(numtofactor);
// 		cout << numtofactor << " = " << T << '\n';
	}
	
	
	cout << "Time taken to factorize " << numtimes << " numbers: " << C.Peek() << 's' << endl;
	
	return true;
}

void testNumberTheorySpeed(long n)
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
