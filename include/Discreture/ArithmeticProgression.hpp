#pragma once
#include "IntegerInterval.hpp"
#include "Misc.hpp"
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <cassert>
#include <vector>

namespace discreture
{

// An arithmetic progression is simply a set of the form
// {a,a+d,a+2d,a+3d,...,a+kd}. Similar to python range(n,m,step).
template <class IntType>
class ArithmeticProgression
{
public:
    static_assert(std::is_integral<IntType>::value,
                  "Template parameter IntType must be integral");
    static_assert(std::is_signed<IntType>::value,
                  "Template parameter IntType must be signed");
    using value_type = IntType;
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;
    using reverse_iterator = iterator;
    using const_reverse_iterator = reverse_iterator;

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
    explicit ArithmeticProgression(IntType n) : from_(0), to_(n), step_(1)
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
        : from_(from), to_(to), step_(step)
    {
        assert(step_ != 0);
        if (step_ > 0 && to_ < from_)
            to_ = from_;
        if (step_ < 0 && to_ > from_)
            to_ = from_;

        auto d = modulo<IntType>(from_ - to_, step_);

        if (step_ > 0)
            to_ += d;
        else
        {
            to_ += d + step_;
            if (d == 0)
                to_ -= step_;
        }
    }

    size_type size() const
    {
        auto t = to_ + modulo<difference_type>(from_ - to_, step_);
        return (t - from_)/step_;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Random access iterator class.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator, const IntType&, boost::random_access_traversal_tag>
    {
    public:
        explicit iterator(size_type t_from = 0, size_type t_step = 1)
            : m_ID(t_from), step_(t_step)
        {}

        size_type step() const { return step_; }

    private:
        void increment() { m_ID += step_; }

        void decrement() { m_ID -= step_; }

        const IntType& dereference() const { return m_ID; }

        void advance(difference_type n) { m_ID += n*step_; }

        bool equal(const iterator& it) const { return m_ID == it.m_ID; }

        difference_type distance_to(const iterator& it) const
        {
            assert(step_ != 0);
            return (static_cast<difference_type>(it.m_ID) -
                    static_cast<difference_type>(m_ID)) /
              step_;
        }

    private:
        IntType m_ID{0};
        size_type step_{1};

        friend class boost::iterator_core_access;
        friend class ArithmeticProgression;
    }; // end class iterator

    iterator begin() const { return iterator(from_, step_); }
    iterator end() const { return iterator(to_, step_); }

    iterator rbegin() const { return iterator(to_ - step_, -step_); }
    iterator rend() const { return iterator(from_ - step_, -step_); }

    IntType operator[](size_type m) const { return from_ + step_*m; }

    template <class Pred>
    IntType partition_point(Pred p)
    {
        return *std::partition_point(begin(), end(), p);
    }

private:
    IntType from_;
    IntType to_;
    IntType step_;
}; // end class ArithmeticProgression

using arithmetic_progression = ArithmeticProgression<int>;
using big_arithmetic_progression = ArithmeticProgression<std::int64_t>;

} // namespace discreture
