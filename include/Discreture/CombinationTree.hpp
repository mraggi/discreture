#pragma once

#include "Misc.hpp"
#include "VectorHelpers.hpp"

// clang-format off
/*
*  A combination tree is something like this:
*
*          0         1
*         /|\       /
*        1 2 3     2
*       /|  \      |
*      2 3   3     3
*
* i.e. the *branches* are the actual combinations. The idea is that while
* exploring, the tree might be prunned.
*
*/
// clang-format on

namespace discreture
{
template <class IntType, class Predicate, class RAContainerInt = std::vector<IntType>>
class CombinationTree
{
public:
    static_assert(std::is_integral<IntType>::value,
                  "Template parameter IntType must be integral");
    static_assert(std::is_signed<IntType>::value,
                  "Template parameter IntType must be signed");
    using value_type = RAContainerInt;
    using combination = value_type;
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;

public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param n is an integer >= 0
    /// \param k is an integer with 0 <= k <= n
    /// \param p is a partial predicate (unary function or functor) that takes
    /// as input a partial combination and returns either true or false.
    ///
    ////////////////////////////////////////////////////////////
    CombinationTree(IntType n, IntType k, Predicate p)
        : n_(n), k_(k), begin_(n_, k_, p), end_(p, true), pred_(p)
    {
        // 			cout << "In constructor" << endl;
    }

    IntType get_n() const { return n_; }
    IntType get_k() const { return k_; }

    ////////////////////////////////////////////////////////////
    /// \brief Forward iterator for constructing combinations that satisfy a
    /// certain predicate one by one
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator, const combination&, boost::forward_traversal_tag>
    {
    public:
        iterator(Predicate p, bool last)
            : ID_(0), data_(), at_end_(last), pred_(p)
        {} // empty initializer

        iterator(IntType n, IntType k, Predicate p)
            : ID_(0), n_(n), k_(k), data_(), at_end_(false), pred_(p)
        {
            data_.reserve(k_);

            while (DFSUtil(data_, pred_, n_, k_))
            {
                if (data_.size() == static_cast<size_t>(k_))
                {
                    return;
                }
            }

            at_end_ = true;
        }

        inline bool is_at_end(IntType n) const
        {
            UNUSED(n);
            return at_end_;
        }

    private:
        // prefix
        void increment()
        {
            // 				cout << "size of pred: " << sizeof(pred_) << endl;
            while (DFSUtil(data_, pred_, n_, k_))
            {
                if (data_.size() == static_cast<size_t>(k_))
                    return;
            }

            at_end_ = true;
        }

        const combination& dereference() const { return data_; }

        bool equal(const iterator& it) const
        {
            if (at_end_ != it.at_end_)
                return false;

            if (at_end_)
                return true;

            return data_ == it.data_;
        }

    private:
        size_type ID_{0};
        IntType n_{0};
        IntType k_{0};
        combination data_{};
        bool at_end_{true};
        Predicate pred_;

        friend class CombinationTree;
        friend class boost::iterator_core_access;

    }; // end class iterator

    const iterator& begin() const { return begin_; }

    const iterator& end() const { return end_; }

private:
    IntType n_;
    IntType k_;
    iterator begin_;
    iterator end_;
    Predicate pred_;

    static bool augment(combination& comb,
                        Predicate pred,
                        IntType n_,
                        IntType k_,
                        IntType start = 0)
    {
        if (comb.empty())
        {
            if (start < n_ - k_ + 1)
            {
                comb.push_back(start);
                return true;
            }

            return false;
        }

        auto last = comb.back();
        auto guysleft = k_ - comb.size();

        start = std::max(static_cast<IntType>(last + 1), start);

        for (size_t i = start; i < n_ - guysleft + 1; ++i)
        {
            comb.push_back(i);

            if (pred(comb))
                return true;

            comb.pop_back();
        }

        return false;
    }

    static bool DFSUtil(combination& comb, Predicate pred, IntType n_, IntType k_)
    {
        // 			cout << "n,k = " << n_ << " " << k_ << endl;
        if (comb.size() < static_cast<size_t>(k_))
        {
            if (augment(comb, pred, n_, k_))
                return true;
        }

        auto last = comb.back();

        // If it can't be augmented, be it because size is already k or else, we
        // have to start backtracking
        while (!comb.empty())
        {
            last = comb.back();
            comb.pop_back();

            if (augment(comb, pred, n_, k_, last + 1))
                return true;
        }

        return false;
    }

}; // end class CombinationTree

} // namespace discreture
