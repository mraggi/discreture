#pragma once
#include "Misc.hpp"
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <cassert>
#include <vector>

namespace dscr
{

//////////////////////////////////////////
/// \brief In set theory, a common way of defining a natural number is. n :=
/// {0,1,2,...,n-1}, with 0 = {}.
//////////////////////////////////////////
template <class IntType = int>
class IntegerInterval
{
public:
    using value_type = IntType;
    using difference_type = long long;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;

public:
    explicit IntegerInterval() = default;

    explicit IntegerInterval(IntType n) : last_(n) { assert(n >= 0); }
    explicit IntegerInterval(IntType from, IntType to) : first_(from), last_(to)
    {
        assert(size() >= 0);
    }

    size_type size() const { return last_ - first_; }

    ////////////////////////////////////////////////////////////
    /// \brief Random access iterator class.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator,
                                        const IntType&,
                                        boost::random_access_traversal_tag>
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

    IntType operator[](size_type i) const { return first_ + i; }

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

template <class IntType>
auto NN(IntType n)
{
    return IntegerInterval<IntType>{n};
}

template <class IntType>
auto NN(IntType from, IntType to)
{
    return IntegerInterval<IntType>{from, to};
}

template <class Container, class T = typename Container::size_type>
auto indices(const Container& C)
{
    return IntegerInterval<T>(C.size());
}

} // namespace dscr
