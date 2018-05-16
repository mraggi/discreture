#include "combinations_test.hpp"
#include <algorithm>
#include <numeric>
//#include <gsl/gsl_combination.h> // uncomment to test GSL combinations
#include "TimeHelpers.hpp"

using namespace dscr;

bool testCombinations()
{
    std::cout << "============= Testing Combinations ============" << std::endl;

    std::cout << "Basic test: " << std::endl;
    int n = 6;

    for (int r = 0; r <= n; ++r)
    {
        std::cout << " with r = " << r << std::endl;
        combinations X(n, r);
        size_t i = 0;

        for (const auto& x : X)
        {
            std::cout << "\t" << i << " == " << X.get_index(x) << " -> [" << x
                      << "]" << std::endl;

            if (i != X.get_index(x))
            {
                std::cerr << "i != X.get_index(x) for x = " << x
                          << " and i = " << i << std::endl;
                return false;
            }

            if (x != X[i])
            {
                std::cerr << "x != X[i] for " << x << " and i = " << i
                          << std::endl;
                return false;
            }

            ++i;
        }

        // combined test
        if (X.size() > 5)
        {
            int w = 5;
            auto it = X.begin() + 5;

            do
            {
                if (X.get_index(*it) != w)
                {
                    std::cerr << "*it = " << *it << " and w = " << w
                              << std::endl;
                    return false;
                }
                ++it;
                ++w;
            } while (it != X.end());
        }
    }

    std::cout << "Large test" << std::endl;
    combinations X(10, 4);
    size_t i = 0;

    for (const auto& x : X)
    {
        // 		std::cout << "\t" << i << " == " << X.get_index(x) << " -> " <<
        // x
        // << std::endl;

        if (i != X.get_index(x))
        {
            return false;
        }

        ++i;
    }

    // for_each tests
    std::cout << "Testing combinations::for_each" << std::endl;

    combinations FEH(6, 3);
    auto it = FEH.begin();
    bool all_okay = true;
    FEH.for_each([&it, &all_okay](const combinations::combination& x) {
        std::cout << x << std::endl;
        if (*it != x)
            all_okay = false;
        ++it;
    });

    if (!all_okay)
        return false;

    for (int k = 0; k <= 16; ++k)
    {
        int n = k + 2;
        long num = 0;

        combinations X(n, k);

        auto f = [&num](const combinations::combination& x) { ++num; };

        X.for_each(f);
        std::cout << "binomial(" << n << "," << k << ") == " << num
                  << std::endl;
        if (num != binomial(n, k))
            return false;
    }

    // iterator operator tests
    std::cout << " Iterator operator tests" << std::endl;
    auto myIter = X.begin();
    std::cout << *(myIter + 23) << " == ";
    myIter += 46;
    std::cout << *(myIter - 23) << std::endl;
    int d = 76;
    std::cout << d << " == " << (myIter + d) - myIter << std::endl;

    // Checking correct order
    std::cout << " Correct order test: " << std::endl;

    for (auto it = X.begin(); it != X.end(); ++it)
    {
        auto itnext = it + 1;

        if (itnext == X.end())
            break;

        if (!X.compare(*it, *itnext))
            return false;
    }

    std::cout << "Reverse use test: " << std::endl;

    for (int r = 0; r <= n; ++r)
    {
        std::cout << "Starting with r = " << r << std::endl;
        basic_combinations<llint> Y(n, r);
        i = 0;

        for (auto it = Y.rbegin(); it != Y.rend(); ++it, ++i)
        {
            std::cout << "\t" << i << " -> " << *it
                      << " == " << Y[Y.size() - i - 1] << std::endl;

            if (*it != Y[Y.size() - i - 1])
                return false;
        }
    }

    std::cout << " Edge case test: " << std::endl;
    basic_combinations<char> Z(5, 8);

    for (const auto& z : Z)
    {
        std::cout << z << std::endl;
        return false;
    }

    std::cout << " find_if test: " << std::endl;
    combinations W(20, 6);

    auto predicate1 = [](const combinations::combination& comb) -> bool {
        for (size_t i = 0; i < comb.size() - 1; ++i)
        {
            if (2*comb[i] + 1 > comb[i + 1])
                return false;
        }

        return true;
    };
    auto predicate2 = [](const combinations::combination& comb) -> bool {
        for (size_t i = 0; i < comb.size() - 1; ++i)
        {
            if (comb[i] + 3 < comb[i + 1])
                return false;

            if (comb[i] + 1 == comb[i + 1])
                return false;
        }

        return true;
    };

    auto iter = W.find_if(predicate1);

    if (iter != W.end())
    {
        std::cout << "Found this one: " << *iter << std::endl;

        if (!predicate1(*iter))
        {
            std::cout << "But it does NOT satisfy the predicate!" << std::endl;
            return false;
        }
    }
    else
    {

        std::cout << "No combination satisfies the condition" << std::endl;

        // verify that indeed no combination satisfies the predicate
        if (W.get_n() < 30)
        {
            for (const auto& w : W)
            {
                if (predicate1(w))
                    return false;
            }

            std::cout << " and it checks out!!\n" << std::endl;
        }
        else
        {
            std::cout
              << "\tbut this W is too large to actually check one by one.\n"
              << std::endl;
        }
    }

    // 	return true;

    auto T = W.find_all(predicate2);

    size_t numpred2 = 0;
    for (auto& t : T)
        ++numpred2;

    size_t numpred = 0;

    if (W.get_n() < 30)
    {
        for (const auto& w : W)
        {
            if (predicate2(w))
            {
                ++numpred;
            }
        }
        if (numpred2 != numpred)
            return false;
    }
    else
    {
        std::cout << "\tbut this W is too large to actually check one by one."
                  << std::endl;
    }

    return true;
}

