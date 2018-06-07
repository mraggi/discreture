#pragma once
#include "AggregationView.hpp"
#include "VectorHelpers.hpp"
#include <unordered_map>

namespace dscr
{

////////////////////////////////////
// A compound container is a lazy container whose elements are AggregationViews.
// For example,
//     std::vector<std::string> Objects = {"hello", "world", "goodbye"};
//     for (auto permutation : compound_container(Objects,Permutations(3)))
//     {
//         for (auto word : permutation)
//             std::cout << word << ' ';
//         std::cout << '\n';
//     }
//
// just prints out:
//
//     hello world goodbye
//     hello goodbye world
//     world hello goodbye
//     world goodbye hello
//     goodbye hello world
//     goodbye world hello
////////////////////////////////////

template <class Container, class ContainerOfIndexContainers>
class CompoundContainer
{
public:
    using difference_type = long long;
    using size_type = difference_type;
    using indices = typename ContainerOfIndexContainers::value_type;
    using index = typename indices::value_type;
    using value_type = AggregationView<Container, const indices&>;
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

    auto operator[](size_type i) const
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

        iterator(const Container& objects, indices_iterator indices_iter)
            : objects_(&objects), indices_(std::move(indices_iter))
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
