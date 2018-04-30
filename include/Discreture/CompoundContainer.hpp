#pragma once
#include "Arrangement.hpp"
#include "VectorHelpers.hpp"
#include <unordered_map>

namespace dscr
{

template < 	class Container,
			class IndexContainerOfContainers>
class compound_container
{
public:
	using difference_type = long long; //NOLINT
	using size_type = difference_type; //yeah, signed!
	using indices = typename IndexContainerOfContainers::value_type;
	using index = typename indices::value_type;
	using value_type = arrangement<Container,indices>;
	class iterator;
	using const_iterator = iterator;
public:
	compound_container(const Container& objects, const IndexContainerOfContainers& Indices): 
																m_container(objects),
																m_indices(Indices)
	{
		
	}

	size_type size() const
	{
		return m_indices.size();
	}
	
	iterator begin() const
	{
		return iterator(m_container,m_indices.begin());
	}
	
	iterator end() const
	{
		return iterator(m_container,m_indices.end());
	}
	
	value_type operator[](size_type i) const
	{
		auto it = m_cache.find(i);
		if (it == m_cache.end())
		{
			it = m_cache.insert({i,m_indices[i]}).first;
		}
		return make_arrangement(m_container,it->second);
	}
	
	class iterator : public boost::iterator_facade< iterator,
													value_type,
													boost::random_access_traversal_tag,
													value_type>
	{
	public:
		using indexcontainer_iter = typename IndexContainerOfContainers::const_iterator;
		iterator() = default;
		iterator (const Container& objects, const indexcontainer_iter& iiter) : m_container(&objects), 
																			m_index_container_iter(iiter) 
		{}
		
	private:
		void increment()
		{
			++m_index_container_iter;
		}
		
		void decrement()
		{
			--m_index_container_iter;
		}
		
		void advance(difference_type t)
		{
			m_index_container_iter += t;
		}
		
		bool equal(const iterator& other) const
		{
			return m_index_container_iter == other.m_index_container_iter;
		}
		
		value_type dereference() const
		{
			return make_arrangement(*m_container,*m_index_container_iter);
		}
		
		difference_type distance_to(const iterator& other) const
		{
			return other.m_index_container_iter - m_index_container_iter;
		}
		
		const indexcontainer_iter& get_index_iterator() const
		{
			return m_index_container_iter;
		}
		
	private:
		Container const* m_container {nullptr};
		indexcontainer_iter m_index_container_iter;
		friend class boost::iterator_core_access;
		friend class compound_container;
	};
private:
	const Container& m_container;
	IndexContainerOfContainers m_indices;
	mutable std::unordered_map<size_type, typename IndexContainerOfContainers::value_type> m_cache;
};

template < 	class Container,
			class IndexContainerOfContainers>
compound_container<Container,IndexContainerOfContainers> 
make_compound_container(const Container& A, const IndexContainerOfContainers& I) //deprecated in C++17, but useful for C++14
{
	return compound_container<Container,IndexContainerOfContainers>(A,I);
}

} // namespace dscr
