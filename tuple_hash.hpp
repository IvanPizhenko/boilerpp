// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "xfunctional.hpp"

#include <tuple>

namespace std {

template<typename... Types>
struct hash<tuple<Types...>> {
    size_t operator()(const tuple<Types...>& t)
        noexcept(
            stdx::is_nothrow_hashable_v<stdx::type_pack_element<0, Types...>>
            && (
                sizeof...(Types) == 1
                || stdx::is_nothrow_hash_combinable_v<stdx::type_pack_subrange<1, Types...>...>
            )
        )
    {
        size_t result = 0;
        apply([&result](auto&&... args) {
            (stdx::hash_combine(result, args), ...);
        }, t);
        return result;
    }
};

} // namespace std
