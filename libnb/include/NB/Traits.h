#pragma once

#include <concepts>
#include <type_traits>
#include <cstddef>
#include <tuple>

namespace NB::Traits
{
namespace Parameters
{
template<typename... Args>
inline constexpr std::size_t Size = sizeof...(Args);

template<typename T, typename... Args>
inline constexpr bool Has = (std::same_as<T, Args> || ...);

template<std::size_t I, typename... Args> 
requires (I < Size<Args...>)
using Get = typename std::tuple_element<I, std::tuple<Args...>>::type;

namespace 
{
template<typename...>
struct unique_types_impl;

template<typename T>
struct unique_types_impl<T> : std::true_type {};

template<>
struct unique_types_impl<> : std::false_type {};

template<typename T, typename... Args>
struct unique_types_impl<T, Args...> : std::false_type {};

template<typename T, typename... Args>
requires ((!std::same_as<T, Args> && ...) && unique_types_impl<Args...>::value)
struct unique_types_impl<T, Args...> : std::true_type {};
}

template<typename... Args>
inline constexpr bool Unique = unique_types_impl<Args...>::value;
}
}