std::vector<int> differences(const std::vector<int>& x)
{
    std::vector<int> toReturn;
    toReturn.push_back(x[0]);

    for (size_t i = 0; i + 1 < x.size(); ++i)
        toReturn.push_back(x[i + 1] - x[i] - 1);

    return toReturn;
}

bool testCombinationsTree()
{
    std::cout << "========== Testing Combination TREE ==========" << std::endl;

    std::cout << " Use test: " << std::endl;
    int n = 6;

    for (int r = 0; r <= n; ++r)
    {
        std::cout << " with r = " << r << std::endl;
        combinations_tree X(n, r);
        size_t i = 0;

        for (const auto& x : X)
        {
            std::cout << "\t" << i << " == " << X.get_index(x) << " -> " << x
                      << std::endl;

            if (i != X.get_index(x))
                return false;

            if (x != X[i])
                return false;

            ++i;
        }
    }

    std::cout << "Large test" << std::endl;
    combinations_tree X(10, 4);
    size_t i = 0;

    for (const auto& x : X)
    {
        std::cout << "\t" << i << " == " << X.get_index(x) << " -> " << x
                  << std::endl;

        if (i != X.get_index(x))
            return false;

        ++i;
    }

    // iterator operator tests
    std::cout << " Iterator operator tests" << std::endl;
    auto myIter = X.begin();
    std::cout << *(myIter + 23) << " == ";
    myIter += 46;
    std::cout << *(myIter - 23) << std::endl;
    int d = 76;
    std::cout << d << " == " << (myIter + d) - myIter << std::endl;

    // Checking correct order
    std::cout << " Correct order test: " << std::endl;

    for (auto it = X.begin(); it != X.end(); ++it)
    {
        auto itnext = it + 1;

        if (itnext == X.end())
            break;

        if (!X.compare(*it, *itnext))
            return false;
    }

    std::cout << "Reverse use test: " << std::endl;

    for (int r = 0; r <= n; ++r)
    {
        std::cout << "Starting with r = " << r << std::endl;
        basic_combinations_tree<llint> Y(n, r);
        i = 0;

        for (auto it = Y.rbegin(); it != Y.rend(); ++it, ++i)
        {
            std::cout << "\t" << i << " -> " << *it
                      << " == " << Y[Y.size() - i - 1] << std::endl;

            if (*it != Y[Y.size() - i - 1])
                return false;
        }
    }

    std::cout << " Edge case test: " << std::endl;
    basic_combinations_tree<unsigned char> Z(5, 8);

    for (const auto& z : Z)
    {
        std::cout << z << std::endl;
        return false;
    }

    combinations W(30, 3);
    auto T = W.find_all([](const combinations::combination& A) {
        if (A.size() < 2)
            return true;

        int k = A.size();

        if (A[k - 2] == 0)
            return false;

        return A[k - 1]%A[k - 2] == 0;
    });
    std::cout << "Testing findall: " << std::endl;

    for (auto& t : T)
        std::cout << "t = " << t << std::endl;

    // 	auto T2 = W.find_all_old([](const std::vector<int>& A)
    // 	{
    // 		if (A.size() < 2)
    // 			return true;
    // 		int k = A.size();
    // 		if (A[k-2] == 0) return false;
    // 		return A[k-1]%A[k-2] == 0;
    // 	});
    // 	std::cout << "Testing findall: " << std::endl;
    // 	for (auto& t : T2)
    // 		std::cout << "t2 = " << t << std::endl;

    return true;
}
