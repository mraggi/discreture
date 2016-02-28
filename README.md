# Discreture

This is a modern C++ 11 (and 14) library designed to facilitate combinatorial research by providing fast and easy iterators to a few combinatorial objects, such as combinations, permutations, partitions, and others. The idea is to have them resemble the STL containers as much as possible, without actually storing the whole set of objects in memory.

Discreture is designed to follow the STL containers as closely as possible, by providing the standard ways of iterating. In addition, many of the algorithm described in the standard <algorithm> work as-is in these containers, but they should be treated as const containers.

# Example use:

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

Some tests show discreture is usually faster when compiled with clang++ instead of g++.

# Installation

To download and install, run the following commands:

```sh
git clone https://github.com/mraggi/discreture.git
cd discreture
mkdir build
cd build
cmake ..
make
sudo make install #optional
```

You can run tests like this: `./testdiscreture`

# Combinatorial Objects

There are a few combinatorial objects, such as:
  - Combinations
  - Permutations
  - Subsets
  - Multisets
  - Partitions
  - Dyck Paths
  - Range
  - Motzkin Paths

These all follow the same design principle: The templated class is calles basic_SOMETHING<class T>, and the most reasonable type for T is instantiated as SOMETHING. For example, `combinations` is a typedef of `basic_combinations<int>`, and `partitions` is a typedef of `basic_partitions<int>`.
