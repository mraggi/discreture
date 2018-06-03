#pragma once
#include "IntegerInterval.hpp"
#include "Misc.hpp"
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <cassert>
#include <vector>

namespace dscr
{

//////////////////////////////////////////
/// \brief Similar to python range(n) or range(n,m) or range(n,m,step).
//////////////////////////////////////////
template <class IntType>
class ArithmeticProgression
{
public:
    using value_type = IntType;
    using difference_type = long long;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;

public:
    ////////////////////////////////////////////////////////////
    /// \brief Single integer constructor. It's usually better to use
    /// integer_interval(n) instead (faster)
    ///
    /// \param n is an integer >= 0
    ///
    /// \return An abstract random-access container whose elements are
    /// {0,1,2,...,n-1}
    ///
    ////////////////////////////////////////////////////////////
    explicit ArithmeticProgression(IntType n)
        : m_from(0), m_to(n), m_step(1)
    {
        assert(n >= 0);
    }

    //////////////////////////////////////////
    /// \brief Constructor. Automatically detects wheter step size is positive
    /// or negative and adjusts accordingly \param n is an integer \return an
    /// abstract random-access container whose elements are
    /// {n,n+step,n+2*step,...} up to (and not including) t_to.
    //////////////////////////////////////////
    ArithmeticProgression(IntType from, IntType to, IntType step = 1)
        : m_from(from), m_to(to), m_step(step)
    {
        assert(m_step != 0);
        if (m_step > 0 && m_to < m_from)
            m_to = m_from;
        if (m_step < 0 && m_to > m_from)
            m_to = m_from;

        auto d = modulo<IntType>(m_from - m_to, m_step);

        if (m_step > 0)
            m_to += d;
        else
        {
            m_to += d + m_step;
            if (d == 0)
                m_to -= m_step;
        }
    }

    size_type size() const
    {
        auto t = m_to + modulo<difference_type>(m_from - m_to, m_step);
        return (t - m_from)/m_step;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Random access iterator class.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator,
                                        const IntType&,
                                        boost::random_access_traversal_tag>
    {
    public:
        explicit iterator(size_type t_from = 0, size_type t_step = 1)
            : m_ID(t_from), m_step(t_step)
        {}

        size_type step() const { return m_step; }

    private:
        void increment() { m_ID += m_step; }

        void decrement() { m_ID -= m_step; }

        const IntType& dereference() const { return m_ID; }

        void advance(difference_type n) { m_ID += n*m_step; }

        bool equal(const iterator& it) const { return m_ID == it.m_ID; }

        difference_type distance_to(const iterator& it) const
        {
            assert(m_step != 0);
            return (static_cast<difference_type>(it.m_ID) -
                    static_cast<difference_type>(m_ID)) /
              m_step;
        }

    private:
        IntType m_ID{0};
        size_type m_step{1};

        friend class boost::iterator_core_access;
        friend class ArithmeticProgression;
    }; // end class iterator

    iterator begin() const { return iterator(m_from, m_step); }
    iterator end() const { return iterator(m_to, m_step); }

    IntType operator[](size_type m) const { return m_from + m_step*m; }

    template <class Pred>
    IntType partition_point(Pred p)
    {
        return *std::partition_point(begin(), end(), p);
    }

private:
    IntType m_from;
    IntType m_to;
    IntType m_step;
}; // end class ArithmeticProgression

using arithmetic_progression = ArithmeticProgression<int>;
using big_arithmetic_progression = ArithmeticProgression<std::int64_t>;

} // namespace dscr
