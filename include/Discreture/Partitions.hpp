#pragma once

#include "VectorHelpers.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "NumberRange.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace dscr
{

////////////////////////////////////////////////////////////
/// \brief class of partitions of the number n.
/// \param IntType should be an integral type with enough space to store n and k. It can be signed or unsigned.
/// # Example:
///
///	 partitions X(6);
///		for (auto& x : X)
///			cout << x << ' ';
///
/// Prints out:
///
/// 	[ 1 1 1 1 1 1 ] [ 2 1 1 1 1 ] [ 3 1 1 1 ] [ 2 2 1 1 ] [ 4 1 1 ] [ 3 2 1 ] [ 2 2 2 ] [ 5 1 ] [ 4 2 ] [ 3 3 ] [ 6 ]
////////////////////////////////////////////////////////////
template <class IntType>
class basic_partitions
{
public:

	using difference_type = long long;
	using size_type = long long;
	using value_type = std::vector<IntType>;
	using partition = value_type;

	//Declarations.
	class iterator;


	// **************** Begin static functions
	static void next_partition(partition& data, IntType n)
	{
		size_t t = data.size();

		if (t < 2) //At END
		{
			return;
		}

		if (data.front() - data.back() < 2) // We must change size!
		{
			first_with_given_number_of_parts(data, n, t - 1);
			return;
		}

		// If no size change is necessary

		// Starting from the end, we look at the first whose difference is at least 2 in order to transfer one unit from to the first possible.
		IntType menor = data.back();
		IntType suma = menor;

		for (difference_type i = t - 2; i > -1; --i)
		{
			suma += data[i];

			if (data[i] - menor < 2)
				continue;

			suma -= data[i];


			--data[i];
			//cout << "Le decidí bajar al " << i << " que ahora vale " << data[i] << endl;

			++suma;

			size_t numespacios = t - i - 1;
			difference_type exceso = suma - numespacios;


			for (size_t j = i + 1; j < t; ++j)
			{
				if (exceso <= 0)
				{
					data[j] = 1;
					continue;
				}

				if (exceso + 1 >= data[i])
				{
					data[j] = data[i];

					exceso -= difference_type(data[j] - 1);

					continue;
				}

				data[j] = 1 + exceso;
				exceso = 0;
			}

			return;
		}
	}

	static void first_with_given_number_of_parts(partition& data, IntType n, IntType k)
	{
		if (n == 0)
		{
			data.clear();
			return;
		}

		data.resize(k);
		data[0] = n - k + 1;

		for (size_t i = 1; i < k; ++i)
			data[i] = 1;
	}

	static partition conjugate(const partition& P)
	{
		assert(!P.empty());
		partition result(P[0], 1);
		auto n = P.size();

		result[0] = n;

		for (size_t i = 1; i < n; ++i)
		{
			auto t = std::lower_bound(P.begin(), P.end(), i, std::greater<IntType>());

			int r = t - P.begin();

			if (r > 0)
				result[i] = r;
		}

		return result;
	}

	// **************** End static functions

public:

	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param n is an integer >= 0
	///
	////////////////////////////////////////////////////////////
	basic_partitions(IntType n) : m_n(n), m_minnumparts(1), m_maxnumparts(n), m_begin(n, n), m_end()
	{
		m_end.m_ID = size();
	}

	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param n is an integer >= 0
	/// \param numparts is an integer >= 1 and <= n
	///
	////////////////////////////////////////////////////////////
	basic_partitions(IntType n, IntType numparts) : m_n(n), m_minnumparts(numparts), m_maxnumparts(numparts), m_begin(n, numparts), m_end()
	{
		m_end.m_ID = size();
	}

	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param n is an integer >= 0
	/// \param minnumparts is an integer >= 1 and <= n
	/// \param maxnumparts is an integer >= minnumparts and <= n
	///
	////////////////////////////////////////////////////////////
	basic_partitions(IntType n, IntType minnumparts, IntType maxnumparts) : m_n(n), m_minnumparts(minnumparts), m_maxnumparts(maxnumparts), m_begin(n, maxnumparts), m_end()
	{
		m_end.m_ID = size();
	}


	////////////////////////////////////////////////////////////
	/// \brief The total number of partitions
	///
	/// \return p_n
	///
	////////////////////////////////////////////////////////////
	size_type size() const
	{
		if (m_minnumparts == 1 && m_maxnumparts == m_n)
			return partition_number(m_n);

		size_type toReturn = 0;

		for (size_t k = m_minnumparts; k <= m_maxnumparts; ++k)
			toReturn += partition_number(m_n, k);

		return toReturn;
	}

	IntType get_n() const
	{
		return m_n;
	}

	////////////////////////////////////////////////////////////
	/// \brief Forward iterator class.
	////////////////////////////////////////////////////////////
	class iterator :  public boost::iterator_facade<
													iterator,
													const partition&,
													boost::forward_traversal_tag
													>
	{
	public:
		iterator() : m_ID(0), m_data(), m_n(0) {}

		explicit iterator(IntType n, IntType numparts) : m_ID(0), m_data(), m_n(n)
		{
			first_with_given_number_of_parts(m_data, n, numparts);
		}
		
		inline size_type ID() const
		{
			return m_ID;
		}
		
		//boost::iterator_facade provides all the public interface you need, like ++, etc.
		
	private:
		void increment()
		{
			++m_ID;

			next_partition(m_data, m_n);
		}
		
		const partition& dereference() const
		{
			return m_data;
		}
		
		bool equal(const iterator& it) const
		{
			return it.ID() == ID();
		}
		
		difference_type distance_to(const iterator& lhs) const
		{
			return static_cast<difference_type>(lhs.ID()) - ID();
		}

	private:
		size_type m_ID;
		partition m_data;
		IntType m_n;

		friend class boost::iterator_core_access;
		friend class basic_partitions;
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
	IntType m_minnumparts;
	IntType m_maxnumparts;
	iterator m_begin;
	iterator m_end;

}; // end class basic_partitions

using partitions = basic_partitions<int>;

}// end namespace dscr;
