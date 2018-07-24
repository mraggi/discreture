#include "Motzkin.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <set>

using namespace std;
using namespace discreture;

void check_motzkin_path(const motzkin_paths::motzkin_path& x)
{
    int suma = 0;

    for (auto u : x)
    {
        ASSERT_TRUE(u == 1 || u == -1 || u == 0);
        suma += u;

        ASSERT_GE(suma, 0);
    }

    ASSERT_EQ(suma, 0);
}

TEST(MotzkinPaths, ForwardIteration)
{
    for (int n = 0; n < 8; ++n)
    {
        motzkin_paths X(n);
        set<motzkin_paths::motzkin_path> S(X.begin(), X.end());
        ASSERT_EQ(X.size(),
                  S.size()); // check if all motzkin paths are different

        for (const auto& x : X)
        {
            check_motzkin_path(x);
        }
    }
}
