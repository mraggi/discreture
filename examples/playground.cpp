// This file is my personal playground. I just use it to test stuff out.

#include "discreture.hpp"

using namespace std; // NOLINT
using namespace discreture; // NOLINT

int main()
{
    //     auto A = Combinations<char>(5,3);
    auto A = multisets({2, 2, 5});

    A.for_each([](auto& a) { cout << a << endl; });

    cout << endl << "--------------" << endl;
    for (auto&& a : A)
        cout << a << endl;

    return 0;
}
