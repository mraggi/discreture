#pragma once

#include "ArithmeticProgression.hpp"
#include "Misc.hpp"
#include "Reversed.hpp"
#include "Sequences.hpp"
#include "VectorHelpers.hpp"
#include "detail/PartitionsDetail.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace discreture
{

////////////////////////////////////////////////////////////
/// \brief class of partitions of the number n.
/// \param IntType should be an integral type with enough space to store n and
/// k. It can be signed or unsigned. # Example:
///
///	 partitions X(6);
///		for (auto&& x : X)
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
    static_assert(std::is_integral<IntType>::value,
                  "Template parameter IntType must be integral");
    static_assert(std::is_signed<IntType>::value,
                  "Template parameter IntType must be signed");
    using value_type = RAContainerInt;
    using partition = value_type;
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;
    class reverse_iterator;
    using const_reverse_iterator = reverse_iterator;

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

    template <class Func>
    void for_each(Func f) const
    {
        for (auto k : reversed(II(min_num_parts_, max_num_parts_ + 1)))
        {
            for_each(f, k);
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief Bidirectional iterator class.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator, const partition&, boost::bidirectional_traversal_tag>
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
                distribute_unevenly(data.begin() + i + 1,
                                    data.end(),
                                    suffixSum + 1,
                                    data[i]);
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
                distribute_evenly(data.begin() + i + 1, data.end(), suffixSum - 1);
                return;
            }
            suffixSum += data[i];
        }
    }

    static void first_with_given_number_of_parts(partition& data,
                                                 IntType n,
                                                 IntType k)
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

    static void last_with_given_number_of_parts(partition& data,
                                                IntType n,
                                                IntType k)
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

    static size_type calc_size(IntType n, IntType minnumparts, IntType maxnumparts)
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
    static void distribute_evenly(const Iter& first, const Iter& last, IntType n)
    {
        if (first == last)
            return;
        IntType k = last - first;

        auto quot_rem = std::div(n, k);

        //         IntType lower = n/k;
        //         IntType residue = n - lower*k;

        auto mid = first + quot_rem.rem;
        std::fill(first, mid, quot_rem.quot + 1);
        std::fill(mid, last, quot_rem.quot);
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

    template <class Func>
    void for_each(Func f, IntType k) const
    {
        // I'm really sorry about this. I don't know how to improve it. If you
        // do, by all means, tell me about it.
        switch (k)
        {
            // clang-format off
        using part = partition;
        case 0: detail::for_each_partition<part, 0>::apply(n_, f); break;
        case 1: detail::for_each_partition<part, 1>::apply(n_, f); break;
        case 2: detail::for_each_partition<part, 2>::apply(n_, f); break;
        case 3: detail::for_each_partition<part, 3>::apply(n_, f); break;
        case 4: detail::for_each_partition<part, 4>::apply(n_, f); break;
        case 5: detail::for_each_partition<part, 5>::apply(n_, f); break;
        case 6: detail::for_each_partition<part, 6>::apply(n_, f); break;
        case 7: detail::for_each_partition<part, 7>::apply(n_, f); break;
        case 8: detail::for_each_partition<part, 8>::apply(n_, f); break;
        case 9: detail::for_each_partition<part, 9>::apply(n_, f); break;
        case 10: detail::for_each_partition<part, 10>::apply(n_, f); break;
        case 11: detail::for_each_partition<part, 11>::apply(n_, f); break;
        case 12: detail::for_each_partition<part, 12>::apply(n_, f); break;
        case 13: detail::for_each_partition<part, 13>::apply(n_, f); break;
        case 14: detail::for_each_partition<part, 14>::apply(n_, f); break;
        case 15: detail::for_each_partition<part, 15>::apply(n_, f); break;
        case 16: detail::for_each_partition<part, 16>::apply(n_, f); break;
        case 17: detail::for_each_partition<part, 17>::apply(n_, f); break;
        case 18: detail::for_each_partition<part, 18>::apply(n_, f); break;
        case 19: detail::for_each_partition<part, 19>::apply(n_, f); break;
        case 20: detail::for_each_partition<part, 20>::apply(n_, f); break;
        case 21: detail::for_each_partition<part, 21>::apply(n_, f); break;
        case 22: detail::for_each_partition<part, 22>::apply(n_, f); break;

            // clang-format on

        default:
        {
            for (auto&& x : Partitions<IntType, RAContainerInt>(n_, k))
            {
                f(x);
            }

            break;
        }
        } // end switch(k)
    }

}; // end class Partitions

using boost::container::static_vector;

using partitions = Partitions<int>;
using partitions_stack = Partitions<int, static_vector<int, 128>>;

} // namespace discreture
