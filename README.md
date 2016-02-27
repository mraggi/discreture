# Discreture

This is a modern C++ 11 (and 14) library designed to facilitate combinatorial research.

Example use:

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
