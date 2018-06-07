#pragma once
#include "Misc.hpp"
#include <type_traits>

namespace dscr
{

///////////////////////////////////////////////
/// An aggregation is a cluster of things that have come or been brought
/// together.
///
/// class for (lazily) composing two containers "A" and "B", where the elements
/// of B are integers between 0 and A.size(). The elements of
/// AggregationView(A,B) are {A[B[0]], A[B[1]], ...}, but AggregationView is
/// lazy.
///////////////////////////////////////////////
template <class RAContainer, class RAIndexContainer>
class AggregationView
{
public:
    using value_type = typename RAContainer::value_type;
    using size_type = long long;
    using difference_type = size_type;
    class iterator;
    using const_iterator = iterator;

    template <typename RAI_>
    AggregationView(const RAContainer& objects, RAI_&& indices)
        : objects_(objects), indices_{std::forward<RAI_>(indices)}
    {}

    iterator begin() const { return iterator(objects_, indices_.begin()); }

    iterator end() const { return iterator(objects_, indices_.end()); }

    size_type size() const { return indices_.size(); }

    const value_type& operator[](difference_type m) const
    {
        return objects_[indices_[m]];
    }

    class iterator
        : public boost::iterator_facade<iterator,
                                        const value_type&,
                                        boost::random_access_traversal_tag>
    {
    public:
        using index_iter =
          typename std::remove_reference_t<RAIndexContainer>::const_iterator;

        iterator(const RAContainer& objects, const index_iter& index)
            : index_iter_(index), objects_(objects)
        {}

    private:
        void increment() { ++index_iter_; }

        void decrement() { --index_iter_; }

        void advance(difference_type m) { std::advance(index_iter_, m); }

        const value_type& dereference() const { return objects_[*index_iter_]; }

        bool equal(const iterator& other) const
        {
            return index_iter_ == other.index_iter_;
        }

        difference_type distance_to(const iterator& other) const
        {
            return other.index_iter_ - index_iter_;
        }

    private:
        index_iter index_iter_;
        const RAContainer& objects_;

        friend class boost::iterator_core_access;
    };

private:
    const RAContainer& objects_;
    RAIndexContainer indices_;
};

// Utility function for C++14 and below, like make_shared. Deprecated in C++17.
template <class RAContainer, class RAIndexContainer>
auto aggregation_view(const RAContainer& objects, RAIndexContainer&& indices)
  -> AggregationView<RAContainer, RAIndexContainer>
{
    return {objects, std::forward<RAIndexContainer>(indices)};
}

template <class RAContainer, class RAIndexContainer>
std::ostream&
operator<<(std::ostream& os,
           const AggregationView<RAContainer, RAIndexContainer>& A)
{
    for (auto& a : A)
        os << a << ' ';
    return os;
}

} // namespace dscr
