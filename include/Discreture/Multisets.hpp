#pragma once
#include "VectorHelpers.hpp"
#include "Misc.hpp"
#include "NaturalNumber.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace dscr
{
template<class IntType, class RAContainerInt = std::vector<IntType>>
class basic_multisets
{
public:
	using difference_type = long long;
	using size_type = long long;
	using value_type = RAContainerInt;
	using multiset = value_type;

	static void next_multiset(multiset& sub, const multiset& total)
	{
		next_multiset(sub,total,total.size());
	}
	
	static void next_multiset(multiset& sub, const multiset& total, size_t n)
	{
		assert(n == sub.size());
		assert(n == total.size());
		for (size_t i = 0; i < n; ++i)
		{
			if (can_increment(i,sub,total))
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
	
	static void construct_multiset(multiset& sub, const multiset& total, size_type m)
	{
		assert(sub.size() == total.size());
		size_type n = total.size();
		if (n == 0)
			return;
		for (auto& s : sub) s = 0;
		std::vector<size_type> coeffs(n);
		coeffs[0] = 1;
		for (size_type i = 1; i < n; ++i)
		{
			coeffs[i] = coeffs[i-1]*(total[i-1]+1);
		}
		
		for (long i = n-1; i >= 0; --i)
		{
			size_type w = coeffs[i];
			auto t = big_natural_number(total[i]+1).partition_point([m,w](size_type a)
			{
				return a*w <= m;
			}) - 1;
			sub[i] = t;
			m -= w*t;
			if (m <= 0)
				break;
		}
	}
	
	size_type get_index(const multiset& sub) const
	{
		assert(sub.size() == m_total.size());
		size_type coeff = 1;
		size_type result = 0;
		for (size_t i = 0; i < m_total.size(); ++i)
		{
			result += coeff*sub[i];
			coeff *= (m_total[i]+1);
		}
		return result;
	}
	
	////////////////////////////////////////////////////////////
	/// \brief class of all submultisets of a given multiset, expressed as incidence vectors with multiplicities
	/// \param IntType can be an int, short, etc.
	/// # Example:
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
	/// TODO: Make it a random-access class and more like the others. It's not hard.
	///
	////////////////////////////////////////////////////////////
	explicit basic_multisets(const multiset& set) : m_total(set),
	m_size(1)
	{
		for (auto x : set)
		{
			m_size *= (x+1);
		}
	}

	explicit basic_multisets(IntType size, IntType n = 1) : m_total(size, n), m_size(std::pow(n+1,size))
	{
	}

	size_type size() const
	{
		return m_size;
	}

	class iterator : public boost::iterator_facade<
												iterator,
												const multiset&,
												boost::random_access_traversal_tag
												>
	{
	
	public:
		//iterator() : m_submulti(), m_atend(false), m_total(nullptr) {} //empty initializer

		explicit iterator(const multiset& total) : m_ID(0), m_n(total.size()), m_submulti(total.size(), 0), m_total(total)
		{
			
		}

		size_type ID() const
		{
			return m_ID;
		}
		
	private:
		
		iterator(const multiset& total, size_type id) : m_ID(id), m_total(total) {}
		
		//prefix
		void increment()
		{
			++m_ID;
			next_multiset(m_submulti,m_total,m_n);
		}
		
		void decrement()
		{
			--m_ID;
			prev_multiset(m_submulti,m_total,m_n);
		}
		
		const multiset& dereference() const
		{
			return m_submulti;
		}

		//It only makes sense to compare iterators from the SAME multiset.
		bool equal(const iterator& it) const
		{
			return m_ID == it.m_ID;
		}
		
		void advance(difference_type m)
		{
			m_ID += m;
			construct_multiset(m_submulti,m_total,m_ID);
		}
		
		difference_type distance_to(const iterator& it) const
		{
			return it.m_ID - m_ID;
		}
		
	private:
		size_type m_ID{0};
		size_type m_n{0};
		multiset m_submulti {};
		const multiset& m_total;
		
		friend class basic_multisets;
		friend class boost::iterator_core_access;
	};

	iterator begin() const
	{
		return iterator(m_total);
	}

	iterator end() const
	{
		return iterator(m_total,size());
	}
	
	multiset operator[](size_type t) const
	{
		auto w = begin();
		w += t;
		return *w;
	}
	
	class reverse_iterator : 
		public boost::iterator_facade<
					reverse_iterator,
					const multiset&,
					boost::bidirectional_traversal_tag
					>
	{
	
	public:
		explicit reverse_iterator(const multiset& total) : m_ID(0), m_n(total.size()), m_submulti(total), m_total(total)
		{
			
		}

	private:
		
		reverse_iterator(const multiset& total, size_type id) : m_ID(id), m_total(total) {}
		
		//prefix
		void increment()
		{
			++m_ID;
			prev_multiset(m_submulti,m_total,m_n);
		}
		
		void decrement()
		{
			--m_ID;
			next_multiset(m_submulti,m_total,m_n);
		}
		
		const multiset& dereference() const
		{
			return m_submulti;
		}

		//It only makes sense to compare iterators from the SAME multiset.
		bool equal(const reverse_iterator& it) const
		{
			return m_ID == it.m_ID;
		}
		
	private:
		size_type m_ID{0};
		size_type m_n{0};
		multiset m_submulti {};
		const multiset& m_total;
		
		friend class basic_multisets;
		friend class boost::iterator_core_access;
	};

	reverse_iterator rbegin() const
	{
		return reverse_iterator(m_total);
	}

	reverse_iterator rend() const
	{
		return reverse_iterator(m_total,size());
	}
	
private:
	RAContainerInt m_total;
	size_type m_size;
	
	static bool can_increment(size_t index, const multiset& sub, const multiset& total)
	{
		return sub[index] < total[index];
	}
};
using multisets = basic_multisets<int>;
using multisets_fast = basic_multisets<int, boost::container::static_vector<int,48>>;

}
