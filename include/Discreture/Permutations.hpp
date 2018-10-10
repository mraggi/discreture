#pragma once
#include "ArithmeticProgression.hpp"
#include "IndexedViewContainer.hpp"
#include "Misc.hpp"
#include "Probability.hpp"
#include "Sequences.hpp"
#include "VectorHelpers.hpp"

#include <algorithm>
#include <numeric>
#include <type_traits>
namespace discreture
{
////////////////////////////////////////////////////////////
/// \brief class of all n! permutation of size n of the set {0,1,...,n-1}.
/// \param IntType should be an integral type with enough space to store n and
/// k. It can be signed or unsigned. \param n should be an integer < 20, since
/// 20! already exceeds the numeric limits of a 64-bit int # Example 1:
///
///		permutations X(3);
///		for (auto&& x : X)
///			cout << "[" << x << "] ";
///
///		Prints out:
///			[ 0 1 2 ] [ 0 2 1 ] [ 1 0 2 ] [ 1 2 0 ] [ 2 0 1 ] [ 2 1 0 ]
///
///	# Example 2:
///
///		string A = "abc";
///
///		for (auto&& x : permutations(A))
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
template <class IntType = int, class RAContainerInt = std::vector<IntType>>
class Permutations
{
public:
    static_assert(std::is_integral<IntType>::value,
                  "Template parameter IntType must be integral");
    static_assert(std::is_signed<IntType>::value,
                  "Template parameter IntType must be signed");
    using value_type = RAContainerInt;
    using permutation = value_type;
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;
    class reverse_iterator;
    using const_reverse_iterator = reverse_iterator;

public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param n is an integer >= 0
    ///
    ////////////////////////////////////////////////////////////
    explicit Permutations(IntType n) : n_(n) {}

    ////////////////////////////////////////////////////////////
    /// \brief The total number of permutations
    ///
    /// \return n!
    ///
    ////////////////////////////////////////////////////////////
    size_type size() const { return factorial(n_); }

    iterator begin() const { return iterator(n_); }

    const iterator end() const
    {
        return iterator::make_invalid_with_id(size());
    }

    reverse_iterator rbegin() const { return reverse_iterator(n_); }

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
        permutation perm(n_);
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
        permutation I(n_);
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
    /// permutation comb, as if Permutations was a proper data structure
    /// \note This constructs the proper index from scratch. If an iterator is
    /// already known, calling ID() on the iterator is much more efficient.
    /////////////////////////////////////////////////////////////////////////////
    static size_type get_index(const permutation& perm, size_type start = 0)
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
    /// \brief Get an iterator whose current value is p
    ///
    /// \param p the wanted permutation
    /// \return An iterator currently "pointing" at p.
    ////////////////////////////////////////////////////////////
    iterator get_iterator(const permutation& p) const { return iterator(p); }

    ////////////////////////////////////////////////////////////
    /// \brief Random access iterator class. It's much more efficient as a
    /// bidirectional iterator than purely random access.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator, const permutation&, boost::random_access_traversal_tag>
    {
    public:
        explicit iterator(IntType n = 0) : ID_(0), last_(n - 1), data_(n)
        {
            std::iota(data_.begin(), data_.end(), 0);
        }

        explicit iterator(const permutation& p)
            : ID_(get_index(p)), last_(p.size() - 1), data_(p)
        {}

        inline bool is_at_end() const { return ID_ == factorial(last_ + 1); }

        void reset(IntType r)
        {
            ID_ = 0;
            last_ = r - 1;
            data_.resize(r);
            std::iota(data_.begin(), data_.end(), 0);
        }

        inline size_type ID() const { return ID_; }

        static const iterator make_invalid_with_id(size_type id)
        {
            iterator it;
            it.ID_ = id;
            return it;
        }

    private:
        void increment()
        {
            if (ID_ > 1 && ID_%2 == 0)
            {
                std::swap(data_[last_], data_[last_ - 1]);
            }
            else
            {
                std::next_permutation(data_.begin(), data_.end());
            }
            ++ID_;
        }

        void decrement()
        {
            if (ID_ == 0)
                return;

            --ID_;
            std::prev_permutation(data_.begin(), data_.end());
        }

        const permutation& dereference() const { return data_; }

        ////////////////////////////////////////
        ///
        /// \brief Random access capabilities to the iterators
        /// \param n -> This assumes 0 <= n+ID <= size(n,k)
        ///
        ////////////////////////////////////////
        void advance(difference_type n)
        {
            assert(0 <= n + ID_);

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
            ID_ += n;
            construct_permutation(data_, ID_);
        }

        difference_type distance_to(const iterator& other) const
        {
            return static_cast<difference_type>(other.ID()) - ID();
        }

        bool equal(const iterator& other) const { return ID_ == other.ID_; }

    private:
        size_type ID_{0};
        size_type last_{0};
        permutation data_{};

        friend class boost::iterator_core_access;
    }; // end class iterator

