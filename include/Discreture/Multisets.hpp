#pragma once
#include "IntegerInterval.hpp"
#include "Misc.hpp"
#include "VectorHelpers.hpp"
#include "detail/MultisetsDetail.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace discreture
{

/**
 *@brief Multisets is a container to iterate over all subsets of a multiset.
 *
 *For example, let's suppose you have the multiset {0,0,0,1,1,2,2,2,2,3,3,5}.
 *First, we encode this as [3,2,4,2,0,1], meaning we take three 0's, two 1's,
 *etc. Then, the set of submultisets of this can be encoded as lists of length 6
 *where the first element is less than 3, the second less than 2, the third less
 *than 4, and so on. So for example, [1,0,0,2,0,1], representing {0,3,3,5}, is
 *in multisets([3,2,4,2,0,1])
 *
 *# Example usage:
 *
 *	multisets X({1,0,3,1});
 *	for (auto&& x : X)
 *		std::cout << x << " ";
 *
 *Prints out:
 *
 *	[ 0 0 0 0 ]
 *	[ 1 0 0 0 ]
 *	[ 0 0 1 0 ]
 *	[ 1 0 1 0 ]
 *	[ 0 0 2 0 ]
 *	[ 1 0 2 0 ]
 *	[ 0 0 3 0 ]
 *	[ 1 0 3 0 ]
 *	[ 0 0 0 1 ]
 *	[ 1 0 0 1 ]
 *	[ 0 0 1 1 ]
 *	[ 1 0 1 1 ]
 *	[ 0 0 2 1 ]
 *	[ 1 0 2 1 ]
 *	[ 0 0 3 1 ]
 *	[ 1 0 3 1 ]
 *
 */

template <class IntType = int, class RAContainerInt = std::vector<IntType>>
class Multisets
{
public:
    static_assert(std::is_integral<IntType>::value,
                  "Template parameter IntType must be integral");
    static_assert(std::is_signed<IntType>::value,
                  "Template parameter IntType must be signed");
    using value_type = RAContainerInt;
    using multiset = value_type;
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;
    class reverse_iterator;
    using const_reverse_iterator = reverse_iterator;

public:
    explicit Multisets(const multiset& set) : total_(set), size_(1)
    {
        for (auto x : set)
        {
            size_ *= (x + 1);
        }
    }

    explicit Multisets(IntType size, IntType n = 1)
        : total_(size, n), size_(std::pow(n + 1, size))
    {}

    size_type size() const { return size_; }

    iterator begin() const { return iterator(total_); }

    const iterator end() const
    {
        return iterator::make_invalid_with_id(size());
    }

    reverse_iterator rbegin() const { return reverse_iterator(total_); }

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
        multiset sub(total_.size());
        construct_multiset(sub, total_, m);
        return sub;
    }

    //////////////////////////////
    /// @brief Opposite operator to operator[]
    /// @param sub given a multiset, what would it's index be?
    //////////////////////////////
    size_type get_index(const multiset& sub) const
    {
        assert(sub.size() == total_.size());
        size_type coeff = 1;
        size_type result = 0;
        for (size_t i = 0; i < total_.size(); ++i)
        {
            result += coeff*sub[i];
            coeff *= (total_[i] + 1);
        }
        return result;
    }

    class iterator
        : public boost::iterator_facade<iterator, const multiset&, boost::random_access_traversal_tag>
    {

    public:
        iterator() = default;

        explicit iterator(const multiset& total)
            : ID_(0), n_(total.size()), submulti_(total.size(), 0), total_(&total)
        {}

        size_type ID() const { return ID_; }

        static const iterator make_invalid_with_id(size_type id)
        {
            return iterator(id);
        }

    private:
        explicit iterator(size_type id) : ID_(id) {}

        void increment()
        {
            ++ID_;
            next_multiset(submulti_, *total_, n_);
        }

        void decrement()
        {
            --ID_;
            prev_multiset(submulti_, *total_, n_);
        }

        const multiset& dereference() const { return submulti_; }

        // It only makes sense to compare iterators from the SAME multiset.
        bool equal(const iterator& it) const { return ID_ == it.ID_; }

        void advance(difference_type m)
        {
            ID_ += m;
            construct_multiset(submulti_, *total_, ID_);
        }

        difference_type distance_to(const iterator& it) const
        {
            return static_cast<difference_type>(it.ID()) - ID();
        }

    private:
        size_type ID_{0};
        size_type n_{0};
        multiset submulti_{};
        multiset const* total_{nullptr};

        friend class boost::iterator_core_access;
    };

    class reverse_iterator
        : public boost::iterator_facade<reverse_iterator,
                                        const multiset&,
                                        boost::random_access_traversal_tag>
    {
    public:
        reverse_iterator() = default;

        explicit reverse_iterator(const multiset& total)
            : ID_(0), n_(total.size()), submulti_(total), total_(&total)
        {}

        size_type ID() const { return ID_; }

        static const reverse_iterator make_invalid_with_id(size_type id)
        {
            return reverse_iterator(id);
        }

    private:
        explicit reverse_iterator(size_type id) : ID_(id) {}

        // prefix
        void increment()
        {
            ++ID_;
            prev_multiset(submulti_, *total_, n_);
        }

        void decrement()
        {
            --ID_;
            next_multiset(submulti_, *total_, n_);
        }

        void advance(difference_type m)
        {
            size_type s = 1;
            for (auto x : *total_)
                s *= (x + 1);
            ID_ += m;
            construct_multiset(submulti_, *total_, s - ID_ - 1);
        }

        const multiset& dereference() const { return submulti_; }

        // It only makes sense to compare iterators from the SAME multiset.
        bool equal(const reverse_iterator& it) const { return ID_ == it.ID_; }

        difference_type distance_to(const reverse_iterator& other) const
        {
            return static_cast<difference_type>(other.ID()) - ID();
        }

    private:
        size_type ID_{0};
        size_type n_{0}; // must have n_ = submulti_.size() = total_->size()
        multiset submulti_{};
        multiset const* total_{nullptr};

        friend class boost::iterator_core_access;
    };

    template <class Func>
    void for_each(Func f) const
    {
        switch (total_.size())
        {
            // clang-format off
        case 0: detail::for_each_multiset<multiset,0>::apply(total_,f); break;
        case 1: detail::for_each_multiset<multiset,1>::apply(total_,f); break;
        case 2: detail::for_each_multiset<multiset,2>::apply(total_,f); break;
        case 3: detail::for_each_multiset<multiset,3>::apply(total_,f); break;
        case 4: detail::for_each_multiset<multiset,4>::apply(total_,f); break;
        case 5: detail::for_each_multiset<multiset,5>::apply(total_,f); break;
        case 6: detail::for_each_multiset<multiset,6>::apply(total_,f); break;
        case 7: detail::for_each_multiset<multiset,7>::apply(total_,f); break;
        case 8: detail::for_each_multiset<multiset,8>::apply(total_,f); break;
        case 9: detail::for_each_multiset<multiset,9>::apply(total_,f); break;
        case 10: detail::for_each_multiset<multiset,10>::apply(total_,f); break;
        case 11: detail::for_each_multiset<multiset,11>::apply(total_,f); break;
        case 12: detail::for_each_multiset<multiset,12>::apply(total_,f); break;
        case 13: detail::for_each_multiset<multiset,13>::apply(total_,f); break;
        case 14: detail::for_each_multiset<multiset,14>::apply(total_,f); break;
        case 15: detail::for_each_multiset<multiset,15>::apply(total_,f); break;
        case 16: detail::for_each_multiset<multiset,16>::apply(total_,f); break;
        case 17: detail::for_each_multiset<multiset,17>::apply(total_,f); break;
        case 18: detail::for_each_multiset<multiset,18>::apply(total_,f); break;
        case 19: detail::for_each_multiset<multiset,19>::apply(total_,f); break;
        case 20: detail::for_each_multiset<multiset,20>::apply(total_,f); break;
            // clang-format on

        default:
            for (auto& x : (*this))
            {
                f(x);
            }

            break;
        }
    }

    static void next_multiset(multiset& sub, const multiset& total)
    {
        next_multiset(sub, total, total.size());
    }

    static void next_multiset(multiset& sub, const multiset& total, size_type n)
    {
        assert(n == sub.size());
        assert(n == total.size());
        for (auto i : NN(n))
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

        for (auto i : NN(n))
        {
            if (sub[i] != 0)
            {
                --sub[i];
                return;
            }
            sub[i] = total[i];
        }
    }

    static void construct_multiset(multiset& sub,
                                   const multiset& total,
                                   size_type m)
    {
        assert(sub.size() == total.size());
        size_type n = total.size();
        if (n == 0)
            return;
        for (auto&& s : sub)
            s = 0;
        std::vector<size_type> coeffs(n);
        coeffs[0] = 1;
        for (auto i : II(1, n))
        {
            coeffs[i] = coeffs[i - 1]*(total[i - 1] + 1);
        }

        for (difference_type i = n - 1; i >= 0; --i)
        {
            size_type w = coeffs[i];
            auto t = big_integer_interval(total[i] + 1)
                       .partition_point(
                         [m, w](size_type a) { return a*w <= m; }) -
              1;
            sub[i] = t;
            m -= w*t;
            if (m <= 0)
                break;
        }
    }

private:
    multiset total_;
    size_type size_;

    static bool can_increment(size_t index,
                              const multiset& sub,
                              const multiset& total)
    {
        return sub[index] < total[index];
    }
};

using boost::container::static_vector;

using multisets = Multisets<int>;
using multisets_stack = Multisets<int, static_vector<int, 48>>;

} // namespace discreture
