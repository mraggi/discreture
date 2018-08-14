#pragma once
#include "IndexedView.hpp"
#include "VectorHelpers.hpp"
#include <unordered_map>

namespace discreture
{

////////////////////////////////////
// An IndexedViewContainer is a lazy container whose elements are IndexedViews.
// For example,
//     std::vector<std::string> Objects = {"hello", "world", "goodbye"};
//     for (auto&& permutation :
//     indexed_view_container(Objects,Permutations(3)))
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
//
// You probably shouldn't use this directly unless you know what you are doing.
// Better to use combinations(A,4), for example, which returns one of these if
// A is a container itself.
////////////////////////////////////

template <class Container, class ContainerOfIndexContainers>
class IndexedViewContainer
{
public:
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    using indices = typename ContainerOfIndexContainers::value_type;
    using index = typename indices::value_type;
    using value_type = IndexedView<const Container&, const indices&>;
    class iterator;
    using const_iterator = iterator;

public:
    IndexedViewContainer(Container objects, ContainerOfIndexContainers indices)
        : objects_(std::move(objects)), indices_(std::move(indices))
    {}

    size_type size() const { return indices_.size(); }

    iterator begin() const { return iterator(objects_, indices_.begin()); }

    iterator end() const { return iterator(objects_, indices_.end()); }

    auto operator[](size_type i) const
    {
        return indexed_view(objects_, indices_[i]);
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

        iterator(const Container& objects, indices_iterator indices_iter)
            : objects_(objects), indices_(std::move(indices_iter))
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
            return indexed_view(objects_, *indices_);
        }

        difference_type distance_to(const iterator& other) const
        {
            return other.indices_ - indices_;
        }

        const indices_iterator& get_index_iterator() const { return indices_; }

    private:
        const Container& objects_;
        indices_iterator indices_;
        friend class boost::iterator_core_access;
    };

private:
    Container objects_; // TODO(mraggi): make this use the move-or-reference
                        // idiom.
    ContainerOfIndexContainers indices_; // TODO(mraggi): make this use the
                                         // move-or-reference idiom.
};

// deprecated in C++17, but useful for C++14
template <class Container, class ContainerOfIndexContainers>
auto indexed_view_container(const Container& A,
                            const ContainerOfIndexContainers& I)
{
    return IndexedViewContainer<Container, ContainerOfIndexContainers>(A, I);
}

} // namespace discreture
