#pragma once

#include "Basic.hpp"
#include "Vectorhelpers.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "Range.hpp"

namespace dscr
{	
	
	////////////////////////////////////////////////////////////
    /// \brief class of all n choose k combinations of size k of the set {0,1,...,n-1}.
    /// \param IntType should be an integral type with enough space to store n and k. It can be signed or unsigned.
	/// \param n the size of the set
	/// \param k the size of the combination (subset). Should be an integer such that n choose k is not bigger than the largest unsigned long int there is. For example, typically 50 choose 25 is already larger than the largest long unsigned int.
	/// # Example:
	///
	///		combinations X(6,3);
	///		for (const auto& x : X)
	///			cout << x << " ";
	///
	/// Prints out:
	///
	/// 	[ 0 1 2 ] [ 0 1 3 ] [ 0 2 3 ] [ 1 2 3 ] [ 0 1 4 ] [ 0 2 4 ] [ 1 2 4 ] [ 0 3 4 ] [ 1 3 4 ] [ 2 3 4 ] [ 0 1 5 ] [ 0 2 5 ] [ 1 2 5 ] [ 0 3 5 ] [ 1 3 5 ] [ 2 3 5 ] [ 0 4 5 ] [ 1 4 5 ] [ 2 4 5 ] [ 3 4 5 ]
	///
	/// # Example 2:
	///
	///     basic_combinations<short int> X(5,1);
	///		for (const auto& x : X)
	///			cout << x << " ";
	///		Prints out:
	///			[0] [1] [2] [3] [4]
	///
	///	# Example 3:
	/// 
	///		string A = "helloworld";
	///		combinations X(A.size(),2);
	///		for (const auto& x : X)
	///		{
	///			auto b = compose(A,x);
	///			cout << b << "-";
	///		}
	///
	///		Prints out:
	///			he-hl-el-hl-el-ll-ho-eo-lo-lo-hw-ew-lw-lw-ow-ho-eo-lo-lo-oo-wo-hr-er-lr-lr-or-wr-or-hl-el-ll-ll-ol-wl-ol-rl-hd-ed-ld-ld-od-wd-od-rd-ld-
	///
    ////////////////////////////////////////////////////////////
	template <class IntType>
	class basic_combinations
	{
	public:
		
		typedef long long int difference_type;
		typedef unsigned long long int size_type;
		typedef vector<IntType> value_type;
		typedef vector<IntType> combination;

		//Declarations.
		class iterator;
		
		// **************** Begin static functions
		static IntType next_combination(combination& data, IntType hint = 0)
		{
			assert(std::is_sorted(data.begin(),data.end()));
			if (data.empty())
				return 0;
			IntType k = data.size()-1;
// 			cout << "bah1 " << k << endl;
// 			cout << "hint = " << hint << endl;
			for (IntType i = hint; i < k; ++i)
			{
				if (data[i]+1 != data[i+1]) //Does NOT improve with binary search... huh.
				{
					//i is the first that can be augmented
					++data[i];
					for (IntType j = 0; j < i; ++j)
					{
						data[j] = j;
					}
					
					i = std::max(i,static_cast<IntType>(1));
					return i-1;
				}
			}
// 			cout << "bah2" << endl;
			++data[k];
			for (IntType j = 0; j < k; ++j)
			{
				data[j] = j;
			}
			k = std::max(k,static_cast<IntType>(1));
			return k-1;
		}
	
		static void prev_combination(combination& data)
		{
			assert(std::is_sorted(data.begin(),data.end()));
// 			assert(data.back() != data.size()-1);

			IntType k = data.size();
			IntType i = 0;
			for ( ; i < k; ++i)
			{
				if (data[i] != i)
				{
					--data[i];
					break;
				}
			}
			if (i != k)
			{
				IntType a = data[i]-i;
				for (IntType j = 0; j < i; ++j,++a)
				{
					data[j] = a;
				}
			}
		}
		
		static void construct_combination(combination& data, size_type m)
		{
			IntType k = data.size();
			for (IntType i = 0; i < k; ++i)
			{
				IntType r = k - i;
				IntType first = r;
				while (binomial(first,r) <= m) { ++first; }
				--first;
				
				data[r-1] = first;
				m -= binomial(first,r);
			}
		}
		
