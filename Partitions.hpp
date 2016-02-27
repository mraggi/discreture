#pragma once

#include "Basic.hpp"
#include "Vectorhelpers.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "Range.hpp"

namespace dscr
{	
	
	////////////////////////////////////////////////////////////
    /// \brief class of partitions of the number n.
    /// \param IntType should be an integral type with enough space to store n and k. It can be signed or unsigned.
	/// # Example:
	///   
	///     partitions X(6);
	///		for (auto& x : X)
	///			cout << x << " ";
	///
	/// Prints out:
	///
	/// 	[ 1 1 1 1 1 1 ] [ 2 1 1 1 1 ] [ 3 1 1 1 ] [ 2 2 1 1 ] [ 4 1 1 ] [ 3 2 1 ] [ 2 2 2 ] [ 5 1 ] [ 4 2 ] [ 3 3 ] [ 6 ] 
    ////////////////////////////////////////////////////////////
	template <class IntType>
	class basic_partitions
	{
	public:
		
		typedef long long int difference_type;
		typedef unsigned long long int size_type;
		typedef vector<IntType> value_type;
		typedef vector<IntType> partition;

		//Declarations.
		class iterator;
		
		// **************** Begin static functions
		static void next_partition(partition& data, IntType n)
		{
			size_t t = data.size();

			if (t == 1) //At END
			{
				return;
			}

			if(data.front()-data.back() < 2)
			{
				//Hay que cambiar de tamano
				data.pop_back();
				data[0]=n-t+2;
				for(size_t i=1; i<t-1; ++i)
				{
					data[i]=1;
				}
				return;
			}
			//cuando no hay que cambiar de tamano
			//Comenzando del final, buscamos al primero cuya diferencia sea 2 o más para pasar una unidad al primero que sea posible
			IntType menor=data.back();
			IntType suma=menor;
			for(difference_type i=t-2; i>-1; --i)
			{
				suma += data[i];
				
				if(data[i]-menor<2)
					continue;
				
				suma -= data[i];
				
				
				--data[i];
				//cout << "Le decidí bajar al " << i << " que ahora vale " << data[i] << endl;

				++suma;

				size_t numespacios = t-i-1;
				difference_type exceso = suma - numespacios;

				
				for (size_t j = i+1; j < t; ++j)
				{
					if (exceso <= 0)
					{
						data[j] = 1;
						continue;
					}
					
					if (exceso+1 >= data[i])
					{
						data[j] = data[i];
					
						exceso -= int(data[j]-1);
					
						continue;
					}
					data[j] = 1+exceso;
					exceso = 0;
					
				}
				return;
			}
		}
	
		static void prev_partition(partition& data, IntType n)
		{
			
		}
		
		static partition conjugate(const partition& P) 
		{
			assert (!P.empty());
			partition result(P[0],1);
			auto n = P.size();
			
			result[0] = n;
			for (size_t i = 1; i < n; ++i)
			{
				auto t = std::lower_bound(P.begin(), P.end(),i,std::greater<IntType>());
					
				int r = t-P.begin();
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
		basic_partitions(IntType n) : m_n(n), m_begin(n), m_end(), m_rbegin(n),  m_rend()
		{
			m_end.m_ID = size();
			m_rend.m_ID = size();
		}
		
		////////////////////////////////////////////////////////////
		/// \brief The total number of partitions
		///
		/// \return p_n
		///
		////////////////////////////////////////////////////////////
		size_type size() const { return partition_number(m_n); }
		
		
		
		IntType get_n() const { return m_n; }
		
		
		////////////////////////////////////////////////////////////
		/// \brief Forward iterator class.
		////////////////////////////////////////////////////////////
		class iterator : public std::iterator<std::forward_iterator_tag,partition>
		{
		public:
			iterator() : m_ID(0), m_data(), m_n(0) {} //empty initializer
		public:
			explicit iterator(IntType n) : m_ID(0), m_data(n,1), m_n(n)
			{
			}
			
			//prefix
			inline iterator& operator++()
			{
				++m_ID;
				
				next_partition(m_data,m_n);
				
				return *this;
			}
			
			inline iterator& operator--()
			{
				
				if (m_ID == 0)
					return *this;
				
				--m_ID;
				
				prev_partition(m_data);
				
				return *this;
			}
			
			inline const vector<IntType>& operator*() const
			{
				return m_data;
			}
			
			inline const partition* operator->() const
			{ 
				return & operator*();
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
			
			inline bool is_at_end(IntType n) const
			{
				return m_ID == partition_number(n);
			}
			
			void reset(IntType r)
			{
				m_ID = 0;
				m_data.clear();
				m_data.resize(r,1);
			}
			
		private:
			size_type m_ID;
			partition m_data;
			IntType m_n;
			
			friend class basic_partitions;
		}; // end class iterator

		////////////////////////////////////////////////////////////
		/// \brief Forward Iterator class
		////////////////////////////////////////////////////////////
		class reverse_iterator : public std::iterator<std::forward_iterator_tag,partition>
		{
		public:
			reverse_iterator() : m_n(0), m_ID(0), m_data() {} //empty initializer
			explicit reverse_iterator(IntType n) : m_n(n), m_ID(0), m_data(1,n)
			{
			}
			
			//prefix
			inline reverse_iterator& operator++()
			{
				++m_ID;
				
				prev_partition(m_data);
				
				return *this;
			}
			
			inline reverse_iterator& operator--()
			{				
				assert (m_ID != 0);

				--m_ID;
				
				next_partition(m_data);

				return *this;
			}
			
			inline const partition& operator*()
			{
				return m_data;
			}
			
			inline const partition& operator*() const
			{
				return m_data;
			}
			
			inline const partition* operator->() const
			{ 
				return & operator*();
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
			
			
			
		private:
			IntType m_n;
			size_type m_ID;
			partition m_data;
			
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
		
		const reverse_iterator& rbegin() const
		{
			return m_rbegin;
		}
		
		const reverse_iterator& rend() const
		{
			return m_rend;
		}
		

	private:
		IntType m_n;
		iterator m_begin;	
		iterator m_end;
		reverse_iterator m_rbegin;	
		reverse_iterator m_rend;
		
	}; // end class basic_partitions
	
	using partitions = basic_partitions<int>;

}// end namespace dscr;
