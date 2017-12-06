#include <iostream>
#include <vector>
#include <algorithm>
#include "NumberTheory.hpp"
#include "VectorHelpers.hpp"
#include "TimeHelpers.hpp"

using namespace std;
using namespace dscr;

bool testFillPrimes()
{
	PrimeFactorizer P(1224);
	vector<long> U = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223};
	cout << "Here are the first few prime numbers: " << vector<long>(P.primes.begin(), P.primes.begin()+30) << endl;
	
	return (P.primes == U);
}

bool testPrimeFactorization()
{
	PrimeFactorizer P(100000);
	
	for (long n = 1; n < 20000; ++n)
	{
		auto T = P.prime_factorization(n);
		
		if (n != long(T))
		{
			cout << "This is not the correct factorization of " << n << ": " << endl;
			cout << T << endl;
			return false;
		}
		if (n < 200)
			cout << n << " = " << T << endl;
	}
	
	Chronometer C;
    srand(time(nullptr));
    
    long num = 0;
    while (C.Peek() < 0.01)
    {
        long n = rand()%100000000;
        auto T = P.prime_factorization(n);
        if (n != long(T))
        {
            cout << "This is not the correct factorization of " << n << ": " << endl;
			cout << T << endl;
            cout << "because " << n << " != " << long(T) << endl;
			return false;
        }
        for (auto t : T)
        {
            if (!P.is_prime(t.p))
			{
				cout << "In the factorization of " << n << " this is not a prime number!!!: " << t.p << endl;
                return false;
			}
        }
        ++num;
//         cout << "num = " << num << endl;
    }
    cout << "Factorized " << num << " random numbers " << endl;
	
	return true;
}

bool testIsPrime()
{
	PrimeFactorizer P(1000);
	for (auto p : P.primes)
	{
		if (!P.is_prime(p))
			return false;
	}
	if (P.is_prime(1))
		return false;
	if (P.is_prime(4))
		return false;
	if (P.is_prime(6))
		return false;
	if (P.is_prime(9))
		return false;
	if (P.is_prime(10))
		return false;
	if (P.is_prime(8))
		return false;
	if (P.is_prime(12))
		return false;
	if (P.is_prime(100))
		return false;

	return true;
}

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

bool testGCDandLCM()
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

bool testNumberTheory()
{
	if (!testFillPrimes())
	{
		cout << "Fill primes test failed" << endl;
		return false;
	}
	
	if (!testIsPrime())
	{
		cout << "IsPrime test failed" << endl;
		return false;
	}
	
	if (!testPrimeFactorization())
	{
		cout << "Prime Factorization test failed" << endl;
		
		return false;
	}
	
	if (!testGCDandLCM())
	{
		
		return false;
	}
	
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
