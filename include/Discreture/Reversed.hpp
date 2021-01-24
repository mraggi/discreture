#pragma once

#include "TemplateHelpers.hpp"

namespace discreture
{

template <class Container>
class Reversed
{
public:
    using Cont_t = std::remove_cv_t<std::remove_reference_t<Container>>;
    using value_type = typename Cont_t::value_type;
    using difference_type = typename Cont_t::difference_type;
    using size_type = typename Cont_t::size_type;

    using iterator = typename Cont_t::reverse_iterator;
    using const_iterator = typename Cont_t::const_reverse_iterator;

    using reverse_iterator = typename Cont_t::iterator;
    using const_reverse_iterator = typename Cont_t::const_iterator;

    explicit Reversed(Container&& C) : original_(C) {}

    const_iterator begin() const { return original_.rbegin(); }
    const_iterator end() const { return original_.rend(); }
    //     iterator begin() { return original_.rbegin(); }
    //     iterator end() { return original_.rend(); }

    const_iterator cbegin() const { return original_.crbegin(); }
    const_iterator cend() const { return original_.crend(); }

    //     reverse_iterator rbegin() { return original_.begin(); }
    //     reverse_iterator rend() { return original_.end(); }
    const_reverse_iterator rbegin() const { return original_.begin(); }
    const_reverse_iterator rend() const { return original_.end(); }

    const_reverse_iterator crbegin() const { return original_.cbegin(); }
    const_reverse_iterator crend() const { return original_.cend(); }

    size_type size() const { return original_.size(); }

private:
    add_const_to_value_t<Container> original_;
};

#if __cplusplus > 201703L
// deduction guide only for c++17 :(
template <class Container>
Reversed(Container &&)->Reversed<Container>;
#endif

// Utility function for C++14 and below, like make_shared. Deprecated in C++17.
template <class Container>
auto reversed(Container&& C)
{
    return Reversed<Container>{std::forward<Container>(C)};
}

} // namespace discreture
