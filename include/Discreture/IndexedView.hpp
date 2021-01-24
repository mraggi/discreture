#pragma once
#include "Misc.hpp"
#include "TemplateHelpers.hpp"

namespace discreture
{

///////////////////////////////////////////////
/// IndexedView is a class for (lazily) composing two containers "A" and "B",
/// where the elements of B are indices of A (integers between 0 and A.size()).
/// The elements of IndexedView(A,B) are {A[B[0]], A[B[1]], ...}, but
/// IndexedView is lazy (hence the name "view").
///////////////////////////////////////////////
template <class RAContainer, class RAIndexContainer>
class IndexedView
{
public:
    using ContainerUnderlying = std::remove_reference_t<RAContainer>;
    using IndexContainerUnderlying = std::remove_reference_t<RAIndexContainer>;
    using value_type = typename ContainerUnderlying::value_type;
    using size_type = std::ptrdiff_t;
    using difference_type = size_type;
    class iterator;
    using const_iterator = iterator;

    IndexedView(RAContainer&& objects, RAIndexContainer&& indices)
        : objects_(std::forward<RAContainer>(objects))
        , indices_{std::forward<RAIndexContainer>(indices)}
    {}

    iterator begin() const { return iterator(objects_, indices_.begin()); }

    iterator end() const { return iterator(objects_, indices_.end()); }

    size_type size() const { return indices_.size(); }

    const value_type& operator[](difference_type m) const
    {
        return objects_[indices_[m]];
    }

    class iterator
        : public boost::iterator_facade<iterator, const value_type&, boost::random_access_traversal_tag>
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
    add_const_to_value_t<RAContainer> objects_;
    add_const_to_value_t<RAIndexContainer> indices_;
};

#if __cplusplus >= 201703L
// deduction guide only for c++17 :(
template <class RAContainer, class RAIndexContainer>
IndexedView(RAContainer&&, RAIndexContainer &&)
  ->IndexedView<RAContainer, RAIndexContainer>;
#endif

// Utility function for C++14 and below, like make_shared. Deprecated in C++17.
template <class RAContainer, class RAIndexContainer>
auto indexed_view(RAContainer&& objects, RAIndexContainer&& indices)
  -> IndexedView<RAContainer, RAIndexContainer>
{
    return {std::forward<RAContainer>(objects),
            std::forward<RAIndexContainer>(indices)};
}

template <class RAContainer, class RAIndexContainer>
std::ostream& operator<<(std::ostream& os,
                         const IndexedView<RAContainer, RAIndexContainer>& A)
{
    for (auto&& a : A)
        os << a << ' ';
    return os;
}

} // namespace discreture
