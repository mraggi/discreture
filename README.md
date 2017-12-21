[![Build Status](https://travis-ci.org/mraggi/discreture.svg?branch=master)](https://travis-ci.org/mraggi/discreture)

# Discreture

This is a modern C++14 library designed to facilitate combinatorial research by providing fast and easy iterators to a few combinatorial objects, such as combinations, permutations, partitions, and others. The idea is to have discreture's lazy containers interface resemble the STL containers as much as possible, by providing the standard ways of iterating over them.

In addition, many of the algorithms described in the standard <algorithm> library work as-is in these containers, as if the containers were marked as const.

This library is provided as a header-only library and has been tested on Linux. Other operating systems might work. Let me know if you find any issues!

# Quick preview:

```c++
	#include <iostream>
	#include <discreture.hpp>
	int main()
	{
		using namespace std;
		using namespace dscr; //for expository purposes.
		
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

You need to compile with the `-std=c++14` flag:
`g++ -std=c++14 -O3 main.cpp`

# Installation

Discreture is a header-only library. To use, simpley make sure your programs have access to the .hpp files (all files inside "include" dir). Just copy them to your project's include folders or tell your compiler where to look.

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

This will install everything under `/usr/local/` by default. If you wish to install to some other directory, replace the `cmake ..` above by something like `cmake .. -DCMAKE_INSTALL_PREFIX=/usr/`.

There are three options: BUILD_EXAMPLES, BUILD_TESTS and BUILD_BENCHMARKS. To use discreture you don't need to compile anything, but if you wish to, you can compile examples, tests and benchmarks by replacing the `cmake ..` part by:
	`cmake .. -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON`

# How to start using the library
To use the library, after compiling, just add `#include <discreture.hpp>` to your project and make sure you are compiling in `c++14` mode (or later). With the GCC compiler this can be done by compiling like this: `g++ -std=c++14 myfile.cpp`. You can include only part of the library, say, combinations, by adding `#include <Discreture/Combinations.hpp>` for example.

# Combinatorial Objects

Within this library, one can construct a few combinatorial objects, such as:
  - Combinations
  - Permutations
  - Partitions
  - Dyck Paths
  - Motzkin Paths
  - Set Partitions
  - Multisets
  - Number Ranges

All follow the same design principle: The templated class is called `basic_SOMETHING<class T, class Container>`, and the simplest types for `T` and `Container` are instantiated as SOMETHING. For example, `combinations` is a typedef of `basic_combinations< int, vector<int> >`, and `partitions` is a typedef of `basic_partitions<int, vector<int>>`. T is usually an (signed) integer type, like `char`, `short`, `int`, `long`. Some tests show that on different machines different types produce faster code, so even if you don't need numbers bigger than 127 it might be a good idea to use `int` or `long` rather than `char`. 

`Container` is defaulted to `vector<T>`, so you can just write `basic_combinations<short>` instead of `basic_combinations<short, vector<short>>`, but other container types with similar interfaces to vector are possible. A good example is boost's `static_vector`. See section "Getting that last drop of speed" for more.

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
	auto comb = X[10000]; //produces the 10,000-th combination.
```

This is much slower if one plans to actually iterate over all of them. 

However, iterator arithmetic is implemented, so one could even do binary search on `X` with the following code:
```c++
	#include <algorithm>
	// ...
	combinations X(30,10);
	std::partition_point(X.begin(), X.end(), predicate);
```
where `predicate` is a unary predicate that takes a `const combinations::combination&` as an argument and returns true or false, in a way that for all the first combinations it returns true and the last ones return false.

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


### Getting that last drop of speed

By default, `basic_combinations<T>::combination` (and all others) are `std::vector<T>`, which allocates memory on the heap. If you really need the utmost performance, this may be changed to any random access container with the same interface as vector. A good choice is `boost::containter::static_vector<T,K>` (or even `boost::containter::small_vector<T,K>`), where `K` is the biggest size you'll need.

Some sane defaults for `K` have been set in `combinations_fast`, `permutations_fast`, `dyck_paths_fast`, which are just typedef's of `basic_combinations<int,boost::containter::static_vector<int,K>>` and so on.

So for example, the following code iterates over all combinations of size 3 of `{0,1,...,6}` in a slightly faster way than `dscr::combinations`.
```c++
	#include <Discreture/Combinations.hpp>
	
	int main()
	{
		for (auto& x : dscr::combinations_fast(7,3))
		{
			//do stuff with x
		}
	}
```

This only works if combination size (*e.g.* 3) is less than 32. If for some reason you need combination sizes bigger than 32, just use something like this:
```c++
	#include <Discreture/Combinations.hpp>
	
	int main()
	{
		using my_fast_big_combinations = dscr::basic_combinations<int,boost::containter::static_vector<int,50>>;
		for (auto& x : my_fast_big_combinations(52,50))
		{
			//do stuff with x
		}
	}
```

Each of `permutations`, `dyck_paths`, etc. has its corresponding "fast" version: `permutations_fast`, `dyck_paths_fast`, etc. with their own custom set limits. If you are going to need monstrous objects (like permutations of size 17 or more (why?!)), just typedef as in the previous example or use regular old fashioned `permutations`.

#### combinations::for_each

For combinations in particular, there is one last possible speedup: use for_each, like in the following example.

```c++
	#include <Discreture/Combinations.hpp>
	
	void f(const dscr::combinations_fast::combination& x)
	{
		// Do stuff to x
	}
	
	int main()
	{
		dscr::combinations_fast X(34,17);
		X.for_each(f);
	}
```

This code applies `f` to every element of `X`, and it's almost twice as fast (see benchmarks) as doing manual iteration, up to size 17. More than that and `for_each` falls back on manual iteration. Of course, `f` can be a lambda or a functor too.

# Benchmarks.

## Combinations benchmarks

Two different libraries were tested: GNU Scientific Library (GSL) and euler314's library. 

The GNU Scientific Library is a well-known and mature library. For more information, [check their website](https://www.gnu.org/software/gsl/). 

Euler314's library (unnamed as far as I know) can be found [here](https://github.com/euler314/combinatorics) and provides similar functionality to discreture, although discreture provides many more features.

Iterating over all combinations of size n/2 over a set of size n took the following time:

<img src="https://github.com/mraggi/discreture/blob/master/combvsgsl.png" width="600" alt="discreture::combinations vs GSL combinations" title="discreture::combinations vs GSL combinations">


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


**Note**: GSL and euler314 iterates in the same order as `combinations_tree`. Not really sure why euler314's (yellow) is a tiny bit faster than `combinations_tree`. The code does essentially the same thing (although it was written independently).

On the other hand, euler314_maximin (in gray) was a commit that adapted some of discreture's code and iterates in the same order as `combinations`. It's essentially the same code, which is why it takes almost exactly the same amount of time. A minor improvement has been since made by discreture, which is why it's now faster.


Note 2: DoNotOptimize(x) is just a way to tell the compiler to not optimize away the empty loop. From [google benchmarking tools](https://github.com/google/benchmark). 

If you'd like to see other benchmarks, let me know.

## Discreture vs Sagemath

This comparison isn't very fair (C++ vs python). On the same system, iterating over all (24 choose 12) combinations, sage takes 12.2 seconds. Discreture takes approximately 0.005 seconds. No point in graphing that.

## Benchmarks

The following benchmarks where done on a i7-5820K CPU @ 3.30GHz, using Manjaro Linux with gcc 7.2.1. All tests were done using boost::container::static_vector (*i.e.* no heap memory).

The important columns are Speed and Speed (w/o _fast). They mean "how many (combinations/permutations/etc) were generated in one second". Tests were done with e.g. `combinations_fast` and `combinations` respectively. Times are only reported for _fast version.

|Benchmark name                  |   Time     |   # processed     |           Speed (with _fast)    | Speed (w/o _fast) |
|--------------------------------|------------:|-------------------:|:---------------------:|:--------------:|
| **Combinations** | | | | |
|Combinations for_each           |  2.558s    |    2333606220     |      9.121e+08 #/sec| 6.381e+08 #/sec|
|Combinations (No iterator)      |  4.319s    |    2333606220     |      5.403e+08 #/sec| 5.850e+08 #/sec|
|Combinations Forward            |  4.807s    |    2333606220     |      4.855e+08 #/sec| 4.296e+08 #/sec|
|Combinations Reverse            | 10.492s    |    2333606220     |      2.224e+08 #/sec| 2.348e+08 #/sec|
|Combinations Construct          |  0.009s    |         10000     |      1.106e+06 #/sec| 1.089e+06 #/sec|
| **Combinations Tree** | | | | |
|Combinations Tree for_each      |  2.981s    |    2333606220     |      7.828e+08 #/sec| 6.255e+08 #/sec|
|Combinations Tree (No iterator) |  7.723s    |    2333606220     |      3.022e+08 #/sec| 2.512e+08 #/sec|
|Combinations Tree Forward       |  6.993s    |    2333606220     |      3.337e+08 #/sec| 2.973e+08 #/sec|
|Combinations Tree Reverse       |  8.279s    |    2333606220     |      2.819e+08 #/sec| 3.128e+08 #/sec|
|Combinations Tree GSL           | 12.772s    |    2333606220     |      1.827e+08 #/sec| 1.829e+08 #/sec|
|Combinations Tree Construct     |  0.009s    |         10000     |      1.135e+06 #/sec| 1.045e+06 #/sec|
| **Permutations** | | | | |
|Permutations Forward            |  1.462s    |     479001600     |      3.277e+08 #/sec| 3.087e+08 #/sec|
|Permutations Reverse            |  3.332s    |     479001600     |      1.438e+08 #/sec| 1.438e+08 #/sec|
|Permutations Construct          |  0.003s    |         10000     |      2.946e+06 #/sec| 2.963e+06 #/sec|
| **Multisets** | | | | |
|Multisets Forward               |  0.026s    |       9331200     |      3.524e+08 #/sec| 4.189e+08 #/sec|
| **Catalan** | | | | |
|Dyck Paths Forward              |  2.049s    |     477638700     |      2.331e+08 #/sec| 2.234e+08 #/sec|
|Motzkin Paths Forward           |  1.025s    |      50852019     |      4.959e+07 #/sec| 5.068e+07 #/sec|                            
| **Partitions** | | | | |
|Partitions Forward              |  0.030s    |        966467     |      3.194e+07 #/sec| 3.464e+07 #/sec|
|Set Partitions Forward          |  0.766s    |      27644437     |      3.608e+07 #/sec| 3.780e+07 #/sec|

**Noteworthy**: for_each can be really fast if using _fast version for combinations. Standard iteration was slower with _fast version on both combinations and combinations tree reverse for some unknown reason.

# Acknowledgements
 - Manuel Alejandro Romo de Vivar (manolo) for his work on dyck paths, motzkin paths, and his contribution to partition numbers.

 - Juho Lauri for suggestions on improving "tree" combination iterator and many interesting discussions on combinations. 

 - César Benjamín García for suggesting the name "discreture".
 - You: for reading this.
 

# Contributing
Please help us testing, debugging, benchmarking, packaging for the various distros, etc. Also, if you use discreture for your own purposes, let us know!
