#pragma once

#include "CombinationsTree.hpp"

namespace dscr
{
template <class IntType, class Predicate>
class basic_combinations_tree_prunned
{
public:

	typedef long long int difference_type;
	typedef unsigned long long int size_type;
	typedef std::vector<IntType> value_type;
	typedef std::vector<IntType> combination;

	//Declarations.
	class iterator;

public:

	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param n is an integer >= 0
	/// \param k is an integer with 0 <= k <= n
	/// \param p is a partial predicate (unary function or functor) that takes as input a partial combination and returns either true or false.
	///
	////////////////////////////////////////////////////////////
	basic_combinations_tree_prunned(IntType n, IntType k, Predicate p) : m_n(n), m_k(k),  m_begin(m_n, m_k, p), m_end(p, true), m_pred(p)
	{
// 			cout << "In constructor" << endl;
	}

	IntType get_n() const
	{
		return m_n;
	}
	IntType get_k() const
	{
		return m_k;
	}


	////////////////////////////////////////////////////////////
	/// \brief Forward iterator for constructing combinations that satisfy a certain predicate one by one
	////////////////////////////////////////////////////////////
	class iterator : public std::iterator<std::forward_iterator_tag, std::vector<IntType>>
	{
	public:
		iterator(Predicate p, bool last) : m_ID(0), m_data(), m_atEnd(last), m_pred(p) {} //empty initializer
	public:
		iterator(IntType n, IntType r, Predicate p) : m_ID(0), m_n(n), m_k(r), m_data(), m_atEnd(false), m_pred(p)
		{
			m_data.reserve(m_k);

			while (DFSUtil(m_data, m_pred, m_n, m_k))
			{
				if (m_data.size() == static_cast<size_t>(m_k))
				{
					return;
				}
			}

			m_atEnd = true;
		}

		//prefix
		inline iterator& operator++()
		{
// 				cout << "size of pred: " << sizeof(m_pred) << endl;
			while (DFSUtil(m_data, m_pred, m_n, m_k))
			{
				if (m_data.size() == static_cast<size_t>(m_k))
					return *this;
			}

			m_atEnd = true;
			return *this;
		}

		inline const std::vector<IntType>& operator*() const
		{
			return m_data;
		}

		inline const combination* operator->() const
		{
			return & operator*();
		}

		inline size_type ID() const
		{
			return m_ID;
		}

		inline bool operator==(const iterator& it) const
		{
			if (m_atEnd != it.m_atEnd)
				return false;

			if (m_atEnd)
				return true;

			return m_data == it.m_data;
		}

		inline bool operator!=(const iterator& it) const
		{
			if (m_atEnd != it.m_atEnd)
				return true;

			if (m_atEnd)
				return false;

			return m_data != it.m_data;
		}

		inline bool is_at_end(IntType n) const
		{
			return m_atEnd;
		}

	private:
		size_type m_ID {0};
		IntType m_n;
		IntType m_k;
		combination m_data;
		bool m_atEnd;
		Predicate m_pred;

		friend class basic_combinations_tree_prunned;
	}; // end class iterator

	const iterator& begin() const
	{
		return m_begin;
	}

	const iterator& end() const
	{
		return m_end;
	}


private:
	IntType m_n;
	IntType m_k;
	iterator m_begin;
	iterator m_end;
	Predicate m_pred;

	static bool augment(combination& comb, Predicate pred, IntType m_n, IntType m_k, IntType start = 0)
	{
		if (comb.empty())
		{
			if (start < m_n - m_k + 1)
			{
				comb.push_back(start);
				return true;
			}
			else
			{
				return false;
			}
		}

		auto last = comb.back();
		auto guysleft = m_k - comb.size();

		start = std::max(last + 1, start);

		for (size_t i = start; i < m_n - guysleft + 1; ++i)
		{
			comb.push_back(i);

			if (pred(comb))
				return true;

			comb.pop_back();
		}

		return false;
	}

	static bool DFSUtil(combination& comb, Predicate pred, IntType m_n, IntType m_k)
	{
// 			cout << "n,k = " << m_n << " " << m_k << endl;
		if (comb.size() < static_cast<size_t>(m_k))
		{
			if (augment(comb, pred, m_n, m_k))
				return true;
		}

		auto last = comb.back();

		// If it can't be augmented, be it because size is already k or else, we have to start backtracking
		while (!comb.empty())
		{
			last = comb.back();
			comb.pop_back();

			if (augment(comb, pred, m_n, m_k, last + 1))
				return true;
		}

		return false;
	}

}; // end class basic_combinations_tree_prunned

// 	using combinations_tree_prunned = basic_combinations_tree_prunned<int>;
};