		///////////////////////////////////////
		/// \brief Combination comparison "less than" operator. Assumes lhs and rhs have the same size.
		/// \return true if lhs would appear before rhs in the normal iteration order, false otherwise
		///////////////////////////////////////
		static bool compare(const combination& lhs, const combination& rhs)
		{
			assert(lhs.size() == rhs.size());
			auto itl = lhs.rbegin();
			auto itr = rhs.rbegin();
			for ( ; itl != lhs.rend(); ++itl, ++itr)
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
		basic_combinations(IntType n, IntType k) : m_n(n), m_k(k), m_begin(n,k), m_end(), m_rbegin(n,k),  m_rend()
		{
			m_end.m_ID = size();
			m_rend.m_ID = size();
		}
		
		////////////////////////////////////////////////////////////
		/// \brief The total number of combinations
		///
		/// \return binomial(n,r) 
		///
		////////////////////////////////////////////////////////////
		size_type size() const { return binomial(m_n,m_k); }
		
		
		/////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the ID of the iterator whose value is comb. That is, the index of combination comb in the lexicographic order.
		///
		/// Inverse of operator[]. If combination x is the m-th combination, then get_index(x) is m.
		/// If one has a combinations::iterator, then the member function ID() should return the same value.
		/// \return the index of combination comb, as if basic_combinations was a proper data structure
		/// \note This constructs the proper index from scratch. If an iterator is already known, calling ID on the iterator is much more efficient.
		/////////////////////////////////////////////////////////////////////////////
		size_type get_index(const combination& comb) const
		{
			if (comb.empty()) return 0;
			size_type n = comb.size();
// 			IntType biggest = comb[n-1];
			
			size_type result = 0;
			
			for (difference_type i = n-1; i >= 0; --i)
				result += binomial(comb[i],i+1);
			
			return result;
		}
		
		IntType get_n() const { return m_n; }
		IntType get_k() const { return m_k; }
		
		
		////////////////////////////////////////////////////////////
		/// \brief Random access iterator class. It's much more efficient as a bidirectional iterator than purely random access.
		////////////////////////////////////////////////////////////
		class iterator : public std::iterator<std::random_access_iterator_tag,vector<IntType>>
		{
		public:
			iterator() : m_ID(0), m_data(), m_placetostartsearch(0) {} //empty initializer
		private:
			explicit iterator(IntType id) : m_ID(id), m_data(), m_placetostartsearch(0) {} //ending initializer: for id only. Do not use unless you know what you are doing.
		public:
			iterator(IntType n, IntType r) : m_ID(0), m_data(range<IntType>(r)), m_placetostartsearch(r-1)
			{
			}
			
			//prefix
			inline iterator& operator++()
			{
				++m_ID;
				
				m_placetostartsearch = next_combination(m_data,m_placetostartsearch);
				
				return *this;
			}
			
			inline iterator& operator--()
			{
				
				if (m_ID == 0)
					return *this;
				
				--m_ID;
				
				prev_combination(m_data);
				
				return *this;
			}
			
			inline const vector<IntType>& operator*() const
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
				construct_combination(m_data,m_ID);
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
			
			inline bool is_at_end(IntType n) const
			{
				return m_ID == binomial(n, m_data.size());
			}
			
			void reset(IntType n, IntType r)
			{
				m_ID = 0;
				overwrite(m_data, range<IntType>(r));
				m_placetostartsearch = r-1;
			}
			
		private:
			size_type m_ID {0};
			combination m_data;
			IntType m_placetostartsearch {0};
			
			friend class basic_combinations;
		}; // end class iterator
		
		iterator get_iterator(const combination& comb)
		{
			iterator it;
			it.m_ID = get_index(comb);
			it.m_data = comb;
			it.m_placetostartsearch = 0;
			return it;
		}

		////////////////////////////////////////////////////////////
		/// \brief Reverse random access iterator class. It's much more efficient as a bidirectional iterator than purely random access.
		////////////////////////////////////////////////////////////
		class reverse_iterator : public std::iterator<std::random_access_iterator_tag,vector<IntType>>//bidirectional iterator
		{
		public:
			reverse_iterator() : m_n(0), m_ID(0), m_data() {} //empty initializer
		private:
			explicit reverse_iterator(IntType id) : m_ID(id), m_data() {} //ending initializer: for id only. Do not use unless you know what you are doing.
		public:
			reverse_iterator(IntType n, IntType r) : m_n(n), m_ID(0), m_data(range<IntType>(n-r,n))
			{
			}
			
			//prefix
			inline reverse_iterator& operator++()
			{
				++m_ID;
				
				prev_combination(m_data);
				
				return *this;
			}
			
			inline reverse_iterator& operator--()
			{				
				assert (m_ID != 0);

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
				auto num = binomial(m_n,m_data.size())-m_ID-1;
				// If n is large, then it's better to just construct it from scratch.
				construct_combination(m_data,num);
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
				return m_ID == binomial(m_n, m_data.size());;
			}
			
			void reset(IntType n, IntType r)
			{
				m_n = n;
				m_ID = 0;
				m_data = range<IntType>(n-r,n);
			}
		private:
			IntType m_n;
			size_type m_ID;
			combination m_data;
			
			friend class basic_combinations;
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
		/// 	auto it = X.find_if([](const vector<int>& comb) -> bool
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
			while (DFSUtil(A,pred))
			{
				if (A.size() == static_cast<size_t>(m_k))
					return get_iterator(A);
			}
			return end();
		}
		
		///////////////////////////////////////////////
		/// \brief This is an efficient way to construct all combination of size k which fully satisfy a predicate 
		/// 
		/// This function is similar to find_if, but it returns a vector with all combinations which satisfy pred,
		/// 
		/// # Example:
		/// 
		/// 	combinations X(10,5);
		/// 	auto vall = X.find_all([](const vector<int>& comb) -> bool
		///		{
		///			for (int i = 0; i < comb.size()-1; ++i)
		///			{
		///				if (comb[i]+1 == comb[i+1])
		///					return false;
		///			}
		///			return true;
		///		});
		/// 	for (const auto& v : vall)
		/// 		cout << v << endl;
		/// 		
		/// 		
		/// Prints out:	
		/// 	[ 0 2 4 6 8 ]
		///		[ 0 2 4 6 9 ]
		///		[ 0 2 4 7 9 ]
		///		[ 0 2 5 7 9 ]
		///		[ 0 3 5 7 9 ]
		///		[ 1 3 5 7 9 ]
		/// which are all combinations which don't contain two consecutive elements
		/// 		
		/// \param Pred should be what we call a *partial predicate*: It takes a combination as a parameter and returns either true or false.
		///
		///
		/// \return An vector<combination> filled will all permutations which fully satisfy the predicate.
		///
		///	\todo Perhaps one should be able to iterate over all such permutations without constructing a vector of them!
		///
		/////////////////////////////////////////////
		template<class PartialPredicate>
		vector<combination> find_all(PartialPredicate pred)
		{
			vector<combination> toReturn;
			combination A;
			A.reserve(m_k);
			while (DFSUtil(A,pred))
			{
				if (A.size() == static_cast<size_t>(m_k))
					toReturn.push_back(A);
			}
			return toReturn;
		}
		
	private:
		IntType m_n;
		IntType m_k;
		iterator m_begin;	
		iterator m_end;
		reverse_iterator m_rbegin;	
		reverse_iterator m_rend;
		
		template <class P>
		bool augment(combination& comb, P pred, IntType start = 0)
		{
			if (comb.empty())
			{
				if (start < m_n-m_k+1)
				{
					comb.push_back(start);
					return true;
				}
			}
			auto last = comb.back();
			auto guysleft = m_k-comb.size();
			
			start = std::max(last+1,start);
			for (size_t i = start; i < m_n-guysleft+1; ++i)
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
			auto last = comb.back();
// 			auto currsize = comb.size();
			
			if (comb.size() < static_cast<size_t>(m_k))
			{
				if (augment(comb,pred))
					return true;
			}
			// If it can't be augmented, be it because size is already k or else, we have to start backtracking 
			while (!comb.empty())
			{
				last = comb.back();
				comb.pop_back();
				if (augment(comb,pred,last+1))
					return true;
			}
			return false;
		}
		
	}; // end class basic_combinations
	
	using combinations = basic_combinations<int>;

} // end namespace dscr;




