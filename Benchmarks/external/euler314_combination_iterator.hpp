// combination_iterator.hpp
//
// Produces all k-combinations of the universe {0,...,n-1} in
// lexicographical order. The algorithm is a tuned-up version
// of a simple generation method ("Algorithm T") described in:
//
//   Knuth, Donald E. 
//   The Art of Computer Programming, Volume 4A: Combinatorial Algorithms, Part 1. 
//   Pearson Education Inc., 2011.

#ifndef COMBINATION_ITERATOR_HPP
#define COMBINATION_ITERATOR_HPP

// This code was produced by Juho Lauri (euler314).

#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

#include <boost/iterator/iterator_facade.hpp>

template <typename T>
class combination_iterator
	: public boost::iterator_facade<
	combination_iterator<T>,
	const std::vector<T>&,
	boost::forward_traversal_tag
	>
{
public:
	combination_iterator() :  comb_() { }

	explicit combination_iterator(T n, T k) : end_(false), n_(n), k_(k), comb_(k)
	{
		assert(k != 0 && n_ > k);
		std::iota(comb_.begin(), comb_.end(), 0);
		assert(!end_);
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		std::int64_t j = k_ - 1;

		for (const T end = n_ - k_; j >= 0 && comb_[j] >= end + j; --j) { }

		if (j < 0)
		{
			assert(comb_.front() == n_ - k_);
			end_ = true;
			return;
		}

		++comb_[j];

		for (const std::int64_t end = k_ - 1; j < end; ++j)
		{
			comb_[j + 1] = comb_[j] + 1;
		}

	}

	bool equal(const combination_iterator& other) const
	{
		return end_ == other.end_;
	}

	const std::vector<T>& dereference() const
	{
		return comb_;
	}

	bool end_{true};
	const int n_{0};
	const int k_{0};
	std::vector<T> comb_;
};


template <typename T>
class combination_iterator_minimax_order
	: public boost::iterator_facade<
	combination_iterator_minimax_order<T>,
	const std::vector<T>&,
	boost::forward_traversal_tag
	>
{
public:
	combination_iterator_minimax_order() :  comb_() { }

	explicit combination_iterator_minimax_order(T n, T k) : end_(false), n_(n), k_(k), hint_(k), comb_(k)
	{
		assert(k != 0 && n_ > k);
		std::iota(comb_.begin(), comb_.end(), 0);
		assert(!end_);
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		//The following code was copied from the discreture library: http://github.com/mraggi/discreture
		if (k_ == 0)
			return;
		
		

		if (hint_ > 0)
		{
			--hint_;
			++comb_[hint_];
			return;
		}
		
		
		T i = 0;
		for (const T last = comb_.size()-1; (i < last) && (comb_[i]+1 == comb_[i+1]); ++i)
		{
			comb_[i] = i;
		}
		
		++comb_[i];
		
		if (comb_[i] == n_)
			end_ = true;
		else
			hint_ = i;
	}

	bool equal(const combination_iterator_minimax_order& other) const
	{
		return end_ == other.end_;
	}

	const std::vector<T>& dereference() const
	{
		return comb_;
	}

	bool end_{true};
	const int n_{0};
	const int k_{0};
	int hint_{};
	std::vector<T> comb_;
};

#endif
