#include "Tests.hpp"
//#include <gsl/gsl_combination.h> // uncomment to test GSL combinations

using namespace dscr;

void testVectorHelpers()
{
	vector<float> A = {0.2, 0.3, 0.8};
	auto B = A / 8.0;
	cout << B << endl;
}


bool testCombinations()
{
	cout << "========== Testing Combinations ==========" << endl;
	
	cout << " Use test: " << endl;
	combinations X(10,4);
	size_t i = 0;
	
	for (const auto& x : X)
	{
		cout << "\t" << i << " == " << X.get_index(x) << " -> " << x << endl;
		if (i != X.get_index(x))
			return false;
		++i;
	}
	
	// iterator operator tests
	cout << " Iterator operator tests" << endl;
	auto myIter = X.begin();
	cout << *(myIter + 23) << " == ";
	myIter += 46;
	cout << *(myIter - 23) << endl;
	int d = 76;
	cout << d << " == " << (myIter + d) - myIter << endl;
	
	
	// Checking correct order
	cout << " Correct order test: " << endl;
	for (auto it = X.begin(); it != X.end(); ++it)
	{
		auto itnext = it+long(1);
		if (itnext == X.end())
			break;
		if (!X.compare(*it, *itnext))
			return false;
	}
	
	cout << " Reverse use test: " << endl;
	basic_combinations<lluint> Y(6,3);
	i = 0;
	for (auto it = Y.rbegin(); it != Y.rend(); ++it,++i)
	{
		cout << "\t" << i << " -> " << *it << " == " << Y[Y.size()-i-1] << endl;
		if (*it != Y[Y.size()-i-1])
			return false;
	}
	
	cout << " Edge case test: " << endl;
	basic_combinations<uchar> Z(5,8);
	for (const auto& z : Z)
	{
		cout << z << endl;
		return false;
	}
	
	cout << " find_if test: " << endl;
	combinations W(20,6);
	
	auto predicate1 = [](const vector<int>& comb) -> bool
	{
		for (size_t i = 0; i < comb.size()-1; ++i)
		{
			if (2*comb[i]+1 > comb[i+1])
				return false;
		}
		return true;
	};
	auto predicate2 = [](const vector<int>& comb) -> bool
	{
		for (size_t i = 0; i < comb.size()-1; ++i)
		{
			if (comb[i]+3 < comb[i+1])
				return false;
			if (comb[i]+1 == comb[i+1])
				return false;
		}
		return true;
	};
	
	auto iter = W.find_if(predicate1);
	if (iter != W.end())
	{
		cout << "Found this one: " << *iter << endl;
		if (!predicate1(*iter))
		{
			cout << "But it does NOT satisfy the predicate!" << endl;
			return false;
		}
		
		
	}
	else
	{

		cout << "No combination satisfies the condition" << endl;
		
		// verify that indeed no combination satisfies the predicate
		if (W.get_n() < 30)
		{
			for (const auto& w : W)
				if (predicate1(w)) return false;
			cout << " and it checks out!!" << endl;
		} else
		{
			cout << "\tbut this W is too large to actually check one by one." << endl;
		}
	}
// 	return true;
	
	cout << "These are the permutations that satisfy the predicate: " << endl;
	auto T = W.find_all(predicate2);
	for (const auto& t : T)
		cout << t << endl;
	
	cout << "Checking one by one: " << endl;
	size_t numpred = 0;
	if (W.get_n() < 30)
	{
		for (const auto& w : W)
		{
			if (predicate2(w))
			{
				cout << w << endl;
				
				++numpred;
			}
		}
		if (numpred != T.size())
		{
			cout << "Error in find_all: a one-by-one check found a different number than a find_all check" << endl;
			return false;
		}
	} else
	{
		cout << "\tbut this W is too large to actually check one by one." << endl;
	}
	
	return true;
}

bool testPermutations()
{
	cout << "========== Testing Permutations ==========" << endl;
	
	cout << " Use test: " << endl;
	permutations X(4);
	size_t i = 0;
	
	for (const auto& x : X)
	{
		cout << "\t" << i << " = " << X.get_index(x) << " -> " << x << endl;
		if (i != X.get_index(x))
			return false;
		++i;
	}
	
	cout << " Reverse use test: " << endl;
	basic_permutations<lluint> Y(5);
	i = 0;
	for (auto it = Y.rbegin(); it != Y.rend(); ++it, ++i)
	{
		cout << "\t" << i << " -> " << *it << " == " << Y[Y.size()-i-1] << endl;
		if (*it != Y[Y.size() - i - 1])
			return false;
	}
	
	cout << "Edge case test: " << endl;
	basic_permutations<uchar> Z(0);
	for (const auto& z : Z)
	{
		cout << z << endl;
	}
	return true;
}

