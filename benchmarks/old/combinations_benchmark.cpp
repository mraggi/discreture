#include "combinations_benchmark.hpp"
#include "../do_not_optimize.hpp"
#include "TimeHelpers.hpp"
#include <algorithm>
#include <numeric>

using namespace dscr;

void testCombinationsSpeed(int n, int k)
{
    binomial(100, 0); // so that it doesn't do it later.
    combinations X(n, k);

    Chronometer C;

    for (auto& x : X)
    {
        DoNotOptimize(x);
    }

    std::cout << "Time taken to see all (" << n << " choose " << k
              << ") = " << binomial(n, k) << " combinations: " << C.Reset()
              << "s" << std::endl;

    auto last = X.rend();
    for (auto it = X.rbegin(); it != last; ++it)
    {
        DoNotOptimize(*it);
    }

    std::cout << "Time taken to see all (" << n << " choose " << k
              << ") = " << X.size()
              << " combinations in reverse order: " << C.Reset() << "s"
              << std::endl;

    X.for_each([](const combinations::combination& x) { DoNotOptimize(x); });

    std::cout << "Time taken to apply a function to all (" << n << " choose "
              << k << ") = " << X.size() << " combinations: " << C.Reset()
              << "s" << std::endl;

    combinations W(100, 5);
    auto T = W.find_all([](const combinations::combination& A) {
        if (A.size() < 2)
            return true;

        int k = A.size();
        return A[k - 1] > A[k - 2] + 2;
    });

    for (auto& t : T)
    {
        DoNotOptimize(t);
    }

    std::cout << "Time taken find all combinations satisfying a predicate: "
              << C.Reset() << "s" << std::endl;
}

#ifdef TEST_GSL_COMBINATIONS
#include <gsl/gsl_combination.h>
void testGSLComb(int n, int k)
{
    gsl_combination* c;

    Chronometer C;
    // 	for (int n = 8; n < 34; n += 1)
    // 	{
    c = gsl_combination_calloc(n, k);

    do
    {
        DoNotOptimize(*c);
    } while (gsl_combination_next(c) == GSL_SUCCESS);

    gsl_combination_free(c);

    std::cout << "Time taken to see all (" << n << " choose " << k
              << ") = " << binomial(n, k)
              << " combinations with GNU Scientific Library (GSL): "
              << C.Reset() << "s" << std::endl;
    // 	}
}
#endif

void testCombinationsTreeSpeed(int n, int k)
{
    Chronometer C;
    lex_combinations X(n, k);

    for (auto& x : X)
    {
        DoNotOptimize(x);
    }

    std::cout << "Time taken to see all (" << n << " choose " << k
              << ") = " << X.size()
              << " combinations in TREE ORDER: " << C.Reset() << "s"
              << std::endl;

    auto end = X.rend();
    for (auto it = X.rbegin(); it != end; ++it)
    {
        DoNotOptimize(*it);
    }

    std::cout << "Time taken to see all (" << n << " choose " << k
              << ") = " << X.size()
              << " combinations in REVERSE TREE ORDER: " << C.Reset() << "s"
              << std::endl;

#ifdef TEST_GSL_COMBINATIONS
    testGSLComb(n, k);
#endif
}

#ifdef TEST_GSL_COMBINATIONS
void produceAllGSLData(int from, int to)
{
    std::cout << "gsl = [";
    Chronometer C;
    gsl_combination* c;

    for (int n = from; n < to; ++n)
    {
        c = gsl_combination_calloc(n, n/2);

        do
        {
            DoNotOptimize(*c);
        } while (gsl_combination_next(c) == GSL_SUCCESS);

        gsl_combination_free(c);

        std::cout << C.Reset() << ", ";
    }

    std::cout << ']' << std::endl;
}
#endif

void produceAllCombinationData(int from, int to)
{
    std::cout << "combinations = [";
    Chronometer C;

    for (int n = from; n < to; ++n)
    {
        for (const auto& x : combinations_fast(n, n/2))
        {
            DoNotOptimize(x);
        }

        std::cout << C.Reset() << ", ";
    }

    std::cout << ']' << std::endl;
}

void produceAllCombinationReverseData(int from, int to)
{
    std::cout << "combinations_reversed = [";
    Chronometer C;

    for (int n = from; n < to; ++n)
    {
        combinations_fast X(n, n/2);

        for (auto it = X.rbegin(); it != X.rend(); ++it)
        {
            DoNotOptimize(*it);
        }

        std::cout << C.Reset() << ", ";
    }

    std::cout << ']' << std::endl;
}

void produceAllLexCombinationsData(int from, int to)
{
    std::cout << "lex_combs = [";
    Chronometer C;

    for (int n = from; n < to; ++n)
    {
        for (const auto& x : lex_combinations_stack(n, n/2))
        {
            DoNotOptimize(x);
        }

        std::cout << C.Reset() << ", ";
    }

    std::cout << ']' << std::endl;
}

void produceAllLexCombinationsReverseData(int from, int to)
{
    std::cout << "lex_combinations_reversed = [";
    Chronometer C;

    for (int n = from; n < to; ++n)
    {
        lex_combinations_fast X(n, n/2);

        for (auto it = X.rbegin(); it != X.rend(); ++it)
        {
            DoNotOptimize(*it);
        }

        std::cout << C.Reset() << ", ";
    }

    std::cout << ']' << std::endl;
}

#include "../external/euler314_combination_iterator.hpp"
void produceAllEulerGuyData(int from, int to)
{
    std::cout << "euler314 = [";
    Chronometer C;

    for (int n = from; n < to; ++n)
    {
        auto end = combination_iterator<int>();

        for (auto it = combination_iterator<int>(n, n/2); it != end; ++it)
        {
            DoNotOptimize(*it);
        }

        std::cout << C.Reset() << ", ";
    }

    std::cout << ']' << std::endl;
}

void produceAllBFCombinations(int from, int to)
{
    std::cout << "combinationBF = [";
    Chronometer C;

    for (int n = from; n < to; ++n)
    {
        combinations_fast X(n, n/2);

        X.for_each(
          [](const combinations_fast::combination& x) { DoNotOptimize(x); });

        std::cout << C.Reset() << ", ";
    }

    std::cout << ']' << std::endl;
}

void produceAllCombinationBenchmarkData(int from, int to)
{
    produceAllBFCombinations(from, to);
    produceAllCombinationData(from, to);
    produceAllEulerGuyData(from, to);
    produceAllCombinationReverseData(from, to);
    produceAllLexCombinationsData(from, to);
    produceAllLexCombinationsReverseData(from, to);
    produceAllGSLData(from, to);
}
