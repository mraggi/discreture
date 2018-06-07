#pragma once
#include "AggregationView.hpp"
#include "VectorHelpers.hpp"
#include <unordered_map>

namespace dscr
{

template <class Container, class ContainerOfIndexContainers>
class CompoundContainer
{
public:
    using difference_type = long long;
    using size_type = difference_type;
    using indices = typename ContainerOfIndexContainers::value_type;
    using index = typename indices::value_type;
    using value_type = AggregationView<Container, indices>;
    class iterator;
    using const_iterator = iterator;

public:
    CompoundContainer(const Container& objects,
                      const ContainerOfIndexContainers& Indices)
        : objects_(objects), indices_(Indices)
    {}

    size_type size() const { return indices_.size(); }

    iterator begin() const { return iterator(objects_, indices_.begin()); }

    iterator end() const { return iterator(objects_, indices_.end()); }

    value_type operator[](size_type i) const
    {
        return aggregation_view(objects_, indices_[i]);
    }

    class iterator
        : public boost::iterator_facade<iterator,
                                        value_type,
                                        boost::random_access_traversal_tag,
                                        value_type>
    {
    public:
        using indices_iterator =
          typename ContainerOfIndexContainers::const_iterator;

        iterator() = default;

        iterator(const Container& objects, const indices_iterator& indices_iter)
            : objects_(&objects), indices_(indices_iter)
        {}

    private:
        void increment() { ++indices_; }

        void decrement() { --indices_; }

        void advance(difference_type n) { indices_ += n; }

        bool equal(const iterator& other) const
        {
            return indices_ == other.indices_;
        }

        value_type dereference() const
        {
            return aggregation_view(*objects_, *indices_);
        }

        difference_type distance_to(const iterator& other) const
        {
            return other.indices_ - indices_;
        }

        const indices_iterator& get_index_iterator() const { return indices_; }

    private:
        Container const* objects_{nullptr};
        indices_iterator indices_;
        friend class boost::iterator_core_access;
        friend class CompoundContainer;
    };

private:
    const Container& objects_;
    ContainerOfIndexContainers indices_;
};

// deprecated in C++17, but useful for C++14
template <class Container, class ContainerOfIndexContainers>
auto compound_container(const Container& A, const ContainerOfIndexContainers& I)
{
    return CompoundContainer<Container, ContainerOfIndexContainers>(A, I);
}

} // namespace dscr
