#pragma once

#include "Vectorhelpers.hpp"
#include "Sequences.hpp"
#include "Range.hpp"
#include <cassert>
#include <algorithm>

// TODO: Subsets in some other orders, like decord_begin() or something... I don't know.

namespace dscr
{	
	
	////////////////////////////////////////////////////////////
    /// \brief class of all 2^n subsets of the set {0,1,...,n-1}, expressed as incidence vectors
    /// \param BoolType is at least a bool, but it can be an int, uint, etc. It can be signed or unsigned.
	/// # Example:
	///   
	///     subsets X(4);
	///		for (const auto& x : X)
	///			cout << x << " ";
	///
	/// Prints out:
	///
	/// 	[0000] [1000] [0100] [1100] [0010] [1010] [0110] [1110] [0001] [1001] [0101] [1101] [0011] [1011] [0111] [1111]
    ////////////////////////////////////////////////////////////
	template <class BoolType>
	class basic_subsets
	{
	public:
		typedef long long int difference_type;
		typedef unsigned long long int size_type;
		typedef vector<BoolType> value_type;
		typedef vector<BoolType> subset;
	
		// Static functions
		static void next_subset(subset& data)
		{
			for (size_t i = 0; i < data.size(); ++i)
			{
				//cout << "i = " << i << endl;
				if (!data[i])
				{
					data[i] = 1;
					for (size_t j=0; j < i; ++j)
					{
						data[j] = 0;
					}
					return;
				}
			}
		}
	
		static void prev_subset(subset& data)
		{
			for (size_t i = 0; i < data.size(); ++i)
			{
				//cout << "i = " << i << endl;
				if (data[i])
				{
					data[i] = 0;
					for (size_t j=0; j < i; ++j)
					{
						data[j] = 1;
					}
					return;
				}
			}
		}
		
		static void construct_subset(subset& data, size_type m)
		{
			for (size_t i = 0; i < data.size(); ++i)
				data[i] = static_cast<bool>((m & (size_t(1)<<i)));
		}
		
	public:
		
		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param n is an integer >= 0
		///
		////////////////////////////////////////////////////////////
		basic_subsets(size_t n) : m_n(n), m_begin(n), m_end(), m_rbegin(n),  m_rend()
		{
			m_end.m_ID = size();
			m_rend.m_ID = size();
		}
		
		////////////////////////////////////////////////////////////
		/// \brief The total number of subsets
		///
		/// \return 2^n
		///
		////////////////////////////////////////////////////////////
		size_type size() const { return static_cast<size_type>(1) << m_n; }
		
		
		/////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the ID of the iterator whose value is set. That is, the index of subset sub in the lexicographic order.
		///
		/// Inverse of operator[]. If subset x is the m-th subset, then get_index(x) is m.
		/// If one has a subsets::iterator, then the member function ID() should return the same value.
		/// \return the index of subset sub, as if basic_subsets was a proper data structure
		/// \note This constructs the proper index from scratch. If an iterator is already known, calling ID on the iterator is much more efficient.
		/////////////////////////////////////////////////////////////////////////////
		size_type get_index(const subset& set) const
		{
			size_t s = set.size();
			assert(s < 64);
			size_t r = 0;
			
			for (size_t i = 0; i < s; ++i)
			{
				if (set[i])
					r += (static_cast<size_t>(1) << i);
			}
			
			return r;
		}
		
		////////////////////////////////////////////////////////////
		/// \brief Random access iterator class. It's much more efficient as a bidirectional iterator than purely random access.
		////////////////////////////////////////////////////////////
		class iterator : public std::iterator<std::random_access_iterator_tag,vector<BoolType>>//bidirectional iterator
		{
		public:
			iterator() : m_ID(0), m_data() {} //empty initializer
		public:
			iterator(size_t n) : m_ID(0), m_data(n,0)
			{
			}
			
			//prefix
			inline iterator& operator++()
			{
				++m_ID;
				
				next_subset(m_data);
				
				return *this;
			}
			
