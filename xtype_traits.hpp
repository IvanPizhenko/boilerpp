// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include <functional>
#include <type_traits>

namespace stdx {

template<typename T, typename Hash = std::hash<T>>
struct is_nothrow_hashable {
    static constexpr bool value = noexcept(Hash::operator());
};

template<typename T, typename Hash = std::hash<T>>
inline constexpr bool is_nothrow_hashable_v = is_nothrow_hashable<T, Hash>::value;

template<class T, class Hash = std::hash<T>>
struct is_nothrow_hash_combinable {
    static constexpr bool value =
        std::is_nothrow_constructible_v<Hash>
        && stdx::is_nothrow_hashable_v<T, Hash>;
};

template<class T, class Hash = std::hash<T>>
inline constexpr bool is_nothrow_hash_combinable_v = is_nothrow_hash_combinable<T, Hash>::value;

// type_pack_element
// @see http://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/

#ifdef __clang__

template <std::size_t Index, typename ...Types>
using nth_element_t = __type_pack_element<Index, Types...>;

#else

namespace detail {

template <std::size_t Index, typename T>
struct indexed {
    using type = T;
};

template <typename Indices, typename ...Types>
struct indexer;

template <std::size_t ...Indices, typename ...Types>
struct indexer<std::index_sequence<Indices...>, Types...>: indexed<Indices, Types>...
{
};

template <std::size_t Index, typename T>
static indexed<Index, T> select(indexed<Index, T>);

}  // namespace detail

template <std::size_t Index, typename ...Types>
using type_pack_element =
    typename decltype(select<Index>(detail::indexer<std::index_sequence_for<Types...>, Types...>{}))::type;

#endif


// type_pack_subrange
// @see https://stackoverflow.com/a/45172773/1540501

namespace detail {

template<std::size_t N, typename... Types, std::size_t... Indices>
std::tuple<std::tuple_element_t<N + Indices, std::tuple<Types...>>...>
subrange_helper(std::index_sequence<Indices...>);

} // namespace detail

template<std::size_t N, typename... Types>
using type_pack_subrange = decltype(
    detail::subrange_helper<N, Types...>(std::make_index_sequence<sizeof...(Types) - N>{})
);

}  // namespace stdx
