#pragma once
#include <vector>
#include "Misc.hpp"

namespace  dscr
{

//////////////////////////////////////////
/// \brief Similar to python range(n) or range(n,m) or range(n,m,step).
/// \param n is an integer
/// \return an abstract random-access container whose elements are {n,n+1,n+2,...,m-1}
//////////////////////////////////////////
template <class IntType>
class range
{
public:
	typedef long int difference_type;
	typedef IntType size_type;
	typedef IntType value_type;
public:

	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param n is an integer >= 0
	///
	////////////////////////////////////////////////////////////
	range(IntType n) : m_from(0), m_to(n), m_step(1), m_begin(0), m_end(n)
	{
		m_end.m_ID = m_to;
	}

	range(IntType t_from, IntType t_to, IntType t_step = 1) : 	m_from(t_from),
		m_to(t_to),
		m_step(t_step),
		m_begin(t_from, t_step),
		m_end(t_to + modulo(static_cast<difference_type>(t_from - t_to), static_cast<difference_type>(t_step)))
	{
// 			m_end.m_ID = ;
// 			cout << "m_end = " << *m_end << endl;
// 			cout << "t_to = " << t_to << endl;
// 			cout << "step = " << t_step << endl;
// 			cout << "-7 modulo 4 = " << (-7)%4 << endl;
	}

	size_type size() const
	{
		return m_to - m_from;
	}

	operator std::vector<IntType>() const
	{
		std::vector<IntType> toReturn(begin(), end());
		return toReturn;
	}

	////////////////////////////////////////////////////////////
	/// \brief Random access iterator class.
	////////////////////////////////////////////////////////////
	class iterator : public std::iterator<std::random_access_iterator_tag, std::vector<IntType>> //bidirectional iterator
	{
	public:

		iterator(size_type t_from) : m_step(1), m_ID(t_from) { }

		iterator(size_type t_from, size_type t_step) : m_step(t_step), m_ID(t_from) { }

		//prefix
		inline iterator& operator++()
		{
			m_ID += m_step;

			return *this;
		}

		inline iterator& operator--()
		{
			m_ID -= m_step;

			return *this;
		}

		inline const IntType& operator*() const
		{
			return m_ID;
		}

		////////////////////////////////////////
		///
		/// \brief Random access capabilities to the iterators
		/// \param n -> This assumes 0 <= n+ID <= size(n)
		///
		////////////////////////////////////////
		inline iterator& operator+=(long int n)
		{
			m_ID += n;
			return *this;
		}

		inline iterator& operator-=(long int n)
		{
			return operator+=(-n);
		}

		inline bool operator==(const iterator& it)
		{
			return *it == m_ID;
		}

		inline bool operator!=(const iterator& it)
		{
			return *it != m_ID;
		}

		inline difference_type operator-(const iterator& it)
		{
			return abs((static_cast<difference_type>(m_ID) - *it)) / m_step;
		}

		size_type step() const
		{
			return m_step;
		}
	private:
		size_type m_step {1};
		size_type m_ID {0} ;


		friend class range;
	}; // end class iterator



	const iterator& begin() const
	{
		return m_begin;
	}

	const iterator& end() const
	{
		return m_end;
	}


	IntType operator[](size_type m) const
	{
		return m_from + m_step * m;
	}

private:
	IntType m_from;
	IntType m_to;
	IntType m_step;
	iterator m_begin;
	iterator m_end;
}; // end class range

template <class IntType>
inline typename range<IntType>::iterator operator+(typename range<IntType>::iterator it, long int n)
{
	it += n;
	return it;
}

template <class IntType>
inline typename range<IntType>::iterator operator-(typename range<IntType>::iterator it, long int n)
{
	it -= n;
	return it;
}

template <class T>
void overwrite(std::vector<T>& lhs, range<T> rhs)
{
	size_t n = rhs.size();
	lhs.resize(n);

	for (size_t i = 0; i < n; ++i)
		lhs[i] = rhs[i];
}

} // end namespace dscr;
