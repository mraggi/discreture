#pragma once

#include "ArithmeticProgression.hpp"
#include "CombinationTreePrunned.hpp"
#include "CompoundContainer.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "VectorHelpers.hpp"
#include "detail_combinations_tree_bf.hpp"
#include <algorithm>
#include <numeric>

namespace dscr
{

////////////////////////////////////////////////////////////
/// \brief class of all n choose k combinations of size k of the set
/// {0,1,...,n-1} in lexicographic order \param IntType should be an integral
/// type with enough space to store n and k. It can be signed or unsigned.
/// \param n the size of the set
/// \param k the size of the combination (subset). Should be an integer such
/// that n choose k is not bigger than the largest unsigned long int there is.
/// For example, 50 choose 25 is already larger than the largest long long
/// unsigned int. # Example:
///
///		combinations_tree X(6,3);
///		for (const auto& x : X)
///			cout << x << " ";
///
/// Prints out:
///
/// 	[ 0 1 2 ] [ 0 1 3 ] [ 0 1 4 ] [ 0 1 5 ] [ 0 2 3 ] [ 0 2 4 ] [ 0 2 5 ] [
/// 0 3 4 ] [ 0 3 5 ] [ 0 4 5 ] [ 1 2 3 ] [ 1 2 4 ] [ 1 2 5 ] [ 1 3 4 ] [ 1 3 5
/// ] [ 1 4 5 ] [ 2 3 4 ] [ 2 3 5 ] [ 2 4 5 ] [ 3 4 5 ]
///
////////////////////////////////////////////////////////////
template <class IntType = int, class RAContainerInt = std::vector<IntType>>
class CombinationTree
{
public:
    using value_type = RAContainerInt;
    using combination = value_type;
    using difference_type = long long;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;
    class reverse_iterator;
    using const_reverse_iterator = reverse_iterator;

    // **************** Begin static functions
    static inline bool next_combination(combination& data, IntType n)
    {
        const IntType k = data.size();
        const IntType diff = n - k;
        return next_combination(data, n, k, diff);
    }

    static inline bool next_combination(combination& data,
                                        IntType n,
                                        IntType k,
                                        IntType difference)
    {
        if (k == 0)
            return false;
        assert(difference == n - k);
        const IntType last = k - 1;
        if (data[last] + 1 < n)
        {
            ++data[last];
            return true;
        }

        for (IntType i = k - 2; i >= 0; --i)
        {
            if (data[i] != difference + i)
            {
                ++data[i];
                IntType a = data[i] + 1;
                ++i;
                for (; i < k; ++i, ++a)
                {
                    data[i] = a;
                }

                return true;
            }
        }
        return false;
    }

    static inline void prev_combination(combination& data, IntType n)
    {
        if (data.empty())
            return;
        IntType a = n - 1;
        for (difference_type i = data.size() - 1; i > 0L; --i, --a)
        {
            if (data[i] - 1 != data[i - 1])
            {
                --data[i];
                return;
            }
            data[i] = a;
        }
        --data[0];
    }

    static void construct_combination(combination& data, size_type m, IntType n)
    {
        IntType k = data.size();
        m = binomial<size_type>(n, k) - m - 1;

        for (IntType i = 0; i < k; ++i)
        {
            IntType r = k - i;

            // i <= n-t-1 <= n-r implies that the range is this
            big_integer_interval N(r, n - i);
            auto t = N.partition_point([m, r](auto t) {
                return binomial<size_type>(t, r) <= m;
            }) -
              1;

            data[i] = n - t - 1;
            m -= binomial<size_type>(t, r);
        }
    }

    static size_type get_index(const combination& comb, IntType n) // needs n
    {
        size_type k = comb.size();

        size_type result = 0;

        for (difference_type i = 0; i < k; ++i)
            result += binomial<size_type>(n - comb[k - i - 1] - 1, i + 1);

        return binomial<size_type>(n, k) - result - 1;
    }

    ///////////////////////////////////////
    /// \brief Combination comparison "less than" operator. Assumes lhs and rhs
    /// have the same size. \return true if lhs would appear before rhs in the
    /// iteration order, false otherwise
    ///////////////////////////////////////
    static bool compare(const combination& lhs, const combination& rhs)
    {
        assert(lhs.size() == rhs.size());
        auto itl = lhs.begin();
        auto itr = rhs.begin();

        for (; itl != lhs.end(); ++itl, ++itr)
        {
            if (*itl > *itr)
                return false;

            if (*itl < *itr)
                return true;
        }

        return false;
    }
    // **************** End static functions

public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param n is an integer >= 0
    /// \param k is an integer with 0 <= k <= n
    ///
    ////////////////////////////////////////////////////////////
    CombinationTree(IntType n, IntType k)
        : n_(n), k_(k), size_(binomial<size_type>(n, k))
    {}

