#pragma once

#include <numeric>

#include "ArithmeticProgression.hpp"
#include "Misc.hpp"
#include "Partitions.hpp"
#include "Sequences.hpp"
#include "VectorHelpers.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace discreture
{

////////////////////////////////////////////////////////////
/// \brief class of set_partitions of the number n.
/// \param IntType should be an integral type with enough space to store n and
/// k. It can be signed or unsigned. # Example:
///
///	 set_partitions X(3);
///		for (auto&& x : X)
///			cout << x << endl;
///
/// Prints out all set partitions of {0,1,2}:
///
/// 	[ [ 0 ] [ 1 ] [ 2 ] ]
///		[ [ 0 1 ] [ 2 ] ]
///		[ [ 0 2 ] [ 1 ] ]
///		[ [ 1 2 ] [ 0 ] ]
///		[ [ 0 1 2 ] ]
///
///
///	# Example 2:
///	One can specify the number of parts:
///
///		set_partitions X(4,2);
///		for (auto&& x : X)
///			cout << x << endl;
///
/// Prints out all set partitions of {0,1,2,3,4} with exactly 2 parts:
///
///		[ [ 0 1 2 ] [ 3 ] ]
///		[ [ 0 1 3 ] [ 2 ] ]
///		[ [ 0 2 3 ] [ 1 ] ]
///		[ [ 1 2 3 ] [ 0 ] ]
///		[ [ 0 1 ] [ 2 3 ] ]
///		[ [ 0 2 ] [ 1 3 ] ]
///		[ [ 0 3 ] [ 1 2 ] ]
///
///
////////////////////////////////////////////////////////////
template <class IntType = int>
class SetPartitions
{
public:
    static_assert(std::is_integral<IntType>::value,
                  "Template parameter IntType must be integral");
    static_assert(std::is_signed<IntType>::value,
                  "Template parameter IntType must be signed");
    using number_partition = std::vector<IntType>;
    using value_type = std::vector<number_partition>;
    using set_partition = value_type;
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;

    // **************** Begin static functions

    static bool next_set_partition(set_partition& data,
                                   const number_partition& part)
    {
        auto n = std::accumulate(part.begin(), part.end(), 0L);
        return next_set_partition(data, part, n);
    }

    static bool next_set_partition(set_partition& data,
                                   const number_partition& part,
                                   difference_type n)
    {
        difference_type anteriorpos = pop(data, n - 1);
        difference_type curr = n - 2;
        difference_type currpos = 0;

        while (true)
        {
            currpos = pop(data, curr);

            if (shouldBreak(data, part, currpos, anteriorpos))
                break;

            anteriorpos = currpos;
            --curr;

            if (curr == -1)
                break;
        }

        if (curr == -1)
            return false;

        auto newpos = NextAcceptablePlaceToAdd(data, part, currpos);

        data[newpos].push_back(curr);

        for (difference_type i = curr + 1; i < n; ++i)
        {
            data[NextAcceptablePlaceToAdd(data, part)].push_back(i);
        }

        return true;
    }

    static void fill_first_set_partition(set_partition& data,
                                         const number_partition& part)
    {
        IntType numpart = 0;
        IntType etiqueta = 0;
        data.resize(part.size());

        for (auto x : part)
        {
            data[numpart].resize(x);

            for (IntType i = 0; i < x; ++i, ++etiqueta)
            {
                data[numpart][i] = etiqueta;
                // 					cout << etiqueta << endl;
            }

            ++numpart;
        }
    }

    // **************** End static functions

public:
    explicit SetPartitions(IntType n)
        : n_(n), min_num_parts_(1), max_num_parts_(n), size_(calc_size(n, 1, n))
    {}

    SetPartitions(IntType n, IntType numparts)
        : n_(n)
        , min_num_parts_(numparts)
        , max_num_parts_(numparts)
        , size_(calc_size(n, numparts, numparts))
    {}

    SetPartitions(IntType n, IntType minnumparts, IntType maxnumparts)
        : n_(n)
        , min_num_parts_(minnumparts)
        , max_num_parts_(maxnumparts)
        , size_(calc_size(n, minnumparts, maxnumparts))
    {}

    size_type size() const { return size_; }

    IntType get_n() const { return n_; }

    iterator begin() const { return iterator(n_, max_num_parts_); }

    const iterator end() const
    {
        return iterator::make_invalid_with_id(size());
    }

    class iterator
        : public boost::iterator_facade<iterator, const set_partition&, boost::forward_traversal_tag>
    {
    public:
        iterator() : ID_(0), data_(), n_(0) {}

        explicit iterator(IntType n, IntType numparts)
            : ID_(0), data_(n), n_(n), num_partition()
        {
            Partitions<IntType>::first_with_given_number_of_parts(num_partition,
                                                                  n,
                                                                  numparts);
            fill_first_set_partition(data_, num_partition);
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
            ++ID_;

            if (!next_set_partition(data_, num_partition))
            {
                Partitions<IntType>::next_partition(num_partition, n_);
                fill_first_set_partition(data_, num_partition);
            }
        }

        const set_partition& dereference() const { return data_; }

        bool equal(const iterator& it) const { return it.ID() == ID(); }

    private:
        size_type ID_{0};
        set_partition data_{};
        IntType n_{0};
        number_partition num_partition{};

        friend class boost::iterator_core_access;
    }; // end class iterator

private:
    IntType n_;
    IntType min_num_parts_;
    IntType max_num_parts_;
    size_type size_;

private:
    // Private static functions
    static size_type calc_size(IntType n, IntType minnumparts, IntType maxnumparts)
    {
        size_type toReturn = 0;

        for (IntType k = minnumparts; k <= maxnumparts; ++k)
            toReturn += stirling_partition_number(n, k);

        return toReturn;
    }

    static difference_type pop(set_partition& data, IntType num)
    {
        const difference_type n = data.size();
        for (difference_type i = 0; i < n; ++i)
        {
            if (!data[i].empty() && data[i].back() == num)
            {
                data[i].pop_back();
                return i;
            }
        }

        // 			cout << "not found, returning -1" << endl;
        return -1;
    }

    static difference_type NextAcceptablePlaceToAdd(const set_partition& data,
                                                    const number_partition& part,
                                                    difference_type oldpos = -1)
    {
        // 			cout << "Finding if I can put the next number where " <<
        // endl;
        const difference_type n = data.size();
        for (difference_type i = oldpos + 1; i < n; ++i)
        {
            const difference_type dataisize = data[i].size();
            if (dataisize == part[i])
                continue;

            if ((i > 0) && (part[i - 1] == part[i]) && data[i - 1].empty())
                continue;

            return i;
        }

        return -1;
    }
    static bool shouldBreak(const set_partition& data,
                            const number_partition& part,
                            difference_type currpos,
                            difference_type anteriorpos)
    {
        if (currpos == -1)
            return true;

        if (currpos < anteriorpos)
        {
            if (part[currpos] != part[anteriorpos])
                return true;

            if (!data[currpos].empty())
                return true;
        }

        return false;
    }

}; // end class SetPartitions

using set_partitions = SetPartitions<int>;

} // namespace discreture
