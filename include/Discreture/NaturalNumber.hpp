#pragma once
#include "Misc.hpp"
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <cassert>
#include <vector>

namespace  dscr
{

//////////////////////////////////////////
/// \brief In set theory, a common way of defining a natural number is. n := {0,1,2,...,n-1}, with 0 = {}.
//////////////////////////////////////////
template <class IntType>
class basic_natural_number
{
public:
	using value_type = IntType;
	using difference_type = long long; //NOLINT
	using size_type = difference_type;
	class iterator;
	using const_iterator = iterator;

public:

	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param n is an integer >= 0
	///
	////////////////////////////////////////////////////////////
	explicit basic_natural_number(IntType n) : m_n(n)
	{
		assert(n >= 0);
	}

	size_type size() const
	{
		return m_n;
	}

	////////////////////////////////////////////////////////////
	/// \brief Random access iterator class.
	////////////////////////////////////////////////////////////
	class iterator : public boost::iterator_facade<
													iterator,
													const IntType&,
													boost::random_access_traversal_tag
													>
	{
	public:

		explicit iterator(IntType t=0) : m_ID(t) { }
				
	private:
		void increment()
		{
			++m_ID;
		}
		
		void decrement()
		{
			--m_ID;
		}
		
		const IntType& dereference() const
		{
			return m_ID;
		}
		
		void advance(difference_type n)
		{
			m_ID += n;
		}

		bool equal(const iterator& it) const
		{
			return m_ID == it.m_ID;
		}
		
		difference_type distance_to(const iterator& it) const
		{
			return (static_cast<difference_type>(it.m_ID) -
					static_cast<difference_type>(m_ID));
		}

	private:
		IntType m_ID {0};

		friend class boost::iterator_core_access;
		friend class basic_natural_number;
	}; // end class iterator



	iterator begin() const
	{
		return iterator(0);
	}

	iterator end() const
	{
		return iterator(m_n);
	}


	IntType operator[](size_type m) const
	{
		return m;
	}

	template <class Pred>
	IntType partition_point(Pred p)
	{
		return *std::partition_point(begin(), end(), p);
	}
	
private:
	IntType m_n;
}; // end class basic_natural_number

using natural_number = basic_natural_number<int>;
using big_natural_number = basic_natural_number<long long>; //NOLINT

template <class Container, class T = typename Container::size_type>
basic_natural_number<T> indices(const Container& C)
{
	return basic_natural_number<T>(C.size());
}

//TODO(mraggi): zip and enumerate.

}  // namespace dscr
