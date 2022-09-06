// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include <iterator>

// Partially derived from:
// https://raw.githubusercontent.com/HowardHinnant/hash_append/master/n3876.h

//-------------------------------- n3876.h -------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

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

template <typename T, typename Hash = std::hash<T>>
inline std::size_t hash_v(const T& x, Hash h = Hash{}) noexcept(is_nothrow_hashable_v<T, Hash>)
{
    return h(x);
}

inline std::size_t hash_v_combine(const std::size_t seed, const std::size_t v) noexcept
{
    static_assert(
        sizeof(std::size_t) == 2
        || sizeof(std::size_t) == 4
        || sizeof(std::size_t) == 8,
        "Unsupported sizeof(std::size_t)"
    );
    if constexpr (sizeof(std::size_t) == 2) {
        return seed ^ (v + 0x9e37 + (seed << 3) + (seed >> 1));
    } else if constexpr (sizeof(std::size_t) == 4) {
        return seed ^ (v + 0x9e3779b9 + (seed << 6) + (seed >> 2));
    } else if constexpr (sizeof(std::size_t) == 8) {
        return seed ^ (v + 0x9e3779b97f4a7c15 + (seed << 12) + (seed >> 4));
    } else {
        return 0;
    }
}

inline void hash_combine(std::size_t&) noexcept
{
}

template <typename T, typename Hash = std::hash<T>>
inline void hash_combine(std::size_t& seed, const T& val)
    noexcept(is_nothrow_hash_combinable_v<T, Hash>)
{
    seed = hash_v_combine(seed, hash_v<T, Hash>(val));
}

template <typename T, typename... Types>
inline void hash_combine(std::size_t& seed, const T& val, const Types&... args)
    noexcept(is_nothrow_hash_combinable_v<T>)
{
    hash_combine(seed, val);
    hash_combine(seed, args...);
}

template<typename ForwardIter, typename Sentinel>
void hash_combine_range(std::size_t& seed, ForwardIter first, const Sentinel last)
    noexcept(is_nothrow_hash_combinable_v<std::iter_value_t<ForwardIter>>)
{
    for (; first != last; ++first) {
        hash_combine(seed, *first);
    }
}

template<typename ForwardIter, typename Sentinel, typename Hash>
void hash_combine_range(std::size_t& seed, ForwardIter first, const Sentinel last, Hash h)
    noexcept(is_nothrow_hash_combinable_v<std::iter_value_t<ForwardIter>, Hash>)
{
    for (; first != last; ++first) {
        seed = hash_v_combine(seed, h(*first));
    }
}

template <typename... Types>
inline std::size_t hash_v(const Types&... args) noexcept(is_nothrow_hash_combinable_v<Types...>)
{
    std::size_t seed = 0;
    hash_combine(seed, args...);
    return seed;
}

template <typename ForwardIt, typename Sentinel>
inline std::size_t hash_v_range(ForwardIt first, Sentinel last)
    noexcept(is_nothrow_hashable_v<std::iter_value_t<ForwardIt>>)
{
    std::size_t seed = 0;
    hash_combine_range(seed, std::forward<ForwardIt>(first), std::forward<Sentinel>(last));
    return seed;
}

namespace ranges {

template<typename Range>
inline void hash_combine_range(std::size_t& seed, const Range& r)
    noexcept(
        is_nothrow_hash_combinable_v<
            std::iter_value_t<std::invoke_result_t<decltype(std::cbegin<Range>), const Range&>>>)
{
    ::stdx::hash_combine_range(seed, std::cbegin(r), std::cend(r));
}

template<typename Range, typename Hash>
inline void hash_combine_range(std::size_t& seed, const Range& r, Hash h)
    noexcept(
        is_nothrow_hash_combinable_v<
            std::iter_value_t<std::invoke_result_t<decltype(std::cbegin<Range>), const Range&>>, Hash>)
{
    ::stdx::hash_combine_range(seed, std::cbegin(r), std::cend(r), std::forward<Hash>(h));
}

template <typename Range>
inline std::size_t hash_v_range(const Range& r)
    noexcept(
        is_nothrow_hashable_v<
            std::iter_value_t<std::invoke_result_t<decltype(std::cbegin<Range>), const Range&>>>)
{
    return ::stdx::hash_v_range(std::cbegin(r), std::cend(r));
}

template <typename Range>
inline std::size_t hash_v(const Range& r)
    noexcept(
        is_nothrow_hashable_v<
            std::iter_value_t<std::invoke_result_t<decltype(std::cbegin<Range>), const Range&>>>)
{
    return hash_v_range(r);
}

} // namespace 

}  // namespace stdx