bool testSetPartitions()
{
	
	set_partitions X(5);
	int i = 0;
	for (auto& x : X)
	{
		cout << i << ": " << x << endl;
		++i;
	}
	
	set_partitions Y(7,3,4); // set partitions of 7 with either 3 or 4 parts
	for (auto& y : Y)
		cout << y << endl;
	return true;
}

bool testSubsets()
{
	cout << "========== Testing Subsets ==========" << endl;
	
	cout << " Use test: " << endl;
	subsets X(4);
	size_t i = 0;
	
	for (const auto& x : X)
	{
		cout << "\t" << i << " = " << X.get_index(x) << " -> " << x << endl;
		if (i != X.get_index(x))
			return false;
		++i;
	}
	
	cout << " Reverse use test: " << endl;
	basic_subsets<lluint> Y(5);
	i = 0;
	for (auto it = Y.rbegin(); it != Y.rend(); ++it, ++i)
	{
		cout << "\t" << i << " -> " << *it << " == " << Y[Y.size()-i-1] << endl;
		if (*it != Y[Y.size() - i - 1])
			return false;
	}
	
	cout << "Edge case test: " << endl;
	basic_subsets<uchar> Z(0);
	for (const auto& z : Z)
	{
		cout << z << endl;
	}
	return true;
	
}

bool testMultiset()
{
	multisets X({1,0,3,1});
	for (const auto& x : X)
		cout << x << endl;
	return true;
}
bool testPartitions()
{
	int n = 10;
	partitions X(n);
	
	for (const auto& x : X)
	{
		cout << x << endl;
		if (static_cast<int>(Sum(x)) != n)
			return false;
	}
	
	basic_partitions<unsigned char> Y(8);
	
	for (const auto& y : Y)
		cout << y << endl;
	
	
	return true;
}

bool dyckpathiscorrect(const vector<int>& x)
{
	int suma = 0;
	for (auto u : x)
	{
		suma += u;
		if (suma < 0)
			return false;
	}
	if (suma != 0)
		return false;
	
	return true;
}

bool testDyckPaths()
{
	dyck_paths X(3);
	for (const auto& x : X)
	{
		cout << x << endl;
		if (!dyckpathiscorrect(x))
			return false;
	}
	
	for (const auto& x : X)
		cout << dyck_paths::to_string(x, "()") << endl;
	
	dyck_paths Y(0);
	for (const auto& x : Y)
		cout << x << endl;
	return true;
}

bool testMotzkin()
{
	motzkin_paths X(4);
	for (const auto& x : X)
	{
		cout << x << endl;
		if (!dyckpathiscorrect(x))
			return false;
	}
	
	for (const auto& x : X)
		cout << motzkin_paths::to_string(x) << endl;
	
	return true;
}

void testCombinationsSpeed(int n, int k)
{
	Chronometer();
	lluint i = 0;
	combinations X(n,k);
	for (const auto& x : X)
	{
		if (x[0] == 1)
			++i;
	}
	cout << "Time taken to see all (" << n << " choose " << k << ") = " << X.size() << " combinations: " << Chronometer() << "s" <<  endl;

	i = 0;
	for (auto it = X.rbegin(); it != X.rend(); ++it)
	{
		if ((*it)[0] == 1)
			++i;
	}
	cout << "Time taken to see all (" << n << " choose " << k << ") = " << X.size() << " combinations in reverse order: " << Chronometer() << "s" <<  endl;
}

void testPermutationsSpeed(int n)
{
	Chronometer();
	permutations X(n);
	
	lluint i = 0;
	for (const auto& x : X)
	{
		if (x[0] == 3)
			++i;
	}
// 	cout << "i = " << i << endl;
	cout << "Time taken to see all " << n << "! = " << X.size() << " permutations: " << Chronometer() << "s" << endl;
}

void testSubsetsSpeed(int n)
{
	Chronometer();
	subsets X(n);
	lluint i = 0;
	for (const auto& x : X)
		if (x[3])
			++i;
// 	cout << "i = " << i << endl;
	cout << "Time taken to see all 2^" << n << " = " << X.size() << " subsets : " << Chronometer() << "s" << endl;
	
 	subsets_fast XF(n);
	for (const auto& x : XF)
		if (x[3])
			++i;
	cout << "Time taken to see all 2^" << n << " = " << X.size() << " subsets (fast mode) : " << Chronometer() << "s" << endl;
	
}

void testMultisetSpeed()
{
	Chronometer();
	multisets X({2,2,1,3,4,2,3,3,2,3,4,4,5,0,0,1,0,2,2});
	size_t i = 0;
	for (const auto& x : X)
	{
		if (x[1] == 2)
			++i;
	}
	cout << "Time taken to see all " << X.size() << " multisets: " << Chronometer() << "s" << endl;

}

