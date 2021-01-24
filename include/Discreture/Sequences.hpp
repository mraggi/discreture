#pragma once
#include "Misc.hpp"
#include "VectorHelpers.hpp"
#include <iostream>
#include <vector>
namespace discreture
{
using llint = long long int; // NOLINT : I want this to be as big as possible,
                             // not restricted to 64 bits. If in the future
                             // there are 128 bit ints, that's what I want.

//////////////////////////////
/// \brief n!
/// \param n is a (small) nonnegative integer.
/// \return n!
//////////////////////////////
template <class BigIntType = llint>
inline BigIntType factorial(llint n);

//////////////////////////////
/// \brief The number of subsets of size r chosen from a set of size n
/// \param n is a (small) nonnegative integer
/// \param k is a small integer between 0 and n (inclusive)
/// \return n!/(k!*(n-k)!)
//////////////////////////////
template <class BigIntType = llint>
inline BigIntType binomial(llint n, llint k);

//////////////////////////////
/// \brief The n-th catalan number.
/// \param n is a (small) nonnegative integer
/// \return binomial(2n,n)/(n+1)
//////////////////////////////
template <class BigIntType = llint>
inline BigIntType catalan(llint n);

//////////////////////////////
/// \brief The n-th motzkin number.
/// \param n is a (small) nonnegative integer
/// \return M_n
//////////////////////////////
template <class BigIntType = llint>
inline BigIntType motzkin(llint n);

//////////////////////////////
/// \brief The n-th partition number
/// \param n is a (small) nonnegative integer
/// \return P_n
//////////////////////////////
template <class BigIntType = llint>
inline BigIntType partition_number(llint n);

//////////////////////////////
/// \brief The number of partitions of n with k parts
/// \param n is a (small) nonnegative integer
/// \param k <= n is a (small) nonnegative integer
/// \return P_{n,k}
//////////////////////////////
template <class BigIntType = llint>
inline BigIntType partition_number(llint n, llint k);

//////////////////////////////
/// \brief The number of permutations of n which have exactly k cycles.
/// \param n is a (small) nonnegative integer
/// \param k <= n is a (small) nonnegative integer
/// \return The stirling number of the first kind S(n,k)
//////////////////////////////
template <class BigIntType = llint>
inline BigIntType stirling_cycle_number(llint n, llint k);

//////////////////////////////
/// \brief The number of partitions of a set of n elements with exactly k parts
/// \param n is a (small) nonnegative integer
/// \param k <= n is a (small) nonnegative integer
/// \return The stirling number of the second kind S_{n,k}
//////////////////////////////
template <class BigIntType = llint>
inline BigIntType stirling_partition_number(llint n, llint k);

//////////////////////////////
/// \brief The generalized pentagonal numbers (see oeis sequence A001318)
/// \param n is a (small) nonnegative integer
/// \return p_n
//////////////////////////////
template <class BigIntType = llint>
inline BigIntType generalized_pentagonal(llint n);

template <class BigIntType>
inline BigIntType factorial(llint n)
{
    BigIntType toReturn = 1;

    if (n < 2)
        return toReturn;

    for (llint i = 2; i <= n; ++i)
        toReturn *= i;

    return toReturn;
}

template <class BigIntType>
inline BigIntType binomial(llint n, llint k)
{
    if (k > n || k < 0)
        return 0;

    if (k > n - k)
        k = n - k;

    if (k == 0)
        return 1;
    if (k == 1)
        return n;

    static std::vector<std::vector<BigIntType>> B =
      {{1}, {1}, {1, 2}, {1, 3}, {1, 4, 6}, {1, 5, 10}, {1, 6, 15, 20}};
    llint m = B.size();

    if (n < m)
        return B[n][k];

    const llint max_saved_size = 66; // this is the maximum n for which
                                     // binomial(n,k) < 2^63 for any k.
    if (n > max_saved_size)
    {
        std::vector<llint> denominator(k - 1);
        std::iota(denominator.begin(), denominator.end(), 2);
        std::vector<llint> numerator(k);
        std::iota(numerator.begin(), numerator.end(), n - k + 1);
        return reduce_fraction<BigIntType>(std::move(numerator),
                                           std::move(denominator));
    }

    B.resize(n + 1, {1});

    for (; m <= n; ++m)
    {
        llint last = (m + 2)/2 - 1;
        B[m].resize(last + 1);

        for (llint r = 1; r < last; ++r)
        {
            B[m][r] = B[m - 1][r - 1] + B[m - 1][r];
        }

        if (m%2 == 0)
            B[m][last] = 2*B[m - 1][last - 1];
        else
            B[m][last] = B[m - 1][last] + B[m - 1][last - 1];
    }

    return B[n][k];
}

template <class BigIntType>
BigIntType catalan(llint n)
{
    static const std::vector<llint> C = {1,
                                         1,
                                         2,
                                         5,
                                         14,
                                         42,
                                         132,
                                         429,
                                         1430,
                                         4862,
                                         16796,
                                         58786,
                                         208012,
                                         742900,
                                         2674440,
                                         9694845,
                                         35357670,
                                         129644790,
                                         477638700,
                                         1767263190,
                                         6564120420,
                                         24466267020,
                                         91482563640,
                                         343059613650,
                                         1289904147324,
                                         4861946401452};

    llint Csize = C.size();

    if (n < Csize)
        return C[n];

    return binomial(2*n, n)/(n + 1);
}

template <class BigIntType>
inline BigIntType motzkin(llint n)
{
    static std::vector<BigIntType> M = {1, 1, 2, 4, 9, 21, 51, 127, 323};
    // 	static std::vector<BigIntType> M = {1, 1, 2, 4, 9, 21, 51, 127, 323,
    // 835, 2188, 5798, 15511, 41835, 113634, 310572, 853467, 2356779, 6536382,
    // 18199284, 50852019, 142547559, 400763223, 1129760415, 3192727797,
    // 9043402501, 25669818476, 73007772802, 208023278209, 593742784829};

    llint Msize = M.size();

    if (n < Msize)
        return M[n];

    llint oldsize = M.size();
    M.resize(n + 1);
    for (llint m = oldsize; m <= n; ++m)
    {
        // quite likely overflow if using llint
        M[m] = ((2*m + 1)*M[m - 1] + (3*m - 3)*M[m - 2])/(m + 2);
    }

    return M[n];
}

template <class BigIntType>
inline BigIntType generalized_pentagonal(llint n)
{
    llint sign = (n%2)*2 - 1;
    n = sign*(n + 1)/2;
    return (n*(3*n - 1))/2;
}

template <class BigIntType>
inline BigIntType partition_number(llint n)
{
    static std::vector<llint> P = {1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101};

    llint oldsize = P.size();

    if (n < oldsize)
        return P[n];

    P.resize(n + 1, 0);
    for (llint m = oldsize; m <= n; ++m)
    {
        llint sign = 1;
        llint count = 0;
        for (llint k = 1; generalized_pentagonal(k) <= m; ++k)
        {
            P[m] += P[m - generalized_pentagonal(k)]*sign;
            ++count;
            if (count == 2)
            {
                sign *= -1;
                count = 0;
            }
        }
    }

    return P[n];
}

template <class BigIntType>
inline BigIntType partition_number(llint n, llint k)
{
    static std::vector<std::vector<llint>> PNK = {{1},
                                                  {0, 1},
                                                  {0, 1, 1},
                                                  {0, 1, 1, 1},
                                                  {0, 1, 2, 1, 1},
                                                  {0, 1, 2, 2, 1, 1}};

    llint oldsize = PNK.size();

    if (k <= 0 || n <= 0)
        return n == 0 && k == 0;

    if (k > n)
        return 0;

    if (k == n || k == 1)
        return 1;

    if (n < oldsize)
        return PNK[n][k];

    for (llint m = oldsize; m <= n; ++m)
    {
        PNK.emplace_back(m + 1, 0);
        for (llint l = 1; l <= m; ++l)
        {
            llint left = 0;
            if (m - l >= l)
                left = PNK[m - l][l];

            PNK[m][l] = left + PNK[m - 1][l - 1];
        }
    }

    return PNK[n][k];
}

template <class BigIntType>
inline BigIntType stirling_cycle_number(llint n, llint k)
{
    static std::vector<std::vector<llint>> S1 = {{1},
                                                 {0, 1},
                                                 {0, 1, 1},
                                                 {0, 2, 3, 1},
                                                 {0, 6, 11, 6, 1}};

    if (k > n || k < 0)
        return 0;

    llint oldsize = S1.size();
    if (n < oldsize)
        return S1[n][k];

    for (llint m = oldsize; m <= n; ++m)
    {
        S1.emplace_back(m + 1, 0);
        for (llint l = 1; l <= m; ++l)
        {
            llint left = 0;
            if (l < m)
                left = (m - 1)*S1[m - 1][l];
            S1[m][l] = left + S1[m - 1][l - 1];
        }
    }

    return S1[n][k];
}

template <class BigIntType>
inline BigIntType stirling_partition_number(llint n, llint k)
{
    static std::vector<std::vector<llint>> S2 = {{1},
                                                 {0, 1},
                                                 {0, 1, 1},
                                                 {0, 1, 3, 1},
                                                 {0, 1, 7, 6, 1}};

    llint oldsize = S2.size();
    if (n < oldsize)
        return S2[n][k];

    for (llint m = oldsize; m <= n; ++m)
    {
        S2.emplace_back(m + 1, 0);
        for (llint l = 1; l <= m; ++l)
        {
            llint left = 0;
            if (l < m)
                left = l*S2[m - 1][l];
            S2[m][l] = left + S2[m - 1][l - 1];
        }
    }

    return S2[n][k];
}

} // namespace discreture
