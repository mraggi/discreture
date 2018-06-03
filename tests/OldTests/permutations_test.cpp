#include "permutations_test.hpp"
#include "TimeHelpers.hpp"

using namespace dscr;

bool testPermutations()
{
    std::cout << "============= Testing Permutations ============" << '\n';

    std::cout << " Use test: " << '\n';
    permutations X(4);
    size_t i = 0;

    for (const auto& x : X)
    {
        std::cout << "\t" << i << " = " << X.get_index(x) << " -> " << x
                  << '\n';

        if (i != X.get_index(x))
        {
            return false;
        }

        ++i;
    }

    std::cout << " Reverse use test: " << '\n';
    Permutations<llint> Y(5);
    i = 0;

    for (auto it = Y.rbegin(); it != Y.rend(); ++it, ++i)
    {
        std::cout << "\t" << i << " -> " << *it << " == " << Y[Y.size() - i - 1]
                  << '\n';

        if (*it != Y[Y.size() - i - 1])
        {
            return false;
        }
    }

    std::cout << "Edge case test: " << '\n';
    Permutations<unsigned char> Z(0);

    for (const auto& z : Z)
    {
        std::cout << z << std::endl;
    }

    return true;
}
