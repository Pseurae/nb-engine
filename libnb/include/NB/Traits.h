#pragma once

#include <concepts>
#include <type_traits>
#include <cstddef>
#include <tuple>

namespace NB::Traits
{
// Parameter Packs
namespace 
{
template<std::size_t N, typename... Ts> 
using index_parameter_pack_impl = typename std::tuple_element<N, std::tuple<Ts...>>::type;

template <typename T, typename... Other>
inline constexpr auto unique_type_impl = (!std::is_same_v<T, Other> && ...) && unique_type_impl<Other...>;

template <typename T>
inline constexpr auto unique_type_impl<T> = true;
}

template<typename... Args>
struct Parameters
{
    static constexpr auto Size = sizeof...(Args);
    static constexpr bool Empty = (Size == 0);
    static constexpr bool Single = (Size == 1);

    template<std::size_t I>
    requires (I < Size)
    using Get = index_parameter_pack_impl<I, Args...>;

    static constexpr bool Unique = [&]{
        if constexpr (Empty)
            return false;
        else
            return unique_type_impl<Args...>;
    }();

    template<typename T>
    static constexpr bool Has = (std::same_as<T, Args> || ...);
};
}