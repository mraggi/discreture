#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace discreture
{
namespace deprecated
{

    //////////////////////////////////////////
    /// \brief Helper function to linearize tables
    //////////////////////////////////////////
    inline size_t twoD_to_oneD(unsigned x,
                               unsigned y,
                               unsigned width,
                               unsigned height)
    {
        x %= width;
        y %= height;
        return (y*width + x);
    }

    //////////////////////////////////////////
    /// \brief Clamps x to be in the interval [a,b]
    //////////////////////////////////////////
    template <class T>
    inline T Clamped(T x, T a, T b)
    {
        if (a > b)
        {
            std::swap(a, b);
        }

        if (x < a)
            x = a;

        if (x > b)
            x = b;

        return x;
    }

    //////////////
    /// \brief Equivalent to x/|x| when x != 0, and 0 when x = 0
    /// \return 1 if val is positive, -1 if it's negative, and 0 if it's 0
    //////////////
    template <typename T>
    inline int signof(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    //////////////////////////////////////////
    /// \brief This function of x is just the linear function from [a,b] to
    /// [u,v] (extended to all reals, of course). \return f(x), where
    /// f:[a,b]->[u,v] is the only linear, monotone, biyective function.
    //////////////////////////////////////////
    inline double linear_interpolate(
      double x, double a, double b, double u, double v)
    {
        return (v - u)*(x - a)/(b - a) + u;
    }

    using std::vector;
    using std::size_t;

    template <class T>
    T gcd(T a, T b)
    {
        while (b != 0)
        {
            T r = a%b;
            a = b;
            b = r;
        }
        return a;
    }

    template <class T>
    T lcm(T a, T b)
    {
        return a*b/gcd(a, b);
    }

    template <class T>
    T gcd(const std::vector<T>& A)
    {
        auto a = A.front();

        for (size_t i = 1; i < A.size(); ++i)
        {
            a = gcd(a, A[i]);
        }

        return a;
    }

    template <class T>
    T lcm(const std::vector<T>& A)
    {
        auto a = A.front();

        for (size_t i = 1; i < A.size(); ++i)
        {
            a = lcm(a, A[i]);
        }

        return a;
    }

    template <class IntType>
    long InterpretBaseK(long k, const std::vector<IntType>& bla)
    {
        long suma = 0;
        long power = 1;

        for (auto it = bla.rbegin(); it != bla.rend(); ++it)
        {
            suma += power*static_cast<IntType>(*it);
            power *= k;
        }

        return suma;
    }

    inline std::vector<unsigned char> NumberBaseB(unsigned n, unsigned char b)
    {
        std::vector<unsigned char> toReturn;

        while (n)
        {
            toReturn.push_back(n%b);
            n /= b;
        }

        std::reverse(toReturn.begin(), toReturn.end());
        return toReturn;
    }

    struct prime_to_power
    {
        prime_to_power(long prime, long power) : p(prime), a(power) {}
        long p;
        long a;
    };

    struct Factorization
    {
        operator long() const
        {
            long t = 1;
            for (auto& pa : m_prime_factors)
                t *= discreture::pow(pa.p, pa.a);
            return t;
        }

        long& operator[](long p)
        {
            auto it = std::partition_point(m_prime_factors.begin(),
                                           m_prime_factors.end(),
                                           [p](const prime_to_power& p_a) {
                                               return p_a.p < p;
                                           });

            if (it == m_prime_factors.end())
            {
                m_prime_factors.emplace_back(p, 0);
                return m_prime_factors.back().a;
            }

            if (it->p != p)
            {
                ++it;
                it = m_prime_factors.insert(it, prime_to_power(p, 0));
                return it->a;
            }

            return it->a;
        }

        long operator[](long p) const
        {
            auto it = std::partition_point(m_prime_factors.begin(),
                                           m_prime_factors.end(),
                                           [p](const prime_to_power& p_a) {
                                               return p_a.p < p;
                                           });
            if (it == m_prime_factors.end() || it->p != p)
                return 0;
            return it->a;
        }

        void emplace_back(long p, long a)
        {
            assert(m_prime_factors.empty() || p > m_prime_factors.back().p);
            m_prime_factors.emplace_back(p, a);
        }

        auto begin() const { return m_prime_factors.begin(); }

        auto end() const { return m_prime_factors.end(); }

        long size() const { return m_prime_factors.size(); }

    private:
        vector<prime_to_power> m_prime_factors;
    };

    inline std::ostream& operator<<(std::ostream& os, const Factorization& F)
    {
        long i = 0;
        for (auto f : F)
        {
            os << f.p;
            if (f.a != 1)
                os << "^" << f.a;

            if (i + 1 != F.size())
                os << "*";

            ++i;
        }
        return os;
    }

    inline long int_sqrt(long n)
    {
        double dsqrt = sqrt(double(n));

        return long(dsqrt + 0.0000000001);
    }

    inline bool is_square(long N)
    {
        long t = int_sqrt(N);
        return t*t == N;
    }

    inline long FermatFactor(long N)
    {
        assert(N%2 == 1);
        long a = ceil(sqrt(double(N)));
        long b2 = a*a - N;
        while (!is_square(b2))
        {
            ++a;
            b2 = a*a - N;
        }

        return a - int_sqrt(b2);
    }

    inline long PollardRhoFactor(long n)
    {
        long x_fixed = 2, cycle_size = 2, x = 2, factor = 1;

        while (factor == 1)
        {
            for (long count = 1; count <= cycle_size && factor <= 1; ++count)
            {
                x = (x*x + 1)%n;
                factor = gcd(x - x_fixed, n);
            }

            cycle_size *= 2;
            x_fixed = x;
        }
        if (factor < 0)
            factor *= -1;
        return factor;
    }

    class PrimeFactorizer
    {
    public:
        explicit PrimeFactorizer(long n = 5000) { euler_sieve(n); }

        bool is_prime(long p) const
        {
            if (p <= primes.back())
            {
                return std::binary_search(primes.begin(), primes.end(), p);
            }

            // Maybe comment this out? should test this!!
            if (p <= primes.back()*primes.back())
            {
                return bf_is_prime(p);
            }

            long a = FermatFactor(p);
            return a == 1;
        }

        /// Make sure sqrt(n) < primes.back()*primes.back(), otherwise this
        /// could spit out a wrong factorization.
        Factorization prime_factorization(long n)
        {
            // 		assert(n <= primes.back()*primes.back());
            Factorization F;
            if (n <= 1)
                return F;
            for (auto p : primes)
            {
                long a = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++a;
                }
                if (a != 0)
                    F.emplace_back(p, a);

                if (p*p > n)
                    break;
            }

            // 		assert(n < primes.back()*primes.back());

            // 		if (n > primes.back()*primes.back())
            // 		{
            // 			fermat_factorization(n,F);
            // 			cout << "Error: need more primes" << endl;
            // 			return F;
            // 		}

            if (n > 1)
                ++F[n];

            return F;
        }

    private:
        void euler_sieve(long n)
        {
            std::vector<bool> primecharfunc;
            primecharfunc.resize(n + 1, true);
            primes.reserve((1.1*n)/log(n) + 50);
            for (long p = 3; p*p <= n; p += 2)
            {
                if (primecharfunc[p] == true)
                {
                    for (long i = p*2; i <= n; i += p)
                        primecharfunc[i] = false;
                }
            }

            for (long p = 11; p < n; p += 2)
                if (primecharfunc[p])
                    primes.emplace_back(p);
        }

        // private because n has to be odd, and maybe is already a factor in
        // something, so yeah.
        void fermat_factorization(long n, Factorization& F)
        {
            assert(n%2 == 1);
            assert(n > 5);
            long a = FermatFactor(n);

            long b = n/a;

            assert(a*b == n);
            if (a == 1)
            {
                ++F[b];
            }
            else
            {
                fermat_factorization(a, F);
                fermat_factorization(b, F);
            }
        }

        void pollard_factorization(long n, Factorization& F)
        {
            long a = PollardRhoFactor(n);

            long b = n/a;
            if (a > b)
                std::swap(a, b);

            std::cout << n << " = " << a << "*" << b << std::endl;
            assert(a*b == n);
            if (a == 1)
            {
                ++F[b];
            }
            else
            {
                pollard_factorization(a, F);
                pollard_factorization(b, F);
            }
        }

    public:
        std::vector<long> primes = {2, 3, 5, 7};

        bool bf_is_prime(long n) const
        {
            for (auto p : primes)
            {
                if (p*p > n)
                    break;
                if (n%p == 0)
                    return false;
            }
            return true;
        }
    };

    //////////////////////////////////////
    /// \brief Bitwise and for std::vector<bool>
    //////////////////////////////////////
    std::vector<bool> operator&(const std::vector<bool>& A,
                                const std::vector<bool>& B);

    //////////////////////////////////////
    /// \brief Bitwise or for std::vector<bool>
    //////////////////////////////////////
    std::vector<bool> operator|(const std::vector<bool>& A,
                                const std::vector<bool>& B);

    template <class T>
    bool AreTheyAllDifferent(const std::vector<T>& G)
    {
        std::vector<T> copyG = G;
        std::sort(copyG.begin(), copyG.end());

        for (size_t i = 0; i < copyG.size() - 1; ++i)
        {
            if (G[i] == G[i + 1])
            {
                return false;
            }
        }

        return true;
    }

    inline std::vector<bool> operator&(const std::vector<bool>& A,
                                       const std::vector<bool>& B)
    {
        size_t size = std::min(A.size(), B.size());
        std::vector<bool> G;

        for (size_t i = 0; i < size; i++)
            G.push_back(A[i] && B[i]);

        return G;
    }

    inline std::vector<bool> operator|(const std::vector<bool>& A,
                                       const std::vector<bool>& B)
    {
        size_t size = std::min(A.size(), B.size());
        std::vector<bool> G;

        for (size_t i = 0; i < size; i++)
            G.push_back(A[i] || B[i]);

        return G;
    }

    ///////////////////////////
    /// \brief Given a subset S, written in combination form (1,2,4), returns
    /// the same subset written in subset form (01101)
    ///////////////////////////
    template <class T>
    std::vector<bool> CombinationToSubset(const std::vector<T>& C, size_t size)
    {
        std::vector<bool> toReturn(size, 0);

        for (size_t i = 0; i < C.size(); ++i)
        {
            assert(C[i] < size);
            toReturn[C[i]] = 1;
        }

        return toReturn;
    }

    ////////////////////////////////////
    /// \brief Find the minimum value of a std::vector.
    ////////////////////////////////////
    template <class T>
    T min(const std::vector<T>& v)
    {
        assert(v.size() > 0);
        T m = v[0];

        for (size_t i = 1; i < v.size(); ++i)
        {
            if (v[i] < m)
                m = v[i];
        }

        return m;
    }

    ////////////////////////////////////
    /// \brief Find the max value of a std::vector.
    ////////////////////////////////////
    template <class T>
    T max(const std::vector<T>& v)
    {
        assert(v.size() > 0);
        T m = v[0];

        for (size_t i = 1; i < v.size(); ++i)
        {
            if (v[i] > m)
                m = v[i];
        }

        return m;
    }

    ////////////////////////////////////
    /// \brief Find the minimum index of a std::vector.
    ////////////////////////////////////
    template <class T>
    size_t argmin(const std::vector<T>& v)
    {
        assert(v.size() > 0);
        T m = v[0];
        size_t bestisofar = 0;

        for (size_t i = 0; i < v.size(); ++i)
        {
            if (v[i] < m)
            {
                m = v[i];
                bestisofar = i;
            }
        }

        return bestisofar;
    }

    ////////////////////////////////////
    /// \brief Find the maximum index of a std::vector.
    ////////////////////////////////////
    template <class T>
    size_t argmax(const std::vector<T>& v)
    {
        assert(v.size() > 0);
        T m = v[0];
        size_t bestisofar = 0;

        for (size_t i = 0; i < v.size(); ++i)
        {
            if (m < v[i])
            {
                m = v[i];
                bestisofar = i;
            }
        }

        return bestisofar;
    }

    ////////////////////////////////////
    /// \brief std::vector coordinate-wise addition.
    ////////////////////////////////////
    template <class T>
    inline std::vector<T> operator+(const std::vector<T>& U,
                                    const std::vector<T>& V)
    {
        assert(U.size() == V.size());
        auto toReturn = U;

        for (size_t i = 0; i < U.size(); ++i)
        {
            toReturn[i] += V[i];
        }

        return toReturn;
    }

    ////////////////////////////////////
    /// \brief inplace std::vector coordinate-wise addition.
    ////////////////////////////////////
    template <class T>
    inline void operator+=(std::vector<T>& U, const std::vector<T>& V)
    {
        assert(U.size() == V.size());

        for (size_t i = 0; i < U.size(); ++i)
        {
            U[i] += V[i];
        }
    }

    ////////////////////////////////////
    /// \brief inplace std::vector coordinate-wise division by a number.
    ////////////////////////////////////
    template <class T, class NumType>
    inline void operator/=(std::vector<T>& U, NumType t)
    {
        // assert(U.size() == V.size());
        for (size_t i = 0; i < U.size(); ++i)
        {
            U[i] /= t;
        }
    }

    ////////////////////////////////////
    /// \brief inplace std::vector coordinate-wise multiplication by a number.
    ////////////////////////////////////
    template <class T, class NumType>
    inline void operator*=(std::vector<T>& U, NumType t)
    {
        // assert(U.size() == V.size());
        for (size_t i = 0; i < U.size(); ++i)
        {
            U[i] *= t;
        }
    }

    ////////////////////////////////////
    /// \brief coordinate-wise multiplication by a number.
    ////////////////////////////////////
    template <class T, class NumType>
    inline std::vector<T> operator*(std::vector<T> U, NumType t)
    {
        // assert(U.size() == V.size());
        U *= t;
        return U;
    }

    ////////////////////////////////////
    /// \brief coordinate-wise division by a number.
    ////////////////////////////////////
    template <class T, class NumType>
    inline std::vector<T> operator/(std::vector<T> U, NumType t)
    {
        // assert(U.size() == V.size());
        U /= t;
        return U;
    }

    //////////////////////////
    /// \brief returns a std::vector W such that for each coordinate i, W[i] =
    /// min(V[i],U[i])
    //////////////////////////
    template <class T>
    inline std::vector<T> mincac(const std::vector<T>& U,
                                 const std::vector<T>& V)
    {
        assert(U.size() == V.size());
        std::vector<T> toReturn(U.size());

        for (size_t i = 0; i < U.size(); ++i)
        {
            toReturn[i] = std::min(U[i], V[i]);
        }

        return toReturn;
    }

    //////////////////////////
    /// \brief returns a std::vector W such that for each coordinate i, W[i] =
    /// max(V[i],U[i])
    //////////////////////////
    template <class T>
    inline std::vector<T> maxcac(const std::vector<T>& U,
                                 const std::vector<T>& V)
    {
        assert(U.size() == V.size());
        std::vector<T> toReturn(U.size());

        for (size_t i = 0; i < U.size(); ++i)
        {
            toReturn[i] = std::max(U[i], V[i]);
        }

        return toReturn;
    }

} // namespace deprecated
} // namespace discreture