			inline iterator& operator--()
			{
				
				if (m_ID == 0)
					return *this;
				
				--m_ID;
				
				prev_subset(m_data);
				
				return *this;
			}
			
			inline const vector<BoolType>& operator*() const
			{
				return m_data;
			}
			
			////////////////////////////////////////
			/// 
			/// \brief Random access capabilities to the iterators
			/// \param n -> This assumes 0 <= n+ID <= size(n,k)
			///
			////////////////////////////////////////
			inline iterator& operator+=(difference_type n)
			{
				assert (0 <= n+m_ID);
				
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
				construct_subset(m_data,m_ID);
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
			
			inline size_type ID() const { return m_ID; }
			
			inline bool operator==(const iterator& it) const
			{
				return it.ID() == ID();
			}
			
			inline bool operator!=(const iterator& it) const
			{
				return it.ID() != ID();
			}
			
			inline bool is_at_end(size_t n) const
			{
				return m_ID == factorial(n);
			}
			
			void reset(size_t n)
			{
				m_ID = 0;
				m_data = vector<BoolType>(n);
			}
		private:
			size_type m_ID;
			subset m_data;
			
			friend class basic_subsets;
		}; // end class iterator
		

		////////////////////////////////////////////////////////////
		/// \brief Reverse random access iterator class. It's much more efficient as a bidirectional iterator than purely random access.
		////////////////////////////////////////////////////////////
		class reverse_iterator : public std::iterator<std::random_access_iterator_tag,vector<BoolType>>//bidirectional iterator
		{
		public:
			reverse_iterator() : m_ID(0), m_data() {} //empty initializer
			reverse_iterator(size_t n) : m_ID(0), m_data(n,1)
			{
			}
			
			//prefix
			inline reverse_iterator& operator++()
			{
				++m_ID;
				
				prev_subset(m_data);
				
				return *this;
			}
			
			inline reverse_iterator& operator--()
			{				
				assert (m_ID != 0);

				--m_ID;
				
				next_subset(m_data);

				return *this;
			}
			
			inline const vector<BoolType>& operator*()
			{
				return m_data;
			}
			
			inline const vector<BoolType>& operator*() const
			{
				return m_data;
			}
			
			////////////////////////////////////////
			/// 
			/// \brief Random access capabilities to the iterators
			/// \param n -> This assumes 0 <= n+ID <= size(n,k)
			///
			////////////////////////////////////////
			inline reverse_iterator& operator+=(difference_type m)
			{
				assert (0 <= m+m_ID);
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
				auto num = (static_cast<size_type>(1) << m_data.size())-m_ID-1;
				// If n is large, then it's better to just construct it from scratch.
				construct_subset(m_data,num);
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
			
			inline size_type ID() const { return m_ID; }
			
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
				return m_ID == binomial(m_n, m_data.size());
			}
			
			void reset(BoolType n)
			{
				m_ID = 0;
				m_data = vector<BoolType>(n,1);
			}
		private:
			size_type m_ID;
			subset m_data;
			
			friend class basic_subsets;
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
		/// \brief Access to the m-th subset (slow for iteration)
		///
		/// This is equivalent to calling *(begin()+m)
		/// \param m should be an integer between 0 and size(). Undefined behavior otherwise.
		/// \return The m-th subset, as defined in the order of iteration (lexicographic)
		////////////////////////////////////////////////////////////
		subset operator[](size_type m) const
		{
			auto it = begin();
			it += m;
			return *it;
		}
		
		
// 		subset random() const
// 		{
// 		}
		
	private:
		size_t m_n;
		iterator m_begin;	
		iterator m_end;
		reverse_iterator m_rbegin;	
		reverse_iterator m_rend;	
	}; // end class basic_subsets
	typedef basic_subsets<bool> subsets;
	typedef basic_subsets<uint_fast8_t> subsets_fast;
	
	
} // end namespace dscr;




