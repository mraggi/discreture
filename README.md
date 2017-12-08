# Discreture

This is a modern C++14 library designed to facilitate combinatorial research by providing fast and easy iterators to a few combinatorial objects, such as combinations, permutations, partitions, and others. The idea is to have discreture's lazy containers interface resemble the STL containers as much as possible, by providing the standard ways of iterating over them.

In addition, many of the algorithms described in the standard <algorithm> library work as-is in these containers, as if the containers were marked as const.

This library is provided as a header-only library.

# Quick preview:

```c++
	#include <iostream>
	#include <discreture.hpp>
	int main()
	{
		using namespace std;
		using namespace dscr; //for expository purposes.
		
		;
		for (auto& x : combinations(5,3))
			cout << x << endl;
		
		return 0;
	}
```
The above code would produce the following output:

	0 1 2
	0 1 3
	0 2 3
	1 2 3
	0 1 4
	0 2 4
	1 2 4
	0 3 4
	1 3 4
	2 3 4

You need to compile with the -std=c++14 flag:
`g++ -std=c++14 -O2 main.cpp`

Some tests show discreture is usually faster when compiled with clang++ instead of g++. Full benchmarks at the end of the README.

# Installation

Discreture is a header-only library, so making sure your programs have access to the .hpp files (all files inside "include" dir) is enough. Just copy them to your project's include folders. 

To do a system-wide install, do the standard cmake/make dance:
```sh
	git clone https://github.com/mraggi/discreture
	cd discreture
	mkdir build
	cd build
	cmake ..
	make
	sudo make install
```

This will install everything under `/usr/local/` by default. If you wish to install to some other directory, replace the cmake .. above by something like `cmake .. -DCMAKE_INSTALL_PREFIX=/usr/`.

There are three options: BUILD_EXAMPLES, BUILD_TESTS and BUILD_BENCHMARKS. To use discreture you don't need to compile anything, but the examples are compiled by default. You can compile the examples by replacing the `cmake ..` part by:
	`cmake .. -DBUILD_EXAMPLES=ON`

# How to start using the library
To use the library, after compiling, just add `#include <discreture.hpp>` to your project and make sure you are using -std=c++14. With the GCC compiler this can be done by compiling like this: `g++ -std=c++14 myfile.cpp`. If you wish to include only part of the library, one could do `#include <Discreture/Combinations.hpp>` for example.

# Combinatorial Objects

Within this library, one can construct a few combinatorial objects, such as:
  - Combinations
  - Permutations
  - Partitions
  - Dyck Paths
  - Motzkin Paths
  - Set Partitions
  - Multisets
  - Range

All follow the same design principle: The templated class is calles basic_SOMETHING<class T>, and the most reasonable type for T is instantiated as SOMETHING. For example, `combinations` is a typedef of `basic_combinations<int>`, and `partitions` is a typedef of `basic_partitions<int>`. T is usually an (signed) integer type, like `char`, `short`, `int`, `long`. Some tests show that on different machines different types produce faster code, so even if you don't need numbers bigger than 127 it might be a good idea to use `int` or `long` for some reason.

# Basic usage

Here is a quick preview.

```c++
combinations X(30,10); //all subsets of size 10 of {0,1,2,...,29}
for (auto& x : X) 
{ 
	// x is of type const vector<int>&, so anything that works with 
	// const vector references also works on x, such as calling x[3], etc.
}
```

You can iterate in reverse too, in the same way you would reverse-iterate an STL container.
```c++
combinations X(30,10);
for (auto it = X.rbegin(); it != X.rend(); ++it) 
{ 
	auto& x = *it;
	// x is of type const vector<int>&, so anything that works with vectors works on x
}
```

Combinations and permutations are a random-access container (although they are MUCH slower as such than forward or reverse iteration), so something like this works too:
```c++
	combinations X(30,10);
	for (size_t i = 0; i < X.size(); ++i)
	{
		auto x = X[i]; //don't do this
	}
```

This is much slower if one plans to actually iterate over all of them, but iterator arithmetic is implemented, so one could even do binary search on `X` with the following code:
```c++
	#include <algorithm>
	// ...
	combinations X(30,10);
	std::partition_point(X.begin(), X.end(), predicate);
```
where `predicate` is a unary predicate that takes a `const vector<int>&` as an argument and returns true or false, in a way that for all the first combinations it returns true and the last ones return false.

## Examples

Check the files under `examples` for a tutorial on how to use the library. Here is a taste:

For example, suppose you wanted to see all ways to add up to 20 with at most 6 numbers so that all numbers are squares. You can do:

```c++
	#include <iostream>
	#include <Discreture/Partitions.hpp>
	#include <Discreture/VectorHelpers.hpp>

	using namespace dscr;
	
	bool is_perfect_square(int n) 
	{
		if (n < 0)
			return false;
		int r = round(sqrt(n));
		return n == r*r;
	}

	int main()
	{
		
		dscr::partitions X(20,1,6);
		for (auto& x : X)
		{
			if (std::all_of(x.begin(), x.end(), is_perfect_square))
				std::cout << x << std::endl;
		}
		
		return 0;
	}
```

