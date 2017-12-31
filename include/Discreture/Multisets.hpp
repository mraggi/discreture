#pragma once
#include "VectorHelpers.hpp"
#include "Misc.hpp"
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
	basic_multisets(const multiset& set) : m_total(set),
	m_size(1)
	{
		for (auto x : set)
		{
			m_size *= (x+1);
		}
	}

	basic_multisets(IntType size, IntType n = 1) : m_total(size, n), m_size(std::pow(n+1,size))
	{
	}

	size_type size() const
	{
		return m_size;
	}

	struct end_iterator
	{
		end_iterator(size_type id) : m_ID(id) {}
		size_type m_ID;
	};
	
	class iterator :  public boost::iterator_facade<
													iterator,
													const multiset&,
													boost::forward_traversal_tag
													>
	{
	
	public:
		//iterator() : m_submulti(), m_atend(false), m_total(nullptr) {} //empty initializer

		iterator(const multiset& total) : m_ID(0), m_n(total.size()), m_submulti(total.size(), 0), m_total(total)
		{
			
		}

	private:
		
		iterator(const multiset& total, size_type id) : m_ID(id), m_total(total) {}

		bool can_increment(size_t index)
		{
			return m_submulti[index] + 1 <= m_total[index];
		}
		
		//prefix
		void increment()
		{
			++m_ID;
			if (m_n <= 0)
				return;
			
			for (size_t i = 0; i < m_n; ++i)
			{
				if (can_increment(i))
				{
					++m_submulti[i];

					return;
				}
				m_submulti[i] = 0;
			}
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
private:
	RAContainerInt m_total;
	size_type m_size;
};
using multisets = basic_multisets<int>;
using multisets_fast = basic_multisets<int, boost::container::static_vector<int,48>>;

}