    ////////////////////////////////////////////////////////////
    /// \brief The total number of combinations
    ///
    /// \return binomial(n,r)
    ///
    ////////////////////////////////////////////////////////////
    size_type size() const { return size_; }

    IntType get_n() const { return n_; }

    IntType get_k() const { return k_; }

    iterator begin() const { return iterator(n_, k_); }

    const iterator end() const { return iterator(size()); }

    reverse_iterator rbegin() const { return reverse_iterator(n_, k_); }

    const reverse_iterator rend() const { return reverse_iterator(size()); }

    ////////////////////////////////////////////////////////////
    /// \brief Access to the m-th combination (slow for iteration)
    ///
    /// This is equivalent to calling *(begin()+m)
    /// \param m should be an integer between 0 and size(). Undefined behavior
    /// otherwise. \return The m-th combination, as defined in the order of
    /// iteration (lexicographic)
    ////////////////////////////////////////////////////////////
    combination operator[](size_type m) const
    {
        assert(m >= 0 && m < size());
        combination comb(k_);
        construct_combination(comb, m, n_);
        return comb;
    }

    size_type get_index(const combination& comb) const
    {
        return get_index(comb, n_);
    }

    iterator get_iterator(const combination& comb) const
    {
        return iterator(comb, n_);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Random access iterator class. It's much more efficient as a
    /// bidirectional iterator than purely random access.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator,
                                        const combination&,
                                        boost::random_access_traversal_tag>
    {
    public:
        iterator()
            : ID_(0LL), n_(0), k_(0), s_(0), data_() {} // empty initializer

        iterator(const combination& comb, IntType n)
            : ID_(CombinationTree<IntType, RAContainerInt>::get_index(comb, n))
            , n_(n)
            , k_(comb.size())
            , s_(n - comb.size())
            , data_(comb)
        {} // empty initializer

        iterator(IntType n, IntType k)
            : ID_(0), n_(n), k_(k), s_(n - k), data_(k)
        {
            std::iota(data_.begin(), data_.end(), 0);
        }

        inline size_type ID() const { return ID_; }

        inline bool is_at_end(IntType n = -1)
          const // not using n, just for compatibility with the combinations
        {
            IntType k = data_.size();
            return data_.front() == n_ - k;
        }

        // 		void reset(IntType n, IntType k)
        // 		{
        // 			ID_ = 0;
        // 			data_.resize(k);
        // 			std::iota(data_.begin(),data_.end(),0);
        // 		}
        static iterator make_invalid_with_id(size_type id)
        {
            return iterator(id);
        }

    private:
        explicit iterator(size_type id)
            : ID_(id)
            , n_()
            , k_()
            , s_()
            , data_() {} // ending initializer: for id only. Do not use unless
                         // you know what you are doing.

        // prefix
        void increment()
        {
            next_combination(data_, n_, k_, s_);
            ++ID_;
        }

        void decrement()
        {
            if (ID_ == 0)
                return;

            --ID_;

            prev_combination(data_, n_);
        }

        const combination& dereference() const { return data_; }

        ////////////////////////////////////////
        ///
        /// \brief Random access capabilities to the iterators
        /// \param n -> This assumes 0 <= n+ID <= size(n,k)
        ///
        ////////////////////////////////////////
        void advance(difference_type n)
        {
            assert(0 <= n + ID_);

            // If n is small, it's actually more efficient to just iterate to it
            if (std::abs(n) < 30)
            {
                while (n > 0)
                {
                    increment();
                    --n;
                }

                while (n < 0)
                {
                    decrement();
                    ++n;
                }

                return;
            }

            // If n is large, then it's better to just construct it from
            // scratch.
            ID_ += n;
            construct_combination(data_, ID_, n_);
        }

        difference_type distance_to(const iterator& other) const
        {
            return other.ID() - ID();
        }

        bool equal(const iterator& it) const { return ID_ == it.ID_; }

    private:
        size_type ID_{0};
        IntType n_;
        IntType k_;
        IntType s_;
        combination data_;

        friend class CombinationTree;
        friend class boost::iterator_core_access;
    }; // end class iterator

    ////////////////////////////////////////////////////////////
    /// \brief Reverse random access iterator class. It's much more efficient as
    /// a bidirectional iterator than purely random access.
    ////////////////////////////////////////////////////////////
    class reverse_iterator
        : public boost::iterator_facade<reverse_iterator,
                                        const combination&,
                                        boost::random_access_traversal_tag>
    {
    public:
        reverse_iterator() : n_(0), data_() {} // empty initializer
        reverse_iterator(IntType n, IntType r) : n_(n), data_(r)
        {
            std::iota(data_.begin(), data_.end(), n - r);
        }

        size_type ID() const { return ID_; }

        bool is_at_end() const
        {
            return ID_ == binomial<size_type>(n_, data_.size());
            ;
        }

        void reset(IntType n, IntType r)
        {
            n_ = n;
            ID_ = 0;
            data_ = IntegerInterval<IntType>(n - r, n);
        }

    private:
        void increment()
        {
            ++ID_;

            prev_combination(data_, n_);
        }

        void decrement()
        {
            assert(ID_ != 0);

            --ID_;

            next_combination(data_, n_);
        }

        const combination& dereference() const { return data_; }

        ////////////////////////////////////////
        ///
        /// \brief Random access capabilities to the iterators
        /// \param m -> This assumes 0 <= m+ID <= size(m,k)
        ///
        ////////////////////////////////////////
        void advance(difference_type m)
        {
            assert(0 <= m + ID_);

            if (std::abs(m) < 20)
            {
                while (m > 0)
                {
                    increment();
                    --m;
                }

                while (m < 0)
                {
                    decrement();
                    ++m;
                }

                return;
            }

            ID_ += m;
            auto num = binomial<size_type>(n_, data_.size()) - ID_ - 1;
            // If n is large, then it's better to just construct it from
            // scratch.
            construct_combination(data_, num, n_);
        }

        difference_type distance_to(const reverse_iterator& lhs) const
        {
            return static_cast<difference_type>(lhs.ID()) - ID();
        }

        bool equal(const reverse_iterator& it) const { return it.ID() == ID(); }

    private:
        explicit reverse_iterator(size_type id)
            : ID_(id), data_() {} // ending initializer: for id only. Do not
                                  // use unless you know what you are doing.

        IntType n_{};
        size_type ID_{};
        combination data_;

        friend class CombinationTree;
        friend class boost::iterator_core_access;

    }; // end class reverse_iterator

    ///////////////////////////////////////////////
    /// \brief This is an efficient way to construct a combination of size k
    /// which fully satisfies a predicate
    ///
    /// This function is conceptually equivalent to std::find_if(begin(), end(),
    /// Pred), but much faster if the predicate can be evaluated on a partial
    /// combination (so as to prune the search tree)
    ///
    /// # Example:
    ///
    /// 	combinations X(40,6);
    /// 	auto it = X.find_if([](const combinations::combination& comb) ->
    /// bool
    /// 	{
    /// 		for (int i = 0; i < comb.size()-1; ++i)
    /// 		{
    /// 			if (2*comb[i] + 1 > comb[i+1])
    /// 				return false;
    /// 		}
    /// 		return true;
    ///		});
    /// 	cout << *it << endl;
    ///
    /// Prints out:
    /// 	[ 0 1 3 7 15 31 ]
    ///
    ///
    /// \param Pred should be what we call a *partial predicate*: It takes a
    /// combination as a parameter and returns either true or false.
    ///
    ///
    /// \return An interator to a combination which fully satisfies the
    /// predicate.
    ///
    /////////////////////////////////////////////
    template <class PartialPredicate>
    iterator find_if(PartialPredicate pred)
    {
        combination A;
        A.reserve(k_);

        while (DFSUtil(A, pred))
        {
            if (A.size() == static_cast<size_t>(k_))
                return get_iterator(A);
        }

        return end();
    }

    ///////////////////////////////////////////////
    /// \brief This is an efficient way to construct all combination of size k
    /// which fully satisfy a predicate
    ///
    /// This function is similar to find_if, but it returns an object for which
    /// you can iterate over all combinations which satisfy Predicate pred,
    ///
    /// # Example:
    ///
    /// 	combinations X(30,4);
    /// 	auto vall = X.find_all([](constcombinations::combination& comb) ->
    /// bool
    ///		{
    ///			if (comb.size() < 2) return true;
    ///			int k = comb.size();
    ///			if (comb[k-2] == 0) return false;
    ///			return (comb[k-1]%comb[k-2] == 0);
    ///		});
    /// 	for (auto& v : vall)
    /// 		cout << v << endl;
    ///
    ///
    /// Prints out:
    /// 	[ 1 2 4 8 ]
    /// 	[ 1 2 4 12 ]
    /// 	[ 1 2 4 16 ]
    /// 	[ 1 2 4 20 ]
    /// 	[ 1 2 4 24 ]
    /// 	[ 1 2 4 28 ]
    /// 	[ 1 2 6 12 ]
    /// 	[ 1 2 6 18 ]
    /// 	[ 1 2 6 24 ]
    /// 	[ 1 2 8 16 ]
    /// 	[ 1 2 8 24 ]
    /// 	[ 1 2 10 20 ]
    /// 	[ 1 2 12 24 ]
    /// 	[ 1 2 14 28 ]
    /// 	[ 1 3 6 12 ]
    /// 	[ 1 3 6 18 ]
    /// 	[ 1 3 6 24 ]
    /// 	[ 1 3 9 18 ]
    /// 	[ 1 3 9 27 ]
    /// 	[ 1 3 12 24 ]
    /// 	[ 1 4 8 16 ]
    /// 	[ 1 4 8 24 ]
    /// 	[ 1 4 12 24 ]
    /// 	[ 1 5 10 20 ]
    /// 	[ 1 6 12 24 ]
    /// 	[ 1 7 14 28 ]
    /// 	[ 2 4 8 16 ]
    /// 	[ 2 4 8 24 ]
    /// 	[ 2 4 12 24 ]
    /// 	[ 2 6 12 24 ]
    /// 	[ 3 6 12 24 ]
    /// which are all combinations for which every element is a divisor of the
    /// next element.
    ///
    /// \param pred should be a *partial predicate*: It takes a *partial*
    /// combination as a parameter and returns either true or false. At the end
    /// only combinations for which every subcombination evaluated to true are
    /// returned (the combination tree is prunned when Pred returns false)
    ///
    ///
    /// \return An forward-iterable object which whose elements are all
    /// combinations which satisfy predicate pred.
    ///
    /////////////////////////////////////////////
    template <class PartialPredicate>
    auto find_all(PartialPredicate pred)
    {
        return CombinationTreePrunned<IntType,
                                      PartialPredicate,
                                      RAContainerInt>(n_, k_, pred);
    }

    template <class Func>
    void for_each(Func f) const
    {
        // I'm really sorry about this. I don't know how to improve the
        // readability without sacrificing speed. If you do, by all means, tell
        // me about it.
        switch (k_)
        {
        case 0:
            detail::combination_tree_helper0<combination>(f, n_);
            break;

        case 1:
            detail::combination_tree_helper1<combination>(f, n_);
            break;

        case 2:
            detail::combination_tree_helper2<combination>(f, n_);
            break;

        case 3:
            detail::combination_tree_helper3<combination>(f, n_);
            break;

        case 4:
            detail::combination_tree_helper4<combination>(f, n_);
            break;

        case 5:
            detail::combination_tree_helper5<combination>(f, n_);
            break;

        case 6:
            detail::combination_tree_helper6<combination>(f, n_);
            break;

        case 7:
            detail::combination_tree_helper7<combination>(f, n_);
            break;

        case 8:
            detail::combination_tree_helper8<combination>(f, n_);
            break;

        case 9:
            detail::combination_tree_helper9<combination>(f, n_);
            break;

        case 10:
            detail::combination_tree_helper10<combination>(f, n_);
            break;

        case 11:
            detail::combination_tree_helper11<combination>(f, n_);
            break;

        case 12:
            detail::combination_tree_helper12<combination>(f, n_);
            break;

        case 13:
            detail::combination_tree_helper13<combination>(f, n_);
            break;

        case 14:
            detail::combination_tree_helper14<combination>(f, n_);
            break;

        case 15:
            detail::combination_tree_helper15<combination>(f, n_);
            break;

        case 16:
            detail::combination_tree_helper16<combination>(f, n_);
            break;

        case 17:
            detail::combination_tree_helper17<combination>(f, n_);
            break;

        case 18:
            detail::combination_tree_helper18<combination>(f, n_);
            break;

        default:
            for (auto& comb : (*this))
            {
                f(comb);
            }

            break;
        }
    }

private:
    IntType n_;
    IntType k_;
    size_type size_;

private:
    template <class P>
    bool augment(combination& comb, P pred, IntType start = 0)
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

    template <class P>
    bool DFSUtil(combination& comb, P pred)
    {
        // 			auto currsize = comb.size();

        if (comb.size() < static_cast<size_t>(k_))
        {
            if (augment(comb, pred))
                return true;
        }

        auto last = comb.back();

        // If it can't be augmented, be it because size is already k or else, we
        // have to start backtracking
        while (!comb.empty())
        {
            last = comb.back();
            comb.pop_back();

            if (augment(comb, pred, last + 1))
                return true;
        }

        return false;
    }

}; // end class CombinationTree

template <class IntType, typename = EnableIfIntegral<IntType>>
auto combination_tree(IntType n, IntType k)
{
    return CombinationTree<IntType>(n, k);
}

template <class Container,
          class IntType,
          typename = EnableIfNotIntegral<Container>>
auto combination_tree(const Container& X, IntType k)
{
    using comb = CombinationTree<IntType>;
    return compound_container<Container, comb>(X, comb(X.size(), k));
}

template <class IntType,
          std::size_t MAX_SIZE = 32,
          typename = EnableIfIntegral<IntType>>
auto combination_tree_stack(IntType n, IntType k)
{
    using boost::container::static_vector;
    return CombinationTree<int, static_vector<int, MAX_SIZE>>(n, k);
}

} // namespace dscr
