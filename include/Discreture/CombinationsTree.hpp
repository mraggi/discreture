#pragma once

#include "VectorHelpers.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "Range.hpp"

namespace dscr
{

////////////////////////////////////////////////////////////
/// \brief class of all n choose k combinations of size k of the set {0,1,...,n-1} in lexicographic order
/// \param IntType should be an integral type with enough space to store n and k. It can be signed or unsigned.
/// \param n the size of the set
/// \param k the size of the combination (subset). Should be an integer such that n choose k is not bigger than the largest unsigned long int there is. For example, 50 choose 25 is already larger than the largest long long unsigned int.
/// # Example:
///
///		combinations_tree X(6,3);
///		for (const auto& x : X)
///			cout << x << " ";
///
/// Prints out:
///
/// 	[ 0 1 2 ] [ 0 1 3 ] [ 0 1 4 ] [ 0 1 5 ] [ 0 2 3 ] [ 0 2 4 ] [ 0 2 5 ] [ 0 3 4 ] [ 0 3 5 ] [ 0 4 5 ] [ 1 2 3 ] [ 1 2 4 ] [ 1 2 5 ] [ 1 3 4 ] [ 1 3 5 ] [ 1 4 5 ] [ 2 3 4 ] [ 2 3 5 ] [ 2 4 5 ] [ 3 4 5 ]
///
////////////////////////////////////////////////////////////
template <class IntType>
class basic_combinations_tree
{
public:

	typedef long long int difference_type;
	typedef unsigned long long int size_type;
	typedef std::vector<IntType> value_type;
	typedef std::vector<IntType> combination;

	//Declarations.
	class iterator;

	// **************** Begin functions
	static inline void next_combination(combination& data, IntType n)
	{
		if (data.empty())
			return;

		long k = data.size();

		if (k == 0)
			return;


		for (long i = k - 1; i >= 0; --i)
		{
			if (data[i] != n - k + i)
			{
				++data[i];
				IntType t = data[i];
				for (long j = 1; i+j < k; ++j)
				{
					data[i+j] = t + j;
				}

				return;
			}
		}
	}

	static inline void prev_combination(combination& data, IntType n)
	{
		IntType k = data.size();

// 			IntType i = 0;
		if (k == 0)
			return;

		if (k == 1)
		{
			if (data[0] > 0)
				--data[0];

			return;
		}

		if (data[k - 1] != data[k - 2] + 1)
		{
			--data[k - 1];
			return;
		}

		for (int i = 0; i + 1 < k; ++i)
		{
			if (data[i] + k - i - 1 == data.back())
			{
				--data[i];

				for (int j = i + 1; j < k; ++j)
				{
					data[j] = n - (k - j);
				}

				return;
			}
		}

		--data[0];
	}

	size_type get_index(const combination& comb) const
	{
		size_type k = comb.size();

		size_type result = 0;

		for (difference_type i = 0; i < k; ++i)
			result += binomial(m_n - comb[k - i - 1] - 1, i + 1);

		return binomial(m_n, k) - result - 1;
	}

	static void construct_combination(combination& data, size_type m, IntType m_n)
	{
		IntType k = data.size();
		m = binomial(m_n, k) - m - 1;

		for (IntType i = 0; i < k; ++i)
		{
			IntType r = k - i;
			IntType first = r;

			while (binomial(first, r) <= m)
			{
				++first;
			}

			--first;

			data[k - (r - 1) - 1] = m_n - first - 1;
			m -= binomial(first, r);
		}

// 			cout << "data = " << data << endl;
	}

	///////////////////////////////////////
	/// \brief Combination comparison "less than" operator. Assumes lhs and rhs have the same size.
	/// \return true if lhs would appear before rhs in the iteration order, false otherwise
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
	basic_combinations_tree(IntType n, IntType k) : m_n(n), m_k(k), m_begin(n, k), m_end(), m_rbegin(n, k),  m_rend()
	{
		m_end.m_ID = size();
		m_rend.m_ID = size();
	}

