/**
 *Welcome to discreture. This is a short tutorial on some of the functions
 *provided by discreture. Remember that discreture is a header-only library,
 *which means there is no need to install anything: You can simply copy the
 *folder "include" to your project and start using it right away.
 *
 *It's assumed you already know C++. Compile this file with "g++ -std=c++14
 *tutorial.cpp -o tutorial"
 *
 *If you get an error "fatal error: discreture.hpp: No such file or directory"
 *it means your compiler doesn't know where to find discreture. Fix it by
 *compiling with "g++ -std=c++14 -I/path/to/discreture/include tutorial.cpp -o
 *tutorial"
 *
 *For more details about installing, compiling, etc. see README.md.
 *
 *Finally, if you need help, feel free to email me at mraggi@gmail.com
 */

#include "discreture.hpp" //This includes everything in discreture.
#include <iostream>
#include <string>

int main()
{
    // Everything in discreture is in the "discreture" namespace.

    using discreture::operator<<; // just to print stuff
    using std::cout;
    using std::endl;

    // Let's iterate over combinations of 5,3 in a few different ways.
    cout << "We iterate over all subsets of size 3 of {0,1,2,3,4}" << endl;

    for (auto&& x : discreture::combinations(5, 3))
        cout << x << endl; // simply prints out to the screen the combinations.

    cout << "\nNow with letters!" << endl;

    std::string abcde = "abcde";
    for (auto x : discreture::combinations(abcde, 3))
        cout << x << endl;

    /***
     *A few important notes:
     *1. It works with any random-access container, such as std::vector
     *2. It does not check for repeats! So if you do combinations on
     *"aaaaa", it will just produce many sets with "aaa".
     *3. The std::string is necessary, because "abcde" is not a proper
     *container. It's an C-style char array.
     */

    cout << "\nNow in reverse!" << endl;

    auto X = discreture::combinations(5, 3);
    for (auto&& x : reversed(X))
        cout << x << endl;

    cout << "\nNow, we'll do it with direct access. Note this is much slower "
            "than standard iteration."
         << endl;

    for (int i : indices(X))
        cout << X[i] << endl;
    // indices just gives the container with elements
    // {0,1,2,...,Combinations.size()-1}. It works with any container that
    // provides the "size()" method.

    cout << "\nAll of discreture's containers work the same way.\n\nHere we "
            "iterate over partitions, which are all the ways of adding up to a "
            "number."
         << endl;

    for (auto&& p : discreture::partitions(6))
        cout << p << endl;

    cout << "\nOr permutations" << endl;

    for (auto&& p : discreture::permutations(3))
        cout << p << endl;

    cout << "\nOr permutations of a string" << endl;
    std::string abc = "abc";
    for (auto p : discreture::permutations(abc)) // remember: no &
        cout << p << endl;

    cout << "\nOr dyck paths" << endl;
    for (auto&& dyckpath : discreture::dyck_paths(3))
        cout << dyckpath << endl;

    cout << "\nMotzkin paths" << endl;
    for (auto&& motz : discreture::motzkin_paths(3))
        cout << motz << endl;

    cout << "\nMultisets of {2,2,1}" << endl;
    for (auto&& submulti : discreture::multisets({2, 2, 1}))
        cout << submulti << endl;

    cout << "\nSet partions" << endl;
    for (auto&& setpartition : discreture::set_partitions(4))
    {
        cout << '|';
        for (auto&& part : setpartition)
            cout << part << '|';
        cout << endl;
    }

    // setpartition if of type std::vector<std::vector<int>>,
    // thus the more complicated printing function.

    cout << "\nWe now do something more complicated: Let's find all "
            "combinations for which each element divides the next."
         << endl;

    auto divides = [](const auto& partialcomb) {
        int k = partialcomb.size();

        if (k < 2)
            return true;
        return partialcomb[k - 2] != 0 &&
          partialcomb[k - 1]%partialcomb[k - 2] == 0;
    }; // This can be any function or lambda or functor.

    discreture::Combinations<int> C(321, 8);

    for (auto&& c : C.find_all(divides))
    {
        cout << c << endl;
    }
    // find_all(predicate) constructs combinations for which
    // predicate is true for each partial combination. So, for example,
    // for combination [1 5 10 20 40 80 160 320], it has to be true for
    // [1], [1 5], [1 5 10] and so on.

    cout << "If you need more speed, use the for_each method." << endl;
    discreture::Combinations<int> U(10, 5); // for large 10 and 5
    U.for_each([](const auto& u) {
        using discreture::operator<<;
        if (u.back() == 8)
            cout << u << endl;
    });

    return 0;
}
