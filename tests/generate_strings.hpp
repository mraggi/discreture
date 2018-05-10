#pragma once
#include "Probability.hpp"
#include "VectorHelpers.hpp"
#include <algorithm>
#include <string>
#include <vector>

inline std::string generate_random_string(int size)
{
    std::string ouch(size, char());
    for (auto& s : ouch)
        s = dscr::random::random_int<char>('a', 'z' + 1);
    return ouch;
}

inline std::vector<std::string> generate_random_strings(int n)
{
    std::vector<std::string> result(n);
    std::generate(result.begin(), result.end(), []() {
        size_t size = dscr::random::random_int<size_t>(0, 20);
        return generate_random_string(size);
    });

    return result;
}