	////////////////////////////////////////////////////////////
	/// \brief The total number of combinations
	///
	/// \return binomial(n,r)
	///
	////////////////////////////////////////////////////////////
	size_type size() const
	{
		return binomial(m_n, m_k);
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
	/// \brief Random access iterator class. It's much more efficient as a bidirectional iterator than purely random access.
	////////////////////////////////////////////////////////////
	class iterator : public std::iterator<std::random_access_iterator_tag, std::vector<IntType>>
	{
	public:
		iterator() : m_ID(0), m_data() {} //empty initializer
		iterator(const combination& comb) : m_ID(get_index(comb)), m_data(comb) {} //empty initializer
	private:
		explicit iterator(IntType id) : m_ID(id), m_data() {} //ending initializer: for id only. Do not use unless you know what you are doing.
	public:
		iterator(IntType n, IntType r) : m_ID(0), m_n(n), m_data(range<IntType>(r))
		{
		}

		//prefix
		inline iterator& operator++()
		{
			++m_ID;

			next_combination(m_data, m_n);

			return *this;
		}

		inline iterator& operator--()
		{

			if (m_ID == 0)
				return *this;

			--m_ID;

			prev_combination(m_data, m_n);

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

		////////////////////////////////////////
		///
		/// \brief Random access capabilities to the iterators
		/// \param n -> This assumes 0 <= n+ID <= size(n,k)
		///
		////////////////////////////////////////
		inline iterator& operator+=(difference_type n)
		{
			assert(0 <= n + m_ID);

			// If n is small, it's actually more efficient to just iterate to it
			if (abs(n) < 20)
			{
				while (n > 0)
				{
					operator++();
					--n;
				}

				while (n < 0)
				{
					operator--();
					++n;
				}

				return *this;
			}

			// If n is large, then it's better to just construct it from scratch.
			m_ID += n;
			construct_combination(m_data, m_ID, m_n);
			return *this;
		}

		inline iterator& operator-=(difference_type n)
		{
			return operator+=(-n);
		}

		friend iterator operator+(iterator lhs, difference_type  n)
		{
			lhs += n;
			return lhs;
		}

		friend iterator operator-(iterator lhs, difference_type  n)
		{
			lhs -= n;
			return lhs;
		}
		friend difference_type operator-(const iterator& lhs, const iterator& rhs)
		{
			return static_cast<difference_type>(lhs.ID()) - rhs.ID();
		}

		inline size_type ID() const
		{
			return m_ID;
		}

		inline bool operator==(const iterator& it) const
		{
			return it.ID() == ID();
		}

		inline bool operator!=(const iterator& it) const
		{
			return it.ID() != ID();
		}

		inline bool is_at_end(IntType n) const
		{
			return m_ID == binomial(n, m_data.size());
		}

		void reset(IntType n, IntType r)
		{
			m_ID = 0;
			overwrite(m_data, range<IntType>(r));
		}

	private:
		size_type m_ID {0};
		IntType m_n;
		combination m_data;

		friend class basic_combinations_tree;
	}; // end class iterator

	iterator get_iterator(const combination& comb)
	{
		return iterator(comb);
	}

	////////////////////////////////////////////////////////////
	/// \brief Reverse random access iterator class. It's much more efficient as a bidirectional iterator than purely random access.
	////////////////////////////////////////////////////////////
	class reverse_iterator : public std::iterator<std::random_access_iterator_tag, std::vector<IntType>> //bidirectional iterator
	{
	public:
		reverse_iterator() : m_n(0), m_ID(0), m_data() {} //empty initializer
	private:
		explicit reverse_iterator(IntType id) : m_ID(id), m_data() {} //ending initializer: for id only. Do not use unless you know what you are doing.
	public:
		reverse_iterator(IntType n, IntType r) : m_n(n), m_ID(0), m_data(range<IntType>(n - r, n))
		{
		}

		//prefix
		inline reverse_iterator& operator++()
		{
			++m_ID;

			prev_combination(m_data, m_n);

			return *this;
		}

		inline reverse_iterator& operator--()
		{
			assert(m_ID != 0);

			--m_ID;

			next_combination(m_data);

			return *this;
		}

		inline const combination& operator*()
		{
			return m_data;
		}

		inline const combination& operator*() const
		{
			return m_data;
		}

		inline const combination* operator->() const
		{
			return & operator*();
		}

		////////////////////////////////////////
		///
		/// \brief Random access capabilities to the iterators
		/// \param m -> This assumes 0 <= m+ID <= size(m,k)
		///
		////////////////////////////////////////
		inline reverse_iterator& operator+=(difference_type m)
		{
			assert(0 <= m + m_ID);

			if (abs(m) < 20)
			{
				while (m > 0)
				{
					operator++();
					--m;
				}

				while (m < 0)
				{
					operator--();
					++m;
				}

				return *this;
			}

			m_ID += m;
			auto num = binomial(m_n, m_data.size()) - m_ID - 1;
			// If n is large, then it's better to just construct it from scratch.
			construct_combination(m_data, num);
			return *this;

		}

		inline reverse_iterator& operator-=(difference_type n)
		{
			return operator+=(-n);
		}


		friend reverse_iterator operator+(reverse_iterator lhs, difference_type  n)
		{
			lhs += n;
			return lhs;
		}

		friend reverse_iterator operator-(reverse_iterator lhs, difference_type  n)
		{
			lhs -= n;
			return lhs;
		}
		friend difference_type operator-(const reverse_iterator& lhs, const reverse_iterator& rhs)
		{
			return static_cast<difference_type>(lhs.ID()) - rhs.ID();
		}

		inline size_type ID() const
		{
			return m_ID;
		}

		inline bool operator==(const reverse_iterator& it)
		{
			return it.ID() == ID();
		}

		inline bool operator!=(const reverse_iterator& it)
		{
			return it.ID() != ID();
		}

		inline bool is_at_end() const
		{
			return m_ID == binomial(m_n, m_data.size());;
		}

		void reset(IntType n, IntType r)
		{
			m_n = n;
			m_ID = 0;
			m_data = range<IntType>(n - r, n);
		}
	private:
		IntType m_n;
		size_type m_ID;
		combination m_data;

		friend class basic_combinations_tree;
	}; // end class iterator

	const iterator& begin() const
	{
		return m_begin;
	}

	const iterator& end() const
	{
		return m_end;
	}

	const reverse_iterator& rbegin() const
	{
		return m_rbegin;
	}

	const reverse_iterator& rend() const
	{
		return m_rend;
	}


	////////////////////////////////////////////////////////////
	/// \brief Access to the m-th combination (slow for iteration)
	///
	/// This is equivalent to calling *(begin()+m)
	/// \param m should be an integer between 0 and size(). Undefined behavior otherwise.
	/// \return The m-th combination, as defined in the order of iteration (lexicographic)
	////////////////////////////////////////////////////////////
	combination operator[](size_type m) const
	{
		auto it = begin();
		it += m;
		return *it;
	}

private:
	IntType m_n;
	IntType m_k;
	iterator m_begin;
	iterator m_end;
	reverse_iterator m_rbegin;
	reverse_iterator m_rend;

}; // end class basic_combinations_tree

using combinations_tree = basic_combinations_tree<int>;


} // end namespace dscr;




