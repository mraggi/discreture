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
private:
	RAContainerInt m_total;
public:

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
	basic_multisets(const multiset& set) : m_total(set), m_begin(m_total), m_end(m_total)
	{
		m_end.m_atend = true;
	}



	basic_multisets(IntType size, IntType n = 1) : m_total(size, n), m_begin(m_total), m_end(m_total)
	{
		m_end.m_atend = true;
	}

	size_type size() const
	{
		size_type toReturn = 1;

		for (auto x : m_total)
			toReturn *= (x + 1);

		return toReturn;
	}

	class iterator :  public boost::iterator_facade<
													iterator,
													const multiset&,
													boost::forward_traversal_tag
													>
	{
	
	public:
		//iterator() : m_submulti(), m_atend(false), m_total(nullptr) {} //empty initializer

		iterator(const multiset& total) : m_submulti(total.size(), 0), m_atend(false), m_total(total)
		{
			//how it starts
		}

	private:

		//prefix
		void increment()
		{
			for (size_t i = 0; i < m_submulti.size(); ++i)
			{
				if (m_submulti[i] + 1 <= m_total[i])
				{
					++m_submulti[i];

					return;
				}
				m_submulti[i] = 0;
			}

			m_atend = true;
		}

		
		const multiset& dereference() const
		{
			return m_submulti;
		}

		bool equal(const iterator& it) const
		{
			if (it.m_atend)
			{
				return m_atend;
			}
// 				std::cout << "should not run!" << endl;
			if (m_submulti.size() != it.m_submulti.size())
				return false;

			for (size_t i = 0; i < m_submulti.size(); ++i)
			{
				if (m_submulti[i] != (*it)[i])
					return false;
			}

			return true;
		}

		
	private:
		multiset m_submulti;
		bool m_atend;
		const multiset& m_total;
		
		friend class basic_multisets;
		friend class boost::iterator_core_access;
	};

	const iterator& begin() const
	{
		return m_begin;
	}

	const iterator& end() const
	{
		return m_end;
	}

private:
	iterator m_begin;
	iterator m_end;
	
	

};
using multisets = basic_multisets<int>;
using multisets_fast = basic_multisets<int, boost::container::static_vector<int,48>>;

}
