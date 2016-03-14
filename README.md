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

Some tests show discreture is usually faster when compiled with clang++ instead of g++.

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
Furthermore, it's recommended to compile using the clang compiler instead of gcc. One can do this by running `cmake .. -DUSE_CLANG`, or editing the CMakeLists.txt and switch the "OFF" option of USE_CLANG to "ON".

You can run the tests like by running the executable: `./testdiscreture`

# How to start using the library
To use the library, after compiling, just add `#include <discreture/discreture.hpp>` (make sure this can be done) and link to `libdiscreture.so`. With the GCC compiler or CLANG, this can be done by compiling like this: `g++ -ldiscreture myfile.cpp`

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

All follow the same design principle: The templated class is calles basic_SOMETHING<class T>, and the most reasonable type for T is instantiated as SOMETHING. For example, `combinations` is a typedef of `basic_combinations<int>`, and `partitions` is a typedef of `basic_partitions<int>`, following the standard string design: std::string is actually a typedef of std::basic_string<char>.

# Advanced use

Although the full reference is in the doxygen documentation, here is a quick preview. Remember to always `#include "discreture.hpp"` (or `#include <discreture/discreture.hpp>` etc.):

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
combinations X(30,10);
std::lower_bound(X.begin(), X.end(), predicate, combinations::compare); //TODO: FIX THIS!!!!
```
where `predicate` is a unary predicate that takes a `const vector<int>&` as an argument and returns true or false. This would effectively do binary search.
