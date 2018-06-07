#pragma once

#include "ArithmeticProgression.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "VectorHelpers.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace dscr
{

////////////////////////////////////////////////////////////
/// \brief class of partitions of the number n.
/// \param IntType should be an integral type with enough space to store n and
/// k. It can be signed or unsigned. # Example:
///
///	 partitions X(6);
///		for (auto& x : X)
///			cout << x << ' ';
///
/// Prints out:
///
/// 	[ 1 1 1 1 1 1 ] [ 2 1 1 1 1 ] [ 3 1 1 1 ] [ 2 2 1 1 ] [ 4 1 1 ] [ 3 2 1
/// ] [ 2 2 2 ] [ 5 1 ] [ 4 2 ] [ 3 3 ] [ 6 ]
////////////////////////////////////////////////////////////
template <class IntType = int, class RAContainerInt = std::vector<IntType>>
class Partitions
{
public:
    using value_type = RAContainerInt;
    using partition = value_type;
    using difference_type = long long;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;
    class reverse_iterator;
    using const_reverse_iterator = iterator;

    // **************** Begin static functions
    static void next_partition(partition& data, IntType n)
    {
        size_t t = data.size();

        if (t < 2)
        {
            return;
        }

        if (data.front() - data.back() < 2) // We must change size!
        {
            first_with_given_number_of_parts(data, n, t - 1);
            return;
        }

        // If no size change is necessary

        // Starting from the end, we look at the first whose difference is at
        // least 2 in order to transfer one unit from that one and then divide
        // unevenly among the other ones.
        IntType smallest = data.back();
        difference_type suffixSum = smallest;

        for (difference_type i = t - 2; i >= 0; --i)
        {
            if (data[i] - smallest > 1)
            {
                --data[i];
                distribute_unevenly(
                  data.begin() + i + 1, data.end(), suffixSum + 1, data[i]);
                return;
            }
            suffixSum += data[i];
        }
    }

    static void prev_partition(partition& data, IntType n)
    {
        size_type t = data.size();
        if (t == 0)
            return;
        if (t == 1 || data[1] == 1)
        {
            last_with_given_number_of_parts(data, n, t + 1);
            return;
        }

        difference_type suffixSum = data.back();

        for (IntType i = t - 2; i >= 0; --i)
        {

            if (can_increase(data, i))
            {
                ++data[i];
                distribute_evenly(
                  data.begin() + i + 1, data.end(), suffixSum - 1);
                return;
            }
            suffixSum += data[i];
        }
    }

    static void
    first_with_given_number_of_parts(partition& data, IntType n, IntType k)
    {
        if (n == 0)
        {
            data.clear();
            return;
        }

        data.resize(k);

        std::fill(data.begin(), data.end(), 1);

        data[0] = n - k + 1;
    }

    static void
    last_with_given_number_of_parts(partition& data, IntType n, IntType k)
    {
        if (n == 0)
        {
            data.clear();
            return;
        }
        data.resize(k);

        distribute_evenly(data.begin(), data.end(), n);
    }

    static partition conjugate(const partition& P)
    {
        assert(!P.empty());
        partition result(P[0], 1);
        auto n = P.size();

        result[0] = n;

        for (size_t i = 1; i < n; ++i)
        {
            auto t =
              std::lower_bound(P.begin(), P.end(), i, std::greater<IntType>());

            int r = t - P.begin();

            if (r > 0)
                result[i] = r;
        }

        return result;
    }

    // **************** End static functions

public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param n is an integer >= 0
    ///
    ////////////////////////////////////////////////////////////
    explicit Partitions(IntType n)
        : n_(n), min_num_parts_(1), max_num_parts_(n), size_(calc_size(n))
    {}

    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param n is an integer >= 0
    /// \param numparts is an integer >= 1 and <= n
    ///
    ////////////////////////////////////////////////////////////
    Partitions(IntType n, IntType numparts)
        : n_(n)
        , min_num_parts_(numparts)
        , max_num_parts_(numparts)
        , size_(calc_size(n, numparts))
    {}

    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param n is an integer >= 0
    /// \param minnumparts is an integer >= 1 and <= n
    /// \param maxnumparts is an integer >= minnumparts and <= n
    ///
    ////////////////////////////////////////////////////////////
    Partitions(IntType n, IntType minnumparts, IntType maxnumparts)
        : n_(n)
        , min_num_parts_(minnumparts)
        , max_num_parts_(maxnumparts)
        , size_(calc_size(n, minnumparts, maxnumparts))
    {}

    ////////////////////////////////////////////////////////////
    /// \brief The total number of partitions
    ///
    /// \return p_n
    ///
    ////////////////////////////////////////////////////////////
    size_type size() const { return size_; }

    IntType get_n() const { return n_; }

    iterator begin() const { return iterator(n_, max_num_parts_); }

    const iterator end() const
    {
        return iterator::make_invalid_with_id(size());
    }

    reverse_iterator rbegin() const
    {
        return reverse_iterator(n_, min_num_parts_);
    }

    const reverse_iterator rend() const
    {
        return reverse_iterator::make_invalid_with_id(size());
    }

    ////////////////////////////////////////////////////////////
    /// \brief Bidirectional iterator class.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator,
                                        const partition&,
                                        boost::bidirectional_traversal_tag>
    {
    public:
        iterator() : n_(0), data_() {}

        explicit iterator(IntType n, IntType numparts)
            : n_(n), data_(numparts, 1)
        {
            if (numparts > 0)
                data_[0] = n - numparts + 1;
        }

        inline size_type ID() const { return ID_; }

        // boost::iterator_facade provides all the public interface you need,
        // like ++, etc.

        static const iterator make_invalid_with_id(size_type id)
        {
            iterator it;
            it.ID_ = id;
            return it;
        }

    private:
        void increment()
        {
            ++ID_;

            next_partition(data_, n_);
        }

        void decrement()
        {
            --ID_;

            prev_partition(data_, n_);
        }

        const partition& dereference() const { return data_; }

        bool equal(const iterator& it) const { return it.ID() == ID(); }

        difference_type distance_to(const iterator& lhs) const
        {
            return static_cast<difference_type>(lhs.ID()) - ID();
        }

    private:
        size_type ID_{0};
        IntType n_;
        partition data_;

        friend class boost::iterator_core_access;
    }; // end class iterator

    ////////////////////////////////////////////////////////////
    /// \brief Bidirectional iterator class.
    ////////////////////////////////////////////////////////////
    class reverse_iterator
        : public boost::iterator_facade<reverse_iterator,
                                        const partition&,
                                        boost::bidirectional_traversal_tag>
    {
    public:
        reverse_iterator() : n_(0), data_() {}

        explicit reverse_iterator(IntType n, IntType numparts) : n_(n), data_()
        {
            last_with_given_number_of_parts(data_, n, numparts);
        }

        inline size_type ID() const { return ID_; }

        // boost::iterator_facade provides all the public interface you need,
        // like ++, etc.

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

            prev_partition(data_, n_);
        }

        void decrement()
        {
            --ID_;

            next_partition(data_, n_);
        }

        const partition& dereference() const { return data_; }

        bool equal(const reverse_iterator& it) const { return it.ID() == ID(); }

        difference_type distance_to(const reverse_iterator& lhs) const
        {
            return static_cast<difference_type>(lhs.ID()) - ID();
        }

    private:
        size_type ID_{0};
        IntType n_;
        partition data_;

        friend class boost::iterator_core_access;
    }; // end class reverse_iterator

private:
    IntType n_;
    IntType min_num_parts_;
    IntType max_num_parts_;
    size_type size_;

    static size_type calc_size(IntType n) { return partition_number(n); }

    static size_type calc_size(IntType n, IntType numparts)
    {
        return partition_number(n, numparts);
    }

    static size_type
    calc_size(IntType n, IntType minnumparts, IntType maxnumparts)
    {
        size_type toReturn = 0;
        for (size_type k = minnumparts; k <= maxnumparts; ++k)
            toReturn += partition_number(n, k);
        return toReturn;
    }

    static bool can_increase(const partition& data, size_type i)
    {
        if (i == 0)
            return true;

        if (data[i] == 1 || data[i + 1] == 1)
            return false;

        if (data[i - 1] == data[i])
            return false;

        return true;
    }

    template <class Iter>
    static void
    distribute_evenly(const Iter& first, const Iter& last, IntType n)
    {
        if (first == last)
            return;
        auto k = last - first;
        IntType lower = n/k;
        IntType residue = n - lower*k;
        auto mid = first + residue;
        std::fill(first, mid, lower + 1);
        std::fill(mid, last, lower);
    }

    template <class Iter>
    static void distribute_unevenly(Iter first,
                                    const Iter& last,
                                    IntType n,
                                    IntType maximum)
    {
        auto k = last - first;
        IntType excess = n - k;
        for (; first != last; ++first)
        {
            *first = std::min<IntType>(maximum, excess + 1);
            excess += (1 - *first);
        }
    }

}; // end class Partitions

using boost::container::static_vector;

using partitions = Partitions<int>;
using partitions_stack = Partitions<int, static_vector<int, 128>>;

} // namespace dscr
