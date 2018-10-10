#pragma once
#include "Misc.hpp"
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <cassert>
#include <vector>

namespace discreture
{

// An integer interval is a closed-open interval of integers. For example,
// IntegerInterval(3,8) = {3,4,5,6,7}.
template <class IntType = int>
class IntegerInterval
{
public:
    static_assert(std::is_integral<IntType>::value,
                  "Template parameter IntType must be integral");
    using value_type = IntType;
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;
    class reverse_iterator;
    using const_reverse_iterator = reverse_iterator;

public:
    explicit IntegerInterval() = default;

    explicit IntegerInterval(IntType n) : last_(n)
    {
        if (last_ < 0)
            last_ = 0;
    }

    explicit IntegerInterval(IntType from, IntType to) : first_(from), last_(to)
    {
        if (last_ < first_) // empty interval
            last_ = first_;
    }

    size_type size() const { return last_ - first_; }
    IntType operator[](size_type i) const { return first_ + i; }

    class iterator
        : public boost::iterator_facade<iterator, const IntType&, boost::random_access_traversal_tag>
    {
    public:
        explicit iterator(IntType t = 0) : value_(t) {}

    private:
        void increment() { ++value_; }

        void decrement() { --value_; }

        const IntType& dereference() const { return value_; }

        void advance(difference_type n) { value_ += n; }

        bool equal(const iterator& other) const
        {
            return value_ == other.value_;
        }

        difference_type distance_to(const iterator& other) const
        {
            return static_cast<difference_type>(other.value_) - value_;
        }

    private:
        IntType value_{0};

        friend class boost::iterator_core_access;
    }; // end class iterator

    iterator begin() const { return iterator(first_); }
    iterator end() const { return iterator(last_); }

    class reverse_iterator
        : public boost::iterator_facade<reverse_iterator,
                                        const IntType&,
                                        boost::random_access_traversal_tag>
    {
    public:
        explicit reverse_iterator(IntType t = 0) : value_(t) {}

    private:
        void increment() { --value_; }

        void decrement() { ++value_; }

        const IntType& dereference() const { return value_; }

        void advance(difference_type n) { value_ -= n; }

        bool equal(const reverse_iterator& other) const
        {
            return value_ == other.value_;
        }

        difference_type distance_to(const reverse_iterator& other) const
        {
            return value_ - other.value_;
        }

    private:
        IntType value_{0};

        friend class boost::iterator_core_access;
    }; // end class iterator

    reverse_iterator rbegin() const { return reverse_iterator(last_ - 1); }
    reverse_iterator rend() const { return reverse_iterator(first_ - 1); }

    // returns the first integer that does NOT satisfy Predicate
    template <class Predicate>
    IntType partition_point(Predicate p)
    {
        return *std::partition_point(begin(), end(), p);
    }

private:
    IntType first_{0};
    IntType last_{0};
}; // end class IntegerInterval

using integer_interval = IntegerInterval<int>;
using big_integer_interval = IntegerInterval<std::int64_t>;

// Think of NN as the set of natural numbers.
template <class IntType>
auto NN(IntType n)
{
    return IntegerInterval<IntType>{n};
}

template <class IntTypeFrom, class IntTypeTo>
auto II(IntTypeFrom from, IntTypeTo to)
{
    using intt = std::common_type_t<IntTypeFrom, IntTypeTo>;
    return IntegerInterval<intt>{from, to};
}

template <class Container, class Index = std::ptrdiff_t>
auto indices(const Container& C)
{
    return IntegerInterval<Index>(C.size());
}

} // namespace discreture