    class reverse_iterator
        : public boost::iterator_facade<reverse_iterator,
                                        const permutation&,
                                        boost::random_access_traversal_tag>
    {
    public:
        reverse_iterator() : data_() {} // empty initializer
        explicit reverse_iterator(IntType n) : ID_(0), data_(n)
        {
            std::iota(data_.begin(), data_.end(), 0);
            std::reverse(data_.begin(), data_.end());
        }

        inline size_type ID() const { return ID_; }

        void reset(IntType n)
        {
            ID_ = 0;
            data_ = IntegerInterval<IntType>(n);
            std::reverse(data_.begin(), data_.end());
        }

        static const reverse_iterator make_invalid_with_id(size_type id)
        {
            reverse_iterator it;
            it.ID_ = id;
            return it;
        }

    private:
        void increment()
        {
            ++ID_;

            std::prev_permutation(data_.begin(), data_.end());
        }

        void decrement()
        {
            if (ID_ == 0)
                return;

            --ID_;

            std::next_permutation(data_.begin(), data_.end());
        }

        const permutation& dereference() const { return data_; }

        ////////////////////////////////////////
        ///
        /// \brief Random access capabilities to the iterators
        /// \param n -> This assumes 0 <= n+ID <= size(n,k)
        ///
        ////////////////////////////////////////
        void advance(difference_type m)
        {
            assert(0 <= m + ID_);

            if (std::abs(m) < 10) // found experimentally
            {
                while (m > 0)
                {
                    increment();
                    --m;
                }

                while (m < 0)
                {
                    decrement();
                    ++m;
                }
                return;
            }

            // If n is large, then it's better to just construct it from
            // scratch.
            ID_ += m;
            construct_permutation(data_, factorial(data_.size()) - ID_ - 1);
        }

        bool equal(const reverse_iterator& it) const { return it.ID() == ID(); }

        difference_type distance_to(const reverse_iterator& other) const
        {
            return static_cast<difference_type>(other.ID()) - ID();
        }

    private:
        size_type ID_{0};
        permutation data_;

        friend class boost::iterator_core_access;
    }; // end class iterator

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

                    m -= u*f;

                    auto temp = data[start];
                    data[start] = data[u + start];
                    data[u + start] = temp;

                    std::sort(data.begin() + start + 1, data.end());
                    break;
                }
            }
        }
    }

private:
    IntType n_;

    size_type get_index(const permutation& perm, int first, int last)
    {
        if (last <= first)
            return 0;

        RAContainerInt A(perm.begin() + first, perm.begin() + last);
        std::sort(A.begin(), A.end());

        auto n = last - first;

        // 			size_type result = 0;
        difference_type firstdiffer = 0;

        for (; firstdiffer + 1 < n; ++firstdiffer)
        {
            if (perm[firstdiffer + first] != A[firstdiffer])
                break;
        }

        return factorial(n - firstdiffer - 1) +
          get_index(perm, firstdiffer + 1, last);
    }

}; // end class Permutations

using boost::container::static_vector;

// using permutations = Permutations<int>;
using permutations_stack = Permutations<int, static_vector<int, 16>>;

template <class Container, typename = EnableIfNotIntegral<Container>>
auto permutations(const Container& X)
{
    using index_permutations = Permutations<int>;
    return indexed_view_container(X, index_permutations(X.size()));
}

template <typename T, typename = EnableIfIntegral<T>>
auto permutations(T X)
{
    return Permutations<T>(X);
}

} // namespace discreture
