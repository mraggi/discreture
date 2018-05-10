#include "motzkin_test.hpp"
#include "TimeHelpers.hpp"
#include "dyck_test.hpp"
using namespace dscr;

bool testMotzkin()
{
    std::cout << "============= Testing Motzkin Paths ============"
              << std::endl;
    motzkin_paths X(4);

    for (const auto& x : X)
    {
        std::cout << x << std::endl;

        if (!dyckpathiscorrect(x))
        {
            std::cerr << "This dyck path is not correct: [" << x << "]"
                      << std::endl;
            return false;
        }
    }

    for (const auto& x : X)
    {
        std::cout << motzkin_paths::to_string(x) << '\n';
    }

    return true;
}
