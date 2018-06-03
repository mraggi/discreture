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
template <class IntType>
class basic_integer_interval
{
public:
    using value_type = IntType;
    using difference_type = long long; // NOLINT
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;

public:
    explicit basic_integer_interval() {}

    explicit basic_integer_interval(IntType n) : m_end(n) { assert(n >= 0); }
    explicit basic_integer_interval(IntType from, IntType to)
        : m_start(from), m_end(to)
    {
        assert(size() >= 0);
    }

    size_type size() const { return m_end - m_start; }

    ////////////////////////////////////////////////////////////
    /// \brief Random access iterator class.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator,
                                        const IntType&,
                                        boost::random_access_traversal_tag>
    {
    public:
        explicit iterator(IntType t = 0) : m_ID(t) {}

    private:
        void increment() { ++m_ID; }

        void decrement() { --m_ID; }

        const IntType& dereference() const { return m_ID; }

        void advance(difference_type n) { m_ID += n; }

        bool equal(const iterator& it) const { return m_ID == it.m_ID; }

        difference_type distance_to(const iterator& it) const
        {
            return (static_cast<difference_type>(it.m_ID) -
                    static_cast<difference_type>(m_ID));
        }

    private:
        IntType m_ID{0};

        friend class boost::iterator_core_access;
        friend class basic_integer_interval;
    }; // end class iterator

    iterator begin() const { return iterator(m_start); }
    iterator end() const { return iterator(m_end); }

    IntType operator[](size_type m) const { return m_start + m; }

    // returns the first integer that does NOT satisfy Predicate
    template <class Predicate>
    IntType partition_point(Predicate p)
    {
        return *std::partition_point(begin(), end(), p);
    }

private:
    IntType m_start{0};
    IntType m_end{0};
}; // end class basic_integer_interval

using integer_interval = basic_integer_interval<int>;
using big_integer_interval = basic_integer_interval<std::int64_t>;

template <class IntType>
auto NN(IntType n)
{
    return basic_integer_interval<IntType>{n};
}

template <class IntType>
auto NN(IntType from, IntType to)
{
    return basic_integer_interval<IntType>{from, to};
}

template <class Container, class T = typename Container::size_type>
auto indices(const Container& C)
{
    return basic_integer_interval<T>(C.size());
}

} // namespace dscr
