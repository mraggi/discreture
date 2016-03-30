# Discreture

This is a modern C++ 11 (and 14) library designed to facilitate combinatorial research by providing fast and easy iterators to a few combinatorial objects, such as combinations, permutations, partitions, and others. The idea is to have them resemble the STL containers as much as possible, without actually storing the whole set of objects in memory.

Discreture is designed to follow the STL containers as closely as possible, by providing the standard ways of iterating. In addition, many of the algorithms described in the standard <algorithm> library work as-is in these containers, as if the containers were constant.

# Quick preview:

```c++
    #include <iostream>
    #include "discreture.hpp"
    using namespace std;
    using namespace dscr;
    int main()
    {
        combinations X(5,3);
        for (const auto& x : X)
            cout << x << endl;
        return 0;
    }
```
The above code would produce the following output:

    [ 0 1 2 ]
    [ 0 1 3 ]
    [ 0 2 3 ]
    [ 1 2 3 ]
    [ 0 1 4 ]
    [ 0 2 4 ]
    [ 1 2 4 ]
    [ 0 3 4 ]
    [ 1 3 4 ]
    [ 2 3 4 ]

Of course, you need to link with the discreture library:
g++ -O3 -ldiscreture main.cpp

Some tests show discreture is usually faster when compiled with clang++ instead of g++. Full benchmarks at the end of the readme.

# Installation

To download and install on linux, run the following commands:

```sh
git checkout https://github.com/mraggi/discreture.git
cd discreture
sh install_linux.sh
```

This will compile the library and copy the necessary files to /usr/lib and /usr/include. It will ask for your root password. If you just wish to compile and then link manually, do the following:
```sh
git checkout https://github.com/mraggi/discreture.git
cd discreture
mkdir build
cd build
cmake ..
make
```
Furthermore, it is recommended to compile using the clang compiler instead of gcc. One can do this by running `cmake .. -D 
USE_CLANG=1`, or editing the CMakeLists.txt and switch the "OFF" option of USE_CLANG to "ON".

You can run the tests by running the executable: `./testdiscreture`

# How to start using the library
To use the library, after compiling, just add `#include <discreture/discreture.hpp>` to your project and link to `libdiscreture.so`. With the GCC compiler or CLANG, this can be done by compiling like this: `g++ -ldiscreture myfile.cpp`

# Combinatorial Objects

Within this library, one can construct a few combinatorial objects, such as:
  - Combinations
  - Permutations
  - Subsets
  - Multisets
  - Partitions
  - Dyck Paths
  - Motzkin Paths
  - Range
  - Set Partitions

All follow the same design principle: The templated class is calles basic_SOMETHING<class T>, and the most reasonable type for T is instantiated as SOMETHING. For example, `combinations` is a typedef of `basic_combinations<int>`, and `partitions` is a typedef of `basic_partitions<int>`.

# Advanced use

Although the full reference is in the doxygen documentation, here is a quick preview. Remember to always `#include "discreture.hpp"` (or `#include <discreture/discreture.hpp>` and use `using namespace dscr;` or add `dscr::` to everything.):

```c++
combinations X(30,10);
for (const auto& x : X) 
{ 
	// x is of type const vector<int>&, so anything that works with vectors works on x
}
```

You can iterate in reverse too, in the same way you would reverse-iterate an STL container.
```c++
combinations X(30,10);
for (auto it = X.rbegin(); it != X.rend(); ++it) 
{ 
	const auto& x = *it;
	// x is of type const vector<int>&, so anything that works with vectors works on x
}
```

Combinations, subsets and permutations are a random-access container (although they are slower as such than forward or reverse iteration), so something like this works too:
```c++
combinations X(30,10);
for (size_t i = 0; i < X.size(); ++i)
{
	auto x = X[i];
}
```

This is much slower if one plans to actually iterate over all of them, but iterator arithmetic is implemented, so one could even do the following:
```c++
#include <algorithm>
// ...
combinations X(30,10);
std::partition_point(X.begin(), X.end(), predicate);
```
where `predicate` is a unary predicate that takes a `const vector<int>&` as an argument and returns true or false, in a way that for all the first combinations it returns true and the last ones return false. This would do binary search.

# Benchmarks.

On a i7-5820K CPU @ 3.30GHz, on Linux, compiling with -Ofast yields the following results:

| Task | Time taken CLANG 3.7.0 | Time taken GCC 5.2.0 |
| ------------- |:-------------:| :-------------:|
| Time taken to see all (32 choose 16) = 601080390 combinations 					|	 **2.29281s**		|   3.36332s   |
| Time taken to see all (32 choose 16) = 601080390 combinations in reverse order 	|	 **1.67853s**		|   3.98176s   |
| Time taken to see all 12! = 479001600 permutations								|	   1.70865s  		| **1.33693s** |
| Time taken to see all 2^29 = 536870912 subsets 									|	   2.54663s  		| **2.14877s** |
| Time taken to see all 2^29 = 536870912 subsets (fast mode) 						|	   2.10764s  		| **1.84649s** |
| Time taken to see all 56634173 partitions of size 90 								|	 **1.41834s**		|   1.48321s   |
| Time taken to see all 559872000 multisets 										|	 **1.84566s**		|   1.90435s   |
| Time taken to see all 477638700 dyck paths of size 18 							|	 **2.16288s**		|   2.74891s   |
| Time taken to see all 50852019 motzkin paths of size 20 							|	 **1.30359s**		|   1.46971s   |
| Time taken to see all 27644437 set partitions of size 13 							|	   0.960195s  		| **0.79946s** |
| Time taken to see all 42355950 set partitions a set of 15 elements with 4 parts 	|	   1.20166s  		| **1.01687s** |
| **Total Time**																	|	 **19.7s**			|	22.1s	   |

# Acknowledgements
I would like to thank Manuel Alejandro Romo de Vivar (manolo) for his work on dyck paths, motzkin paths, and his contribution to partition numbers.
