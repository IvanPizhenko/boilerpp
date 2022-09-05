// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "utility_hash.hpp"

#include <map>

namespace std {

template<typename Key, typename Value, typename Compare, typename Alloc>
struct hash<map<Key, Value, Compare, Alloc>> {
    using ContainerT = map<Key, Value, Compare, Alloc>;
    size_t operator()(const ContainerT& v) noexcept(stdx::is_nothrow_hash_combinable_v<typename ContainerT::value_type>)
    {
        return stdx::ranges::hash_v(v);
    }
};

} // namespace std
