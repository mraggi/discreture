#pragma once
#include <type_traits>

namespace discreture
{

template <typename T>
using EnableIfIntegral = std::enable_if_t<std::is_integral<T>::value>;

template <typename T>
using EnableIfNotIntegral = std::enable_if_t<!std::is_integral<T>::value>;

template <typename T>
using EnableIfReference = std::enable_if_t<std::is_reference<T>::value>;

template <typename T>
using EnableIfNotReference = std::enable_if_t<!std::is_reference<T>::value>;

// If T is a reference, const T is not what one would expect.
template <class T>
struct const_reference
{
    using type = const std::remove_reference_t<T>&;
};

template <class T>
using const_reference_t = typename const_reference<T>::type;

template <class T>
struct add_const_to_value
{
    using type =
      std::conditional_t<std::is_lvalue_reference<T>::value, const_reference_t<T>, const T>;
};

template <class T>
using add_const_to_value_t = typename add_const_to_value<T>::type;

} // namespace discreture
