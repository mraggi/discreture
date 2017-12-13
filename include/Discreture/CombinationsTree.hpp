#pragma once

#include "VectorHelpers.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "Range.hpp"
#include "combinations_tree_bf.hpp"
#include "CombinationsTreePrunned.hpp"
#include <numeric>
#include <algorithm>

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

	using difference_type = long long;
	using size_type = long long;
	using value_type = std::vector<IntType>;
	using combination = std::vector<IntType>;

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
				long t = data[i];
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
		if (data.empty())
			return;
		IntType a = n-1;
		for (long i = data.size()-1; i > 0L; --i,--a)
		{
			if (data[i]-1 != data[i-1])
			{
				--data[i];
				return;
			} 
			data[i] = a;
		}
		--data[0];
	}

	static size_type get_index(const combination& comb, IntType n) //needs n
	{
		size_type k = comb.size();

		size_type result = 0;

		for (difference_type i = 0; i < k; ++i)
			result += binomial(n - comb[k - i - 1] - 1, i + 1);

		return binomial(n, k) - result - 1;
	}
	
	size_type get_index(const combination& comb) const
	{
		return get_index(comb,m_n);
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
	basic_combinations_tree(IntType n, IntType k) : m_n(n), m_k(k), m_size(binomial(n,k))
	{
	}

	////////////////////////////////////////////////////////////
	/// \brief The total number of combinations
	///
	/// \return binomial(n,r)
	///
	////////////////////////////////////////////////////////////
	size_type size() const
	{
		return m_size;
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
		iterator() : m_ID(0LL), m_data() {} //empty initializer
		iterator(const combination& comb, IntType n) : m_ID(basic_combinations_tree<IntType>::get_index(comb,n)), m_data(comb) {} //empty initializer
	private:
		explicit iterator(size_type id) : m_ID(id), m_data() {} //ending initializer: for id only. Do not use unless you know what you are doing.
	public:
		iterator(IntType n, IntType k) : m_ID(0), m_n(n), m_data(k)
		{
			std::iota(m_data.begin(), m_data.end(), 0);
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
			if (abs(n) < 15)
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

		void reset(IntType n, IntType k)
		{
			m_ID = 0;
			m_data.resize(k);
			std::iota(m_data.begin(),m_data.end(),0);
		}

	private:
		size_type m_ID {0};
		IntType m_n;
		combination m_data;

		friend class basic_combinations_tree;
	}; // end class iterator

	iterator get_iterator(const combination& comb)
	{
		return iterator(comb,m_n);
	}

	////////////////////////////////////////////////////////////
	/// \brief Reverse random access iterator class. It's much more efficient as a bidirectional iterator than purely random access.
	////////////////////////////////////////////////////////////
	class reverse_iterator : public std::iterator<std::random_access_iterator_tag, std::vector<IntType>> //bidirectional iterator
	{
	public:
		reverse_iterator() : m_n(0), m_ID(0), m_data() {} //empty initializer
	private:
		explicit reverse_iterator(size_type id) : m_ID(id), m_data() {} //ending initializer: for id only. Do not use unless you know what you are doing.
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

	iterator begin() const
	{
		return iterator(m_n,m_k);
	}

	iterator end() const
	{
		return iterator(size());
	}

	reverse_iterator rbegin() const
	{
		return reverse_iterator(m_n,m_k);
	}

	reverse_iterator rend() const
	{
		return reverse_iterator(size());
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
	
	///////////////////////////////////////////////
	/// \brief This is an efficient way to construct a combination of size k which fully satisfies a predicate
	///
	/// This function is conceptually equivalent to std::find_if(begin(), end(), Pred),
	/// but much faster if the predicate can be evaluated on a partial combination (so as to prune the search tree)
	///
	/// # Example:
	///
	/// 	combinations X(40,6);
	/// 	auto it = X.find_if([](const std::vector<int>& comb) -> bool
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
	/// \param Pred should be what we call a *partial predicate*: It takes a combination as a parameter and returns either true or false.
	///
	///
	/// \return An interator to a combination which fully satisfies the predicate.
	///
	/////////////////////////////////////////////
	template<class PartialPredicate>
	iterator find_if(PartialPredicate pred)
	{
		combination A;
		A.reserve(m_k);

		while (DFSUtil(A, pred))
		{
			if (A.size() == static_cast<size_t>(m_k))
				return get_iterator(A);
		}

		return end();
	}
	
	///////////////////////////////////////////////
	/// \brief This is an efficient way to construct all combination of size k which fully satisfy a predicate
	///
	/// This function is similar to find_if, but it returns an object for which you can iterate over all combinations which satisfy Predicate pred,
	///
	/// # Example:
	///
	/// 	combinations X(30,4);
	/// 	auto vall = X.find_all([](const std::vector<int>& comb) -> bool
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
	/// which are all combinations for which every element is a divisor of the next element.
	///
	/// \param pred should be a *partial predicate*: It takes a *partial* combination as a parameter and returns either true or false. At the end only combinations for which every subcombination evaluated to true are returned (the combination tree is prunned when Pred returns false)
	///
	///
	/// \return An forward-iterable object which whose elements are all combinations which satisfy predicate pred.
	///
	///
	/////////////////////////////////////////////
	template<class PartialPredicate>
	basic_combinations_tree_prunned<IntType, PartialPredicate> find_all(PartialPredicate pred)
	{
		basic_combinations_tree_prunned<IntType, PartialPredicate> X(m_n, m_k, pred);
		return X;
	}
	
	template <class Func>
	void for_each(Func f) const
	{
		//I'm really sorry about this. I don't know how to improve the readability without sacrificing speed. If you do, by all means, tell me about it.
		switch (m_k)
		{
		case 0:
			detail::combination_tree_helper0(f,m_n);
			break;

		case 1:
			detail::combination_tree_helper1(f,m_n);
			break;

		case 2:
			detail::combination_tree_helper2(f,m_n);
			break;

		case 3:
			detail::combination_tree_helper3(f,m_n);
			break;

		case 4:
			detail::combination_tree_helper4(f,m_n);
			break;

		case 5:
			detail::combination_tree_helper5(f,m_n);
			break;

		case 6:
			detail::combination_tree_helper6(f,m_n);
			break;

		case 7:
			detail::combination_tree_helper7(f,m_n);
			break;

		case 8:
			detail::combination_tree_helper8(f,m_n);
			break;

		case 9:
			detail::combination_tree_helper9(f,m_n);
			break;

		case 10:
			detail::combination_tree_helper10(f,m_n);
			break;

		case 11:
			detail::combination_tree_helper11(f,m_n);
			break;

		case 12:
			detail::combination_tree_helper12(f,m_n);
			break;

		case 13:
			detail::combination_tree_helper13(f,m_n);
			break;

		case 14:
			detail::combination_tree_helper14(f,m_n);
			break;

		case 15:
			detail::combination_tree_helper15(f,m_n);
			break;

		case 16:
			detail::combination_tree_helper16(f,m_n);
			break;
			
		case 17:
			detail::combination_tree_helper17(f,m_n);
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
	IntType m_n;
	IntType m_k;
	size_type m_size;

	
	template <class P>
	bool augment(combination& comb, P pred, IntType start = 0)
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

		start = std::max(static_cast<IntType>(last + 1), start);

		for (size_t i = start; i < m_n - guysleft + 1; ++i)
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

		if (comb.size() < static_cast<size_t>(m_k))
		{
			if (augment(comb, pred))
				return true;
		}

		auto last = comb.back();

		// If it can't be augmented, be it because size is already k or else, we have to start backtracking
		while (!comb.empty())
		{
			last = comb.back();
			comb.pop_back();

			if (augment(comb, pred, last + 1))
				return true;
		}

		return false;
	}
	
}; // end class basic_combinations_tree

using combinations_tree = basic_combinations_tree<int>;


} // end namespace dscr;




