#pragma once

#include "VectorHelpers.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "NumberRange.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace dscr
{	
	
	////////////////////////////////////////////////////////////////////////////////////
	/// \brief Class for iterating through all dyck (dyck) paths.
	/// \param IntType must be a SIGNED integer type.
	///
	/// Dyck paths, also called Catalan Paths, are paths that go from \f$(0,0)\f$ to \f$(0,2n)\f$, 
	/// which never go below the \f$ y=0\f$ line, in which each step is from \f$(x,y)\f$ to either 
	/// \f$(x+1,y+1)\f$ or \f$(x+1,y-1)\f$
	/// #Example Usage:
	///
	///		dyck_paths X(3)
	///		for (const auto& x : X)
	///			cout << x << endl;
	/// Prints out:
	///		[ 1 1 1 -1 -1 -1 ]
	///		[ 1 1 -1 1 -1 -1 ]
	///		[ 1 -1 1 1 -1 -1 ]
	///		[ 1 1 -1 -1 1 -1 ]
	///		[ 1 -1 1 -1 1 -1 ]
	///
	/// # Example: Parenthesis
	///
	/// 	dyck_paths X(3)
	/// 	for (const auto& x : X)
	/// 		cout << dyck_paths::to_string(x, "()") << endl;
	///
	/// Prints out:
	///		((()))
	///		(()())
	///		()(())
	///		(())()
	///		()()()
	///
	/////////////////////////////////////////////////////////////////////////////////////
	template <class IntType>
	class basic_dyck_paths
	{
	public:
		
		using difference_type = long long;
		using size_type = unsigned long long;
		using value_type = std::vector<IntType>;
		using dyck_path = value_type;

		//Declarations.
		class iterator;
		
		// **************** Begin static functions
		static void next_dyck_path(dyck_path& data)
		{
			size_t m_n = data.size()/2;
			if (m_n == 0)
				return;
			
			if (data[1]!=-1)
			{
				size_t loc=2;
				
				while(data[loc]!=-1)
					++loc;
				
				data[loc]=1;
				data[loc-1]=-1;
				
				return;
			}
			
			size_t verif=0;
			size_t i=1;
			while(i<m_n && verif==0)
			{
				if(data[(2*i)+1]==1)
					verif=((2*i)+1);
				++i;
			}
			
// 			for(nuint i=1; i<t; ++t)
// 			{
// 				if(data[(2*i)+1]==0)
// 					verif=((2*i)+1);
// 			}
			
			if(verif==0)
			{
				return;
			} else {
				size_t cont=0;
				auto encontrar=verif+1;
				for(size_t i=0; i<verif; ++i)
				{
					if(data[i]==-1)
					{
						data[i]=1;
						++cont;
					}
				}
				
				while(data[encontrar]!=-1)
					++encontrar;
				data[encontrar]=1;
				data[encontrar-1]=-1;
				while(cont!=0)
				{
					data[encontrar-1-cont]=-1;
					--cont;
				}
				return;
			}
		}
	
		static void prev_dyck_path(dyck_path& data, IntType n)
		{
			//TODO(mraggi): Think about how to do this
		}
		
		static std::string to_string(const dyck_path& data, const std::string& delim = "()")
		{
			std::string toReturn;
			for (auto i : data)
			{
				auto j = 1-(i+1)/2;
				toReturn.push_back(delim[j]);
			}
			return toReturn;
		}
		
		// **************** End static functions
		
	public:
		
		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param n is an integer >= 0
		///
		////////////////////////////////////////////////////////////
		basic_dyck_paths(IntType n) : m_n(n), m_begin(n), m_end(), m_rbegin(n),  m_rend()
		{
			m_end.m_ID = size();
			m_rend.m_ID = size();
		}
		
		////////////////////////////////////////////////////////////
		/// \brief The total number of dyck_paths
		///
		/// \return binomial(2n,n)/(n+1) 
		///
		////////////////////////////////////////////////////////////
		size_type size() const { return catalan(m_n); }
		
		IntType get_n() const { return m_n; }
		
		
		////////////////////////////////////////////////////////////
		/// \brief Forward iterator class.
		////////////////////////////////////////////////////////////
		class iterator :  public boost::iterator_facade<
													iterator,
													const dyck_path&,
													boost::forward_traversal_tag
													>
		{
		public:
			iterator() : m_ID(0), m_data() {} //empty initializer
			explicit iterator(IntType n) : m_ID(0), m_data(2*n,1)
			{
				for (size_t i = n; i < m_data.size(); ++i)
					m_data[i] = -1;
			}
			
			inline size_type ID() const { return m_ID; }

			inline bool is_at_end(IntType n) const
			{
				return m_ID == catalan(n);
			}
			
			void reset(IntType r)
			{
				m_ID = 0;
				m_data.resize(2*r);
				for (size_t i = 0; i < static_cast<size_t>(r); ++i)
					m_data[i] = 1;
				for (size_t i = r; i < 2*static_cast<size_t>(r); ++i)
					m_data[i] = -1;
			}
			
		private:
			//prefix
			void increment()
			{
				++m_ID;
				
				next_dyck_path(m_data);
			}
			
			
			const std::vector<IntType>& dereference() const
			{
				return m_data;
			}
			
			
			bool equal(const iterator& it) const
			{
				return it.ID() == ID();
			}
			
		private:
			size_type m_ID;
			dyck_path m_data;
			
			friend class basic_dyck_paths;
			friend class boost::iterator_core_access;
		}; // end class iterator

		////////////////////////////////////////////////////////////
		/// \brief Reverse random access iterator class. It's much more efficient as a bidirectional iterator than purely random access.
		////////////////////////////////////////////////////////////
		class reverse_iterator : public std::iterator<std::forward_iterator_tag,dyck_path>
		{
		public:
			reverse_iterator() : m_n(0), m_ID(0), m_data() {} //empty initializer
			explicit reverse_iterator(IntType n) : m_n(n), m_ID(0), m_data(1,2*n)
			{
				for (size_t i = 1; i < m_data.size(); i += 2)
					m_data[i] = -1;
			}
			
			//prefix
			inline reverse_iterator& operator++()
			{
				++m_ID;
				
				prev_dyck_path(m_data);
				
				return *this;
			}
			
			inline reverse_iterator& operator--()
			{				
				assert (m_ID != 0);

				--m_ID;
				
				next_dyck_path(m_data);

				return *this;
			}
			
			inline const dyck_path& operator*()
			{
				return m_data;
			}
			
			inline const dyck_path& operator*() const
			{
				return m_data;
			}
			
			inline const dyck_path* operator->() const
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
			dyck_path m_data;
			
			friend class basic_dyck_paths;
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
		
	}; // end class basic_dyck_paths
	
	using dyck_paths = basic_dyck_paths<int>;

} // end namespace dscr;
