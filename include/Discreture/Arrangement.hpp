#pragma once
#include "Misc.hpp"

namespace dscr
{

///////////////////////////////////////////////
/// \brief class for composing two containers "A" and "B", where the elements of
/// B are integers between 0 and A.size() Then the elements of arrangement(A,B)
/// are {A[B[0]], A[B[1]], ...}, but arrangement is lazy.
///////////////////////////////////////////////
template <class RAContainer, class RAIndexContainer>
class arrangement
{
public:
    using value_type = typename RAContainer::value_type;
    using size_type = long long; // NOLINT
    using difference_type = size_type;
    class iterator;
    using const_iterator = iterator;

    arrangement(const RAContainer& objects, const RAIndexContainer& indices)
        : m_objects(objects), m_indices(indices)
    {}

    iterator begin() const { return iterator(m_objects, m_indices.begin()); }

    iterator end() const { return iterator(m_objects, m_indices.end()); }

    size_type size() const { return m_indices.size(); }

    const value_type& operator[](difference_type m) const
    {
        return m_objects[m_indices[m]];
    }

    RAContainer bake() const { return RAContainer(begin(), end()); }

    // ****************** start iterator
    class iterator
        : public boost::iterator_facade<iterator,
                                        const value_type&,
                                        boost::random_access_traversal_tag>
    {
    public:
        using index_iter = typename RAIndexContainer::const_iterator;

        iterator(const RAContainer& objects, const index_iter& index)
            : m_index_iter(index), m_objects(objects)
        {}

    private:
        void increment() { ++m_index_iter; }

        void decrement() { --m_index_iter; }

        void advance(difference_type m) { std::advance(m_index_iter, m); }

        const value_type& dereference() const
        {
            return m_objects[*m_index_iter];
        }

        bool equal(const iterator& other) const
        {
            return m_index_iter == other.m_index_iter;
        }

        difference_type distance_to(const iterator& other) const
        {
            return other.m_index_iter - m_index_iter;
        }

    private:
        index_iter m_index_iter;
        const RAContainer& m_objects;
        friend class boost::iterator_core_access;
    };
    // ********** end iterator
private:
    const RAContainer& m_objects;
    const RAIndexContainer& m_indices;
};

template <class RAContainer, class RAIndexContainer>
arrangement<RAContainer, RAIndexContainer>
make_arrangement(const RAContainer& objects, const RAIndexContainer& indices)
{
    return arrangement<RAContainer, RAIndexContainer>(objects, indices);
}

template <class RAContainer, class RAIndexContainer>
std::ostream& operator<<(std::ostream& os,
                         const arrangement<RAContainer, RAIndexContainer>& A)
{
    for (auto& a : A)
        os << a << ' ';
    return os;
}

} // namespace dscr
