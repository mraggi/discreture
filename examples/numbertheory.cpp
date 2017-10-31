#include <iostream>
#include <vector>
#include <algorithm>
#include "NumberTheory.hpp"
#include "VectorHelpers.hpp"
#include "TimeHelpers.hpp"
// #include "UTests/numbertheorytests.hpp"

using namespace std;
using namespace dscr;

int main()
{
    Chronometer C;
    PrimeFactorizer P(5000);
    
    
//     cout << "Primes (found in " << C.Reset() << "s): " << endl;
// 	cout << P.primes << endl;
	for (int i = 1; i < 1000; ++i)
	{
		auto PF = P.prime_factorization(i);
		cout << PF << endl;
// 		P.print(PF);
	}
	
// 	PrimeFactorizer P2;
// 	P2.old_fill_primes_up_to(50000000);
//     cout << "old Primes (found in " << C.Reset() << "s): "  << endl;
// 	cout << P2.primes << endl;

	return 0;
}
