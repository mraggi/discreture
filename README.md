[![Build Status](https://travis-ci.org/mraggi/discreture.svg?branch=master)](https://travis-ci.org/mraggi/discreture)
[![Coverage Status](https://coveralls.io/repos/github/mraggi/discreture/badge.svg?branch=master)](https://coveralls.io/github/mraggi/discreture?branch=master)
[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://gitlab.com/miguelraggi/discreture/raw/master/LICENSE)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/d660abad682941f1a02518c6fff77c0f)](https://www.codacy.com/app/mraggi/discreture?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=mraggi/discreture&amp;utm_campaign=Badge_Grade)




# Discreture

This is a modern C++14 library designed to facilitate combinatorial research by providing fast and easy iterators to a few combinatorial objects, such as combinations, permutations, partitions, and others. The idea is to have discreture's lazy containers interface resemble the STL containers as much as possible, by providing the standard ways of iterating over them.

In addition, many of the algorithms described in the standard <algorithm> library work as-is in these containers, as if the containers were marked as const.

This library is provided as a header-only library and has been tested on Linux. Other operating systems might work. Let me know if you find any issues!

# Quick preview:

```c++
#include <iostream>
#include <discreture.hpp>

using discreture::operator<<;

int main()
{
    for (auto&& x : discreture::combinations(5,3))
        std::cout << x << std::endl;
    
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

Discreture is a header-only library and its only dependency is boost. Programs using it need to be compiled with `c++14` or later. Tested with gcc 5.4.0 and clang 3.9.0 and up. Other compilers might work too.

To use, simply make sure your programs have access to the .hpp files (all files inside "include" dir). Just copy them to your project's include folders or tell your compiler where to look.

## Pre-requisites for compiling

Nothing needs to be compiled. But if you wish to build examples, benchmarks and tests, these are the pre-requisites.
- A C++ compiler (*i.e.* gcc or clang)
- [boost](http://www.boost.org) (header files. Specifically: iterator_facade)
- [cmake](https://cmake.org/) or [meson](https://mesonbuild.com/)
- [git](https://git-scm.com/) (only for downloading the directory. You can also download it directly from gitlab/github)
- [Google's Test Framework](https://github.com/google/googletest) (for building unit tests only).

Starting from v1.9 we also support the much faster meson build system instead of cmake, but shall continue to maintain support for cmake.

### Installing pre-requisites in Ubuntu Linux and derivatives
```sh
sudo apt-get install libboost-all-dev git build-essential cmake
```

### Installing pre-requisites in Arch Linux and derivatives
```sh
sudo pacman -S boost git gcc cmake
```


### Installing pre-requisites in mac OS
First, make sure [HomeBrew](https://brew.sh/) is installed. Then in a terminal do:

```sh
brew install gcc cmake git boost
```

## Install discreture

To do a system-wide install, do the standard cmake/make dance:
```sh
git clone --recursive https://gitlab.com/miguelraggi/discreture.git
cd discreture
mkdir build
cd build
cmake ..
make
sudo make install
```

This will install the necessary headers under `/usr/local/` by default. If you wish to install to some other directory, replace the `cmake ..` above by something like `cmake .. -DCMAKE_INSTALL_PREFIX=/usr/`.

There are three options: BUILD_EXAMPLES, BUILD_TESTS and BUILD_BENCHMARKS. **To use discreture you don't need to compile anything**, but if you wish to, you can compile examples, tests and benchmarks by replacing the `cmake ..` part by: 
```sh
cmake .. -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON
```

By default, nothing is built, as discreture is a header-only library.

### Trying the examples
After compiling the examples (with `cmake .. -DBUILD_EXAMPLES=ON`), try for example running:
```sh
./combinations 5 3
```

This will output all combinations of size 3 from the set {0,1,2,3,4}.

Or try for example
```sh
./combinations "abcde" 3
```
will output all subsets of size 3 of "abcde".

There are many other example programs there. Play with them.

# How to start using the library
To use the library, after compiling, just add `#include <discreture.hpp>` to your project and make sure you are compiling in `c++14` mode (or later). With the GCC compiler this can be done by compiling like this: `g++ -std=c++14 myfile.cpp`. You can include only part of the library, say, combinations, by adding `#include <Discreture/Combinations.hpp>` for example.

# Combinatorial Objects

Within this library, one can construct a few combinatorial objects, such as:
  - **Combinations**: Subsets of a specific size of either a given set or {0,1,...,n-1}:
    - Example: `{0,3,4}, {0,1,5}` in `combinations(6,3)`
    - Example2: `{'a','b','c'}, {'a','c','d'}` in `combinations("abcdef"s,3)`
  - **Permutations**: A permutation of a collection is a reordering of all the elements of *C*.
    - Example: `[0,1,2], [2,0,1]` in `permutations(3)`
    - Example2 : `['a','b','c'], ['c','a','b']` in `permutations("abc"s)`
  - **Partitions**: Numbers that add up to a given number.
    - Example: `{6,4,1}, {3,3,3,1,1}` in `partitions(11)`
  - **Set Partitions**: Partitions of {0,...,n-1} into disjoint sets.
    - Example: `{ {0,2}, {1,3} }` in `set_partitions(4)`
  - **Multisets**: How many to take of each index?
    - Example: `{2,1,3}, {0,1,1}` in `multisets([3,1,3])`
  - **Dyck Paths**: From (0,0) to (2n,0) but y is never negative and always goes either up or down.
    - Example: `[1,1,-1,1,-1,-1]` in `dyck_paths(3)`. Note no partial sum is less than 0.
  - **Motzkin Paths**: Like dyck paths but allowing 0's.
    - Example: `[1,0,-1,1,1,-1,0,-1]` in `motzkin_paths(9)`
  - **Integer Intervals**: A (lazy) closed-open interval of integers.
    - Example: `integer_interval(4,8)` = {4,5,6,7}
  - **Arithmetic Progression**: A (lazy) set of the form {a,a+d,a+2d,...,a+kd}.
    - Example: `{1,4,7}` in `arithmetic_progression(1,8,3)`

All follow the same design principle: The templated class is called `SomethingOrOther<...>`, with CamelCase notation, and there is either a function or a typedef for the simplest template parameters. However, most of the time you'll be using the `small_case_notation` version, which either is a typedef or a function with sensible parameters.

For example, `partitions` is a typedef of `Partitions<int, vector<int>>`, but `combinations` is a function with two versions, depending on the arguments. It returns either an object of type `Combinations<T, vector<T>>` or `IndexedViewContainer</*some template parameters*/>`, depending on which arguments are passed. Note that there is currently no support for detecting repeats, so `combinations("aabc"s,2)` has `ab` two times. If you need this functionality, let me know and I'll do my best to implement it quickly.

Some tests show that on different machines different types produce faster code, so even if you don't need numbers bigger than 127 it might be a good idea to use `int` or `long` rather than `char`. 

# Basic usage

```c++
auto X = discreture::combinations(30,10); //all subsets of size 10 of {0,1,2,...,29}
for (auto&& x : X) 
{ 
    // x is of type const vector<int>&, so anything that works with 
    // const vector references also works on x, such as indexing, iterating, etc. x[3], etc.
}
```

Reverse iterators are defined too.
```c++
discreture::Combinations<short> X(30,10);
for (auto it = X.rbegin(); it != X.rend(); ++it) 
{ 
    auto& x = *it;
}
```

But of course there is a simpler way:
```c++
auto X = permutations(10);
for (auto&& x : reversed(permutations)) 
{ 
    // do stuff to x.
}
```

Combinations, Permutations and Multisets are random-access containers so something like this works too:
```c++
auto X = discreture::combinations(30,10);
auto comb = X[10000]; //produces the 10,000-th combination.
```

**Warning:** Please note that it is *much* slower if one plans to actually iterate over all of them *à la* 
```c++
for (int i = 0; i < X.size(); ++i)
{ 
    // use X[i] 
}
```
so don't do that.

However, iterator arithmetic is implemented, so one could even do binary search on `X` with the following code:
```c++
#include <algorithm>
// ...
auto X = discreture::combinations(30,10);
std::partition_point(X.begin(), X.end(), predicate);
```
where `predicate` is a unary predicate that takes a `const combinations::combination&` as an argument and returns true or false, in a way that for all the first combinations it returns true and the last ones return false.

This is also useful to use many processors at once. See tutorial_parallel.cpp under "examples" on how to do this.

## Tutorial

Here is a quick mini-tutorial. See the examples for more on usage. Check the files under `examples` for a more complete tutorial on how to use the library. Maybe start with the file called `tutorial.cpp` and then read the others in any order.

### Combinations example
After installing, let's start by creating a file called "combinations.cpp" and adding the following content:
```c++
#include <iostream>
#include <string>
#include <discreture.hpp> // just include everything

using namespace std::string_literals;
using discreture::operator<<;

int main()
{
    for (auto&& x : discreture::combinations("abcde"s,3))
    {
        std::cout << x << std::endl;
    }
    return 0;
}
```

This prints out:
    a b c 
    a b d 
    a c d 
    b c d 
    a b e 
    a c e 
    b c e 
    a d e 
    b d e 
    c d e

### Partition example
For example, suppose you wanted to see all ways to add up to 20 with at most 6 numbers so that all numbers are squares. You can do:

```c++
#include <iostream>
#include <Discreture/Partitions.hpp>
#include <Discreture/VectorHelpers.hpp>

using discreture::operator<<;

bool is_perfect_square(int n) 
{
    if (n < 0)
        return false;
    int r = round(sqrt(n));
    return n == r*r;
}

int main()
{
    auto X = discreture::partitions(20,1,6);
    for (auto&& x : X)
    {
        if (std::all_of(x.begin(), x.end(), is_perfect_square))
            std::cout << x << std::endl;
    }
    
    return 0;
}
```

Then compile with the command `g++ -O2 -std=C++14 main.cpp -o out` and run `./out`. It should produce the following output:

    9 4 4 1 1 1
    16 1 1 1 1
    4 4 4 4 4
    9 9 1 1
    16 4

## Combinations find_if and find_all
Combinations is the most mature part of the library, and some tree-prunning (backtracking) functions to find a specific combination have been implemented:

```c++
#include <iostream>
#include <vector>
#include <discreture.hpp>

using discreture::operator<<;

int main()
{
    auto X = discreture::combinations(10,3);
    
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
    for (auto&& t : T)
        std::cout << t << std::endl;
}
```

Prints out:

    1 2 4
    1 2 6
    1 2 8
    1 3 6
    1 3 9
    2 4 8


These are all combinations for which every element is a divisor of the next element. This is *not* merely a filter: only combinations which satisfy the partial predicate (given by a lambda function) are further explored, in a branch-and-cut way.

### Getting that last drop of speed

By default, `Combinations<T>::combination` (and many others) is a typedef of `std::vector<T>`, which allocates memory on the free store. If you really need the utmost performance (although tests show meager gains at best), this may be changed to any random access container with the same interface as vector. A good choice is `boost::containter::static_vector<T,K>` (or even `boost::containter::small_vector<T,K>`), where `K` is the biggest size you'll need.

Some sane defaults for `K` have been set in `combinations_stack`, `permutations_stack`, `dyck_paths_stack`, which are just typedef's of `basic_combinations<int,boost::containter::static_vector<int,K>>` and so on.

So for example, the following code iterates over all combinations of size 3 of `{0,1,...,6}` in a slightly faster way than `discreture::combinations`.
```c++
#include <Discreture/Combinations.hpp>

int main()
{
    for (auto&& x : discreture::combinations_stack(7,3))
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
    using my_fast_big_combinations = discreture::basic_combinations<int,boost::containter::static_vector<int,50>>;
    for (auto& x : my_fast_big_combinations(52,50))
    {
        //do stuff with x
    }
}
```

Each of `permutations`, `dyck_paths`, etc. has its corresponding "stack memory" version: `permutations_stack`, `dyck_paths_stack`, etc. with their own custom set limits. If you are going to need monstrous objects (like permutations of size 17 or more (why?!)) and for some reason can't allocate a few more bytes (again: why?!), just typedef as in the previous example (or use regular old fashioned `permutations`).

#### combinations::for_each and multisets::for_each

For combinations and multisets in particular, there is one last possible speedup: use for_each, like in the following example.

```c++
#include <Discreture/Combinations.hpp>

void f(const discreture::combinations_stack::combination& x)
{
    // Do stuff to x
}

int main()
{
    discreture::combinations_stack X(34,17);
    X.for_each(f);
}
```

This code applies `f` to every element of `X`, and it's about 30% faster (see benchmarks) as doing iteration, up to size 17. More than that and `for_each` falls back on manual iteration. Of course, `f` can be a lambda or a functor too.

# Benchmarks.

## Combinations benchmarks

Two different libraries were tested: GNU Scientific Library (GSL) and euler314's library. 

The GNU Scientific Library is a well-known and mature library. For more information, [check their website](https://www.gnu.org/software/gsl/). 

Euler314's library (unnamed as far as I know) can be found [here](https://github.com/euler314/combinatorics) and provides similar functionality to discreture, although discreture provides many more features.

Iterating over all combinations of size n/2 over a set of size n took the following time (lower is better):

<img src="https://gitlab.com/miguelraggi/discreture/raw/master/combvsgsl.png" width="600" alt="discreture::combinations vs GSL combinations" title="discreture::combinations vs GSL combinations">


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
auto end = combination_iterator<int>();

for (auto it = combination_iterator<int>(n, n/2); it != end; ++it)
{
    DoNotOptimize(*it);
}
```

Compare to the following (beautiful) code, using discreture:
```c++
for (auto&& x : combinations(n,n/2))
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


**Note 1**: GSL and euler314 iterates in the same order as `lex_combinations`. Not really sure why euler314's (yellow) is a tiny bit faster than `lex_combinations`. The code does essentially the same thing (although it was written independently).

**Note 2**: `DoNotOptimize(x)` is just a way to tell the compiler to not optimize away the empty loop. Taken from [google benchmarking tools](https://github.com/google/benchmark). 

If you'd like to see other benchmarks, let me know.

## Discreture vs Sagemath

This comparison isn't very fair (C++ vs python). On the same system, iterating over all (24 choose 12) combinations, sage takes 12.2 seconds. Discreture takes approximately 0.005 seconds. No point in graphing that.

## Benchmarks

The following benchmarks were done on a i7-5820K CPU @ 3.30GHz, using Manjaro Linux with gcc 8.1.1.

The important column is speed. Higher is better. It means "how many (combinations/permutations/etc) were generated in one second" (basically, # processed / Time). Note the exponents.

<img src="https://gitlab.com/miguelraggi/discreture/raw/master/benchmarks.png" width="900" alt="discreture::benchmarks" title="discreture::benchmarks">

**Noteworthy**: for_each can be really fast if using "stack" version for combinations (*i.e.* combinations_stack). Standard iteration was slower with _stack version on both combinations and combinations tree reverse for some unknown reason.

Run your own benchmarks (with colors!) by building with `cmake -DBUILD_BENCHMARKS=ON` and running
```sh
./discreture_benchmarks
```

### Parallel benchmarks

Random access containers (currently: combinations, lex combinations, permutations and multisets) can be used easily in a multithreaded environment. Here are some benchmarks.

<img src="https://gitlab.com/miguelraggi/discreture/raw/master/benchmarks_parallel.png" width="900" alt="discreture::benchmarks_parallel" title="discreture::benchmarks_parallel">

Run your own benchmarks with 
```sh
./parallel_benchmarks
```

By default, this runs on all available CPUs. Optionally specify the number of threads like so:
```sh
./parallel_benchmarks 4
```

# Acknowledgements
 - Manuel Alejandro Romo de Vivar (manolo) for his work on dyck paths, motzkin paths, and his contribution to partition numbers.

 - Juho Lauri for suggestions on improving lexicographic combinations and many interesting discussions on combinations. 

 - César Benjamín García for suggesting the name "discreture".
 
 - Samuel Lelièvre for his help installing in macOS.
 
 - You: for reading this.

# Contributing
First: If you use discreture for your own purposes, let us know!

Optimizations, suggestions, feature requests, etc. are very welcome too.

Otherwise, you can contribute in many ways:
    
 - Provide bug reports if you encounter them, or even request some features if you'd find them helpful. We'll do our best to provide them.
 - Help us package for the various distros (maybe even other OS's).
 - If you are a developer (or aspiring developer) looking to get your feet wet, here is the current status of the project.

| Container | Forward Iteration? | Reverse Iteration? | Random Access? |
|:----------|:------------------:|:------------------:|:--------------:|
| Combinations     | ✓✓ | ✓ | ✓ |
| Permutations     | ✓  | ✓ | ✓ |
| Multisets     | ✓  | ✓ | ✓ |
| Dyck Paths     | ✓  |      |      |
| Motzkin Paths | ✓  |      |      |
| Partitions     | ✓  | ✓ |      |
| Set Partitions| ✓  |      |     |

Just let us know which algorithm you'd like to implement for something that is missing a checkmark ✓. 

Or choose another combinatorial object of your liking.

For example, two (likely) easy ones to implement would be "non-decreasing sequences" (also known as combinations with repetition) and [compositions](https://en.wikipedia.org/wiki/Composition_(combinatorics)), which are probably pretty easy to implement if you wish to get your hands wet.

We'll even help you set up all the boilerplate code. You just need to say what `next` means for your combinatorial object.

Finally, partitions, set partitions and motzkin paths are both pretty slow right now (well, relatively: only at a few tens of millions of objects generated per second, as opposed to hundreds or even thousands of millions per second, as in the case of combinations for_each). Maybe you have an idea to make them faster.