void testPartitionsSpeed(int n)
{
	Chronometer();
	partitions X(n);
	
	lluint i = 0;
	for (const auto& x : X)
	{
		if (x[0] == 3)
			++i;
	}
// 	cout << "i = " << i << endl;
	cout << "Time taken to see all " << X.size() << " partitions of size " << n  << ": " << Chronometer() << "s" << endl;
}


void testSetPartitionSpeed(int n)
{
	Chronometer();
	set_partitions X(n);
	
	lluint i = 0;
	for (const auto& x : X)
	{
		if (x[0][1] == 3)
			++i;
	}
// 	cout << "i = " << i << endl;
	cout << "Time taken to see all " << X.size() << " set partitions of size " << n  << ": " << Chronometer() << "s" << endl;
	
	Chronometer();
	set_partitions Y(n+2,4);
	
	i = 0;
	for (const auto& y : Y)
	{
		if (y[0][1] == 3)
			++i;
	}
// 	cout << "i = " << i << endl;
	cout << "Time taken to see all " << Y.size() << " set partitions a set of " << n+2 << " elements with " << 4 << " parts: " << Chronometer() << "s" << endl;
	
	
}

void testDyckPathsSpeed(int n)
{
	Chronometer();
	dyck_paths X(n);
	
	lluint i = 0;
	for (const auto& x : X)
	{
		if (x[0] == 1)
			++i;
	}
// 	cout << "i = " << i << endl;
	cout << "Time taken to see all " << X.size() << " dyck paths of size " << n  << ": " << Chronometer() << "s" << endl;
}

void testMotzkinSpeed(int n)
{
	Chronometer();
	motzkin_paths X(n);
	
	lluint i = 0;
	for (const auto& x : X)
	{
		if (x[0] == 1)
			++i;
	}
// 	cout << "i = " << i << endl;
	cout << "Time taken to see all " << X.size() << " motzkin paths of size " << n  << ": " << Chronometer() << "s" << endl;
}

void testCorrectness()
{
	if (
	testCombinations() 	&&
	testPermutations() 	&&
	testSubsets() 		&&
	testPartitions()	&&
	testMultiset()		&&
	testDyckPaths()		&&
	testSetPartitions()		&&
	testMotzkin())
		cout << "\n\n All tests PASSED!" << endl;
	else
		cout << "SOME TESTS FAILED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	
}

void testSpeed()
{
	testCombinationsSpeed();
	testPermutationsSpeed();
	testSubsetsSpeed();
	testPartitionsSpeed();
	testMultisetSpeed();
	testDyckPathsSpeed();
	testMotzkinSpeed();
	testSetPartitionSpeed();
}

void testManualCombinations()
{
	lluint i = 0;
	short n = 33;
	++n;
	--n;
	for (int a00 = 0; a00 < n-15; ++a00)
	for (int a01 = a00+1; a01 < n-14; ++a01)
	for (int a02 = a01+1; a02 < n-13; ++a02)
	for (int a03 = a02+1; a03 < n-12; ++a03)
	for (int a04 = a03+1; a04 < n-11; ++a04)
	for (int a05 = a04+1; a05 < n-10; ++a05)
	for (int a06 = a05+1; a06 < n-9; ++a06)
	for (int a07 = a06+1; a07 < n-8; ++a07)
	for (int a08 = a07+1; a08 < n-7; ++a08)
	for (int a09 = a08+1; a09 < n-6; ++a09)
	for (int a10 = a09+1; a10 < n-5; ++a10)
	for (int a11 = a10+1; a11 < n-4; ++a11)
	for (int a12 = a11+1; a12 < n-3; ++a12)
	for (int a13 = a12+1; a13 < n-2; ++a13)
	for (int a14 = a13+1; a14 < n-1; ++a14)
	for (int a15 = a14+1; a15 < n; ++a15)
	{
		++n;
		if (a15 == 25 || n > 454)
			++i;
		--n;
	}
	cout << "total num: " << i << endl;
}


/*
void testGSLComb()
{
	gsl_combination * c;
	size_t i = 0;

	for (int n = 8; n < 34; n += 1)
	{
		c = gsl_combination_calloc (n, n/2);
		do
		{
			if (gsl_combination_get(c,3) == 1)
				++i;
		}
		while (gsl_combination_next (c) == GSL_SUCCESS);
		gsl_combination_free (c);
		
		std::cout << "time for gsl combinations " << n << " choose " << n/2 <<  " = " << dscr::Chronometer() << std::endl;
	}
}*/