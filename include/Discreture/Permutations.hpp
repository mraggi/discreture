#pragma once
#include "ArithmeticProgression.hpp"
#include "CompoundContainer.hpp"
#include "Misc.hpp"
#include "Probability.hpp"
#include "Sequences.hpp"
#include "VectorHelpers.hpp"

#include <algorithm>
#include <numeric>

namespace dscr
{
////////////////////////////////////////////////////////////
/// \brief class of all n! permutation of size n of the set {0,1,...,n-1}.
/// \param IntType should be an integral type with enough space to store n and
/// k. It can be signed or unsigned. \param n should be an integer < 20, since
/// 20! already exceeds the numeric limits of a 64-bit int # Example 1:
///
///		permutations X(3);
///		for (auto& x : X)
///			cout << "[" << x << "] ";
///
///		Prints out:
///			[ 0 1 2 ] [ 0 2 1 ] [ 1 0 2 ] [ 1 2 0 ] [ 2 0 1 ] [ 2 1 0 ]
///
///	# Example 2:
///
///		string A = "abc";
///
///		for (const auto& x : compound_permutations(A))
///		{
///			cout << b << endl;
///		}
///
///	Prints out:
///		a b c
///		a c b
///		b a c
///		b c a
///		c a b
///		c b a
///
////////////////////////////////////////////////////////////
template <class IntType, class RAContainerInt = std::vector<IntType>>
class basic_permutations
{
public:
    using value_type = RAContainerInt;
    using permutation = value_type;
    using difference_type = long long; // NOLINT
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;
    class reverse_iterator;
    using const_reverse_iterator = reverse_iterator;

public:
    // Static functions
    static void construct_permutation(permutation& data, size_type m)
    {
        size_type n = data.size();
        std::iota(data.begin(), data.end(), 0);
        size_type start = 0;

        for (; m > 0 && start < n; ++start)
        {
            // 					cout << "starting with start = " << start <<
            // endl;
            auto f = factorial(n - start - 1);

            // 					int u = 0;
            if (f > m)
            {
                continue;
            }

            for (size_type u = 1; u < n + 1; ++u)
            {
                if (u*f > m)
                {
                    --u;
                    // 							cout << "m = " << m << endl;
                    // 							cout << "u = " << u << endl;
                    // 							cout << "start = " << start <<
                    // endl;
                    m -= u*f;
                    // Ahora, en m_data[start] debo poner el u-ésimo de los que
                    // sobran
                    auto temp = data[start];
                    data[start] = data[u + start];
                    data[u + start] = temp;
                    // 							cout << "and setting m_data[" << start <<
                    // "]
                    // =
                    // "
                    // << m_data[start] << endl;
                    std::sort(data.begin() + start + 1, data.end());
                    break;
                }
            }
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param n is an integer >= 0
    ///
    ////////////////////////////////////////////////////////////
    explicit basic_permutations(IntType n) : m_n(n) {}

    ////////////////////////////////////////////////////////////
    /// \brief The total number of permutations
    ///
    /// \return n!
    ///
    ////////////////////////////////////////////////////////////
    size_type size() const { return factorial(m_n); }

    iterator begin() const { return iterator(m_n); }

    const iterator end() const
    {
        return iterator::make_invalid_with_id(size());
    }

    reverse_iterator rbegin() const { return reverse_iterator(m_n); }

    const reverse_iterator rend() const
    {
        return reverse_iterator::make_invalid_with_id(size());
    }

    ////////////////////////////////////////////////////////////
    /// \brief Access to the m-th permutation (slow for iteration)
    ///
    /// This is equivalent to calling *(begin()+m)
    /// \param m should be an integer between 0 and size(). Undefined behavior
    /// otherwise. \return The m-th permutation, as defined in the order of
    /// iteration (lexicographic)
    ////////////////////////////////////////////////////////////
    permutation operator[](size_type m) const
    {
        assert(m >= 0 && m < size());
        permutation perm(m_n);
        construct_permutation(perm, m);
        return perm;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Returns the identity permutation: [1, 2, 3, ... , (n-1)]
    ///
    /// \param n is an integer >= 0
    ///
    ////////////////////////////////////////////////////////////
    permutation identity() const
    {
        permutation I(m_n);
        std::iota(I.begin(), I.end(), 0);
        return I;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Constructs a random permutation of {0,1,2,...,n-1}
    ////////////////////////////////////////////////////////////
    permutation random() const
    {
        permutation a = identity();

        std::shuffle(a.begin(), a.end(), random::random_engine());

        return a;
    }

    /////////////////////////////////////////////////////////////////////////////
    /// \brief Returns the ID of the iterator whose value is perm. That is, the
    /// index of permutation perm in the lexicographic order.
    ///
    /// Inverse of operator[]. If permutation x is the m-th permutation, then
    /// get_index(x) is m. If one has a permutations::iterator, then the member
    /// function ID() should return the same value. \return the index of
    /// permutation comb, as if basic_permutations was a proper data structure
    /// \note This constructs the proper index from scratch. If an iterator is
    /// already known, calling ID() on the iterator is much more efficient.
    /////////////////////////////////////////////////////////////////////////////
    size_type get_index(const permutation& perm, size_type start = 0) const
    {
        size_type n = perm.size();

        if (n < 2)
            return 0;

        RAContainerInt sortedperm(perm.begin() + start, perm.end());
        std::sort(sortedperm.begin(), sortedperm.end());
        size_type i = 0;

        while (start < n)
        {
            if (perm[start] != sortedperm[i])
            {
                break;
            }

            ++start;
            ++i;
        }

        if (start == n)
            return 0;

        size_type b = n - start - 1;
        auto w =
          std::lower_bound(sortedperm.begin(), sortedperm.end(), perm[start]) -
          sortedperm.begin() - i;

        return factorial(b)*(w) + get_index(perm, start + 1);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Random access iterator class. It's much more efficient as a
    /// bidirectional iterator than purely random access.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator,
                                        const permutation&,
                                        boost::random_access_traversal_tag>
    {
    public:
        explicit iterator(IntType n = 0) : m_ID(0), m_last(n - 1), m_data(n)
        {
            std::iota(m_data.begin(), m_data.end(), 0);
        }

        inline bool is_at_end() const { return m_ID == factorial(m_last + 1); }

        void reset(IntType r)
        {
            m_ID = 0;
            m_last = r - 1;
            m_data.resize(r);
            std::iota(m_data.begin(), m_data.end(), 0);
        }

        inline size_type ID() const { return m_ID; }

        static const iterator make_invalid_with_id(size_type id)
        {
            iterator it;
            it.m_ID = id;
            return it;
        }

    private:
        void increment()
        {
            if (m_ID > 1 && m_ID%2 == 0)
            {
                std::swap(m_data[m_last], m_data[m_last - 1]);
            }
            else
            {
                std::next_permutation(m_data.begin(), m_data.end());
            }
            ++m_ID;
        }

        void decrement()
        {
            if (m_ID == 0)
                return;

            --m_ID;
            std::prev_permutation(m_data.begin(), m_data.end());
        }

        const permutation& dereference() const { return m_data; }

        ////////////////////////////////////////
        ///
        /// \brief Random access capabilities to the iterators
        /// \param n -> This assumes 0 <= n+ID <= size(n,k)
        ///
        ////////////////////////////////////////
        void advance(difference_type n)
        {
            assert(0 <= n + m_ID);

            if (std::abs(n) < 20)
            {
                while (n > 0)
                {
                    increment();
                    --n;
                }

                while (n < 0)
                {
                    decrement();
                    ++n;
                }

                return;
            }

            // If n is large, then it's better to just construct it from
            // scratch.
            m_ID += n;
            construct_permutation(m_data, m_ID);
        }

        difference_type distance_to(const iterator& other) const
        {
            return static_cast<difference_type>(other.ID()) - ID();
        }

        bool equal(const iterator& other) const { return m_ID == other.m_ID; }

    private:
        size_type m_ID{0};
        size_type m_last{0};
        permutation m_data{};

        friend class boost::iterator_core_access;
    }; // end class iterator

    class reverse_iterator
        : public boost::iterator_facade<reverse_iterator,
                                        const permutation&,
                                        boost::random_access_traversal_tag>
    {
    public:
        reverse_iterator() : m_data() {} // empty initializer
        explicit reverse_iterator(IntType n) : m_ID(0), m_data(n)
        {
            std::iota(m_data.begin(), m_data.end(), 0);
            std::reverse(m_data.begin(), m_data.end());
        }

        inline size_type ID() const { return m_ID; }

        void reset(IntType n)
        {
            m_ID = 0;
            m_data = basic_integer_interval<IntType>(n);
            std::reverse(m_data.begin(), m_data.end());
        }

        static const reverse_iterator make_invalid_with_id(size_type id)
        {
            reverse_iterator it;
            it.m_ID = id;
            return it;
        }

    private:
        void increment()
        {
            ++m_ID;

            std::prev_permutation(m_data.begin(), m_data.end());
        }

        void decrement()
        {
            if (m_ID == 0)
                return;

            --m_ID;

            std::next_permutation(m_data.begin(), m_data.end());
        }

        const permutation& dereference() const { return m_data; }

        ////////////////////////////////////////
        ///
        /// \brief Random access capabilities to the iterators
        /// \param n -> This assumes 0 <= n+ID <= size(n,k)
        ///
        ////////////////////////////////////////
        void advance(difference_type m)
        {
            assert(0 <= m + m_ID);

            if (std::abs(m) < 10) // found experimentally
            {
                while (m > 0)
                {
                    increment();
                    --m;
                }

                while (m < 0)
                {
                    increment();
                    ++m;
                }
                return;
            }

            // If n is large, then it's better to just construct it from
            // scratch.
            m_ID += m;
            construct_permutation(m_data, factorial(m_data.size()) - m_ID - 1);
        }

        bool equal(const reverse_iterator& it) const { return it.ID() == ID(); }

        difference_type distance_to(const reverse_iterator& other) const
        {
            return static_cast<difference_type>(other.ID()) - ID();
        }

    private:
        size_type m_ID{0};
        permutation m_data;

        friend class boost::iterator_core_access;
    }; // end class iterator

private:
    IntType m_n;

    size_type get_index(const permutation& perm, int first, int last)
    {
        if (last <= first)
            return 0;

        RAContainerInt A(perm.begin() + first, perm.begin() + last);
        std::sort(A.begin(), A.end());

        int n = last - first;

        // 			size_type result = 0;
        int firstdiffer = 0;

        for (; firstdiffer + 1 < n; ++firstdiffer)
        {
            if (perm[firstdiffer + first] != A[firstdiffer])
                break;
        }

        return factorial(n - firstdiffer - 1) +
          get_index(perm, firstdiffer + 1, last);
    }

}; // end class basic_permutations
using permutations = basic_permutations<int>;
using permutations_fast =
  basic_permutations<int, boost::container::static_vector<int, 16>>;

template <class Container>
auto compound_permutations(const Container& X)
{
    return compound_container<Container, permutations>(X,
                                                       permutations(X.size()));
}

} // namespace dscr
