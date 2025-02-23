#ifndef _TYPE_CONCEPTS_HPP_
#define _TYPE_CONCEPTS_HPP_

#include <string>
#include <concepts>
#include <type_traits>

#include "Caster.hpp"

namespace args::details
{

template<class T>
concept string_constructible = std::constructible_from<std::string, T>;

template<typename T>
concept push_backable_container = requires(T container)
{
    requires !string_constructible<T>;
    { container.push_back(typename T::value_type()) };
};

template<typename T>
concept insertable_container = requires(T container)
{
    requires !string_constructible<T>;
    { container.insert(typename T::value_type()) };
};

template<typename T>
concept pushable_container = requires(T container)
{
    requires !string_constructible<T>;
    { container.push(typename T::value_type()) };
};

template<typename T>
concept front_pushable_container = requires(T container)
{
    requires !string_constructible<T>;
    { container.push_front(typename T::value_type()) };
};

template<typename T>
concept any_appendable_container = requires()
{
    requires push_backable_container<T> || insertable_container<T> || pushable_container<T> || front_pushable_container<T>;
};

template<typename T>
concept have_caster = requires(T x)
{
    requires std::same_as<T, decltype(args::caster<T>::cast_value(std::string()))>;
};

} // args::details

#endif // _TYPE_CONCEPTS_HPP_
