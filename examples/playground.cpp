// This file is my personal playground. I just use it to test stuff out


#include "Combinations.hpp"

using namespace std;
using namespace dscr;

int main()
{
    auto A = combination_tree(6, 3);

    A.for_each([](auto& a) { cout << a << endl; });

    return 0;
}
