#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

#include "Misc.hpp"

namespace discreture
{

////////////////////////////////////
/// \brief prints out a space separated std::vector.
////////////////////////////////////
template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& V)
{
    std::copy(V.begin(), V.end(), std::ostream_iterator<T>(os, " "));

    return os;
}

////////////////////////////////////
/// \brief prints out a vector of vector's as a matrix
////////////////////////////////////
template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& V)
{
    os << std::endl;
    for (auto&& v : V)
        os << v << std::endl;

    return os;
}

/////////////////////////////
/// \brief Specialization for std::vector printouts for std::vector<bool> so
/// that it doesn't print out spaces between 0's and 1's
/////////////////////////////
inline std::ostream& operator<<(std::ostream& os, const std::vector<bool>& V)
{
    for (bool v : V)
        os << v;

    return os;
}

///////////////////////////
/// \brief Function composition
///
/// \return f∘g
///////////////////////////
template <class vecT, class IntType>
vecT compose(const vecT& f, const std::vector<IntType>& g)
{
    // 		typename vecT::value_type u(0);
    vecT toReturn(g.size());

    for (size_t i = 0; i < g.size(); ++i)
    {
        assert(0 <= g[i] && g[i] < f.size());
        toReturn[i] = f[g[i]];
    }

    return toReturn;
}

} // namespace discreture
