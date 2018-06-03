#pragma once
#include "IntegerInterval.hpp"
#include "Misc.hpp"
#include "VectorHelpers.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace dscr
{
template <class IntType, class RAContainerInt = std::vector<IntType>>
class basic_multisets
{
public:
    using value_type = RAContainerInt;
    using multiset = value_type;
    using difference_type = long long; // NOLINT
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;
    class reverse_iterator;
    using const_reverse_iterator = reverse_iterator;

public:
    static void next_multiset(multiset& sub, const multiset& total)
    {
        next_multiset(sub, total, total.size());
    }

    static void next_multiset(multiset& sub, const multiset& total, size_t n)
    {
        assert(n == sub.size());
        assert(n == total.size());
        for (size_t i = 0; i < n; ++i)
        {
            if (can_increment(i, sub, total))
            {
                ++sub[i];

                return;
            }
            sub[i] = 0;
        }
    }

    static void prev_multiset(multiset& sub, const multiset& total, size_t n)
    {
        assert(n == sub.size());
        assert(n == total.size());

        for (size_t i = 0; i < n; ++i)
        {
            if (sub[i] != 0)
            {
                --sub[i];
                return;
            }
            sub[i] = total[i];
        }
    }

    static void
    construct_multiset(multiset& sub, const multiset& total, size_type m)
    {
        assert(sub.size() == total.size());
        size_type n = total.size();
        if (n == 0)
            return;
        for (auto& s : sub)
            s = 0;
        std::vector<size_type> coeffs(n);
        coeffs[0] = 1;
        for (size_type i = 1; i < n; ++i)
        {
            coeffs[i] = coeffs[i - 1]*(total[i - 1] + 1);
        }

        for (difference_type i = n - 1; i >= 0; --i)
        {
            size_type w = coeffs[i];
            auto t =
              big_integer_interval(total[i] + 1)
                .partition_point([m, w](size_type a) { return a*w <= m; }) -
              1;
            sub[i] = t;
            m -= w*t;
            if (m <= 0)
                break;
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief class of all submultisets of a given multiset, expressed as
    /// incidence vectors with multiplicities \param IntType can be an int,
    /// short, etc. # Example:
    ///
    ///	 multisets X({1,0,3,1});
    ///		for (const auto& x : X)
    ///			std::cout << x << " ";
    ///
    /// Prints out:
    ///
    /// 	[ 0 0 0 0 ]
    ///		[ 1 0 0 0 ]
    ///		[ 0 0 1 0 ]
    ///		[ 1 0 1 0 ]
    ///		[ 0 0 2 0 ]
    ///		[ 1 0 2 0 ]
    ///		[ 0 0 3 0 ]
    ///		[ 1 0 3 0 ]
    ///		[ 0 0 0 1 ]
    ///		[ 1 0 0 1 ]
    ///		[ 0 0 1 1 ]
    ///		[ 1 0 1 1 ]
    ///		[ 0 0 2 1 ]
    ///		[ 1 0 2 1 ]
    ///		[ 0 0 3 1 ]
    ///		[ 1 0 3 1 ]
    ///
    ////////////////////////////////////////////////////////////
    explicit basic_multisets(const multiset& set) : m_total(set), m_size(1)
    {
        for (auto x : set)
        {
            m_size *= (x + 1);
        }
    }

    explicit basic_multisets(IntType size, IntType n = 1)
        : m_total(size, n), m_size(std::pow(n + 1, size))
    {}

    size_type size() const { return m_size; }

    iterator begin() const { return iterator(m_total); }

    const iterator end() const
    {
        return iterator::make_invalid_with_id(size());
    }

    reverse_iterator rbegin() const { return reverse_iterator(m_total); }

    const reverse_iterator rend() const
    {
        return reverse_iterator::make_invalid_with_id(size());
    }

    //////////////////////////////
    /// @brief Random Access Capabilities for multiset
    /// @param m assumes 0 <= m < size(). Undefined behaviour otherwise
    //////////////////////////////
    multiset operator[](size_type m) const
    {
        assert(m >= 0 && m < size());
        multiset sub(m_total.size());
        construct_multiset(sub, m_total, m);
        return sub;
    }

    //////////////////////////////
    /// @brief Opposite operator to operator[]
    /// @param sub given a multiset, what would it's index be?
    //////////////////////////////
    size_type get_index(const multiset& sub) const
    {
        assert(sub.size() == m_total.size());
        size_type coeff = 1;
        size_type result = 0;
        for (size_t i = 0; i < m_total.size(); ++i)
        {
            result += coeff*sub[i];
            coeff *= (m_total[i] + 1);
        }
        return result;
    }

    class iterator
        : public boost::iterator_facade<iterator,
                                        const multiset&,
                                        boost::random_access_traversal_tag>
    {

    public:
        iterator() = default;

        explicit iterator(const multiset& total)
            : m_ID(0)
            , m_n(total.size())
            , m_submulti(total.size(), 0)
            , m_total(&total)
        {}

        size_type ID() const { return m_ID; }

        static const iterator make_invalid_with_id(size_type id)
        {
            return iterator(id);
        }

    private:
        explicit iterator(size_type id) : m_ID(id) {}

        void increment()
        {
            ++m_ID;
            next_multiset(m_submulti, *m_total, m_n);
        }

        void decrement()
        {
            --m_ID;
            prev_multiset(m_submulti, *m_total, m_n);
        }

        const multiset& dereference() const { return m_submulti; }

        // It only makes sense to compare iterators from the SAME multiset.
        bool equal(const iterator& it) const { return m_ID == it.m_ID; }

        void advance(difference_type m)
        {
            m_ID += m;
            construct_multiset(m_submulti, *m_total, m_ID);
        }

        difference_type distance_to(const iterator& it) const
        {
            return static_cast<difference_type>(it.ID()) - ID();
        }

    private:
        size_type m_ID{0};
        size_type m_n{0};
        multiset m_submulti{};
        multiset const* m_total{nullptr};

        friend class boost::iterator_core_access;
    };

    class reverse_iterator
        : public boost::iterator_facade<reverse_iterator,
                                        const multiset&,
                                        boost::bidirectional_traversal_tag>
    {

    public:
        reverse_iterator() = default;

        explicit reverse_iterator(const multiset& total)
            : m_ID(0), m_n(total.size()), m_submulti(total), m_total(&total)
        {}

        size_type ID() const { return m_ID; }

        static const reverse_iterator make_invalid_with_id(size_type id)
        {
            return reverse_iterator(id);
        }

    private:
        explicit reverse_iterator(size_type id) : m_ID(id) {}

        // prefix
        void increment()
        {
            ++m_ID;
            prev_multiset(m_submulti, *m_total, m_n);
        }

        void decrement()
        {
            --m_ID;
            next_multiset(m_submulti, *m_total, m_n);
        }

        const multiset& dereference() const { return m_submulti; }

        // It only makes sense to compare iterators from the SAME multiset.
        bool equal(const reverse_iterator& it) const { return m_ID == it.m_ID; }

        difference_type distance_to(const reverse_iterator& other) const
        {
            return static_cast<difference_type>(other.ID()) - ID();
        }

    private:
        size_type m_ID{0};
        size_type m_n{0}; // must have m_n = m_submulti.size() = m_total->size()
        multiset m_submulti{};
        multiset const* m_total{nullptr};

        friend class boost::iterator_core_access;
    };

private:
    multiset m_total;
    size_type m_size;

    static bool
    can_increment(size_t index, const multiset& sub, const multiset& total)
    {
        return sub[index] < total[index];
    }
};
using multisets = basic_multisets<int>;
using multisets_fast =
  basic_multisets<int, boost::container::static_vector<int, 48>>;

} // namespace dscr