Then compile with the command `g++ -O2 -std=C++14 main.cpp -o out` and run `./out`. It should produce the following output:
```sh
	9 4 4 1 1 1
	16 1 1 1 1
	4 4 4 4 4
	9 9 1 1
	16 4
```

## Combinations find_if and find_all
Combinations is the most mature part of the library, and the following functions have been implemented:

```c++
	#include <iostream>
	#include <vector>
	#include <discreture.hpp>
	
	int main()
	{
		using namespace dscr;
		using namespace std;
		combinations X(10,3);
		
		// T will be an iterable object whose elements are the combinations that satisfy the predicate specified by the lambda function.
		// In this case, the lambda checks that the next to last element divides the last element.
		// The elements of T will therefore be the combinations for which every element is a divisor of the next element.
		
		auto T = X.find_all([](const auto& comb) -> bool
		{
			int k = comb.size();
			
			if (k <= 1) return true;
			
			if (comb[k-2] == 0) return false;
		
			return (comb[k-1]%comb[k-2] == 0);
		});
		for (auto& t : T)
			cout << t << endl;
	}
```

Prints out:
```
	1 2 4
	1 2 6
	1 2 8
	1 3 6
	1 3 9
	2 4 8
```

These are all combinations for which every element is a divisor of the next element. Note that not all combinations are created and then filtered, only combinations which satisfy the partial predicate (given by a lambda function) are further explored.

# Benchmarks.

## Combinations benchmarks

Two different libraries were tested: GNU Scientific Library (GSL) and euler314's library. 

The GNU Scientific Library is a well-known and mature library. For more information, [check their website](https://www.gnu.org/software/gsl/). 

Euler314's library (unnamed as far as I know) can be found [here](https://github.com/euler314/combinatorics) and provides similar functionality to discreture, although discreture provides many more features.

Iterating over all combinations of size n/2 over a set of size n took the following time:

![discreture::combinations vs GSL combinations](https://github.com/mraggi/discreture/blob/master/combvsgsl.png "discreture::combinations vs GSL combinations")


The GSL code used was the following:

```c++
	gsl_combination * c;

	c = gsl_combination_calloc (n, n/2);
	do
	{
		DoNotOptimize(*c);
	}
	while (gsl_combination_next (c) == GSL_SUCCESS);
	gsl_combination_free (c);	

```

The same code using euler314's library:

```c++
	auto end = combination_iterator<long>();

	for (auto it = combination_iterator<long>(n, n/2); it != end; ++it)
	{
		DoNotOptimize(*it);
	}
```

Compare to the following (beautiful) code, using discreture:
```c++
	for (auto& x : combinations(n,n/2))
	{
		DoNotOptimize(x);
	}
```

Or the for_each variant of discreture:
```c++
	auto X = combinations(n,n/2);
	X.for_each([](const combinations::combination& x)
	{
		DoNotOptimize(x);
	});
```


**Note**: GSL and euler314 iterates in the same order as `combinations_tree`. euler314_maximin (in gray) was a commit that adapted some of discreture's code and iterates in the same order as `combinations`. It's essentially the same code, which is why it takes exactly the same amount of time.

If you'd like to see other benchmarks, let me know. I have a lot of fun benchmarking stuff.

## Discreture vs Sagemath

This comparison isn't very fair (C++ vs python). On the same system, iterating over all (24 choose 12) combinations, sage takes 12.2 seconds. Discreture takes approximately 0.005 seconds. No point in graphing that.

## CLANG vs GCC
<!--On a i7-5820K CPU @ 3.30GHz, on Linux, compiling with -Ofast yields the following results:

| Task | Time taken CLANG 3.7.0 | Time taken GCC 5.2.0 |
| ------------- |:-------------:| :-------------:|
| Time taken to see all (32 choose 16) = 601080390 combinations 					|	 **2.29281s**		|   3.36332s   |
| Time taken to see all (32 choose 16) = 601080390 combinations in reverse order 	|	 **1.67853s**		|   3.98176s   |
| Time taken to see all 12! = 479001600 permutations								|	   1.70865s  		| **1.33693s** |
| Time taken to see all 56634173 partitions of size 90 								|	 **1.41834s**		|   1.48321s   |
| Time taken to see all 559872000 multisets 										|	 **1.84566s**		|   1.90435s   |
| Time taken to see all 477638700 dyck paths of size 18 							|	 **2.16288s**		|   2.74891s   |
| Time taken to see all 50852019 motzkin paths of size 20 							|	 **1.30359s**		|   1.46971s   |
| Time taken to see all 27644437 set partitions of size 13 							|	   0.960195s  		| **0.79946s** |
| Time taken to see all 42355950 set partitions a set of 15 elements with 4 parts 	|	   1.20166s  		| **1.01687s** |
| **Total Time**																	|	 **19.7s**			|	22.1s	   |-->

Full benchmarks, with updated compilers, coming soon!

# Acknowledgements
Manuel Alejandro Romo de Vivar (manolo) for his work on dyck paths, motzkin paths, and his contribution to partition numbers.

César Benjamín García for suggesting the name "discreture".

# Contributing
Please help us testing, debugging, benchmarking, packaging for the various distros, etc. Also, if you use discreture for your own purposes, let us know!
