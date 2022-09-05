// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "xfunctional.hpp"

#include <set>

namespace std {

template<typename Key, typename Compare, typename Alloc>
struct hash<set<Key, Compare, Alloc>> {
    size_t operator()(const set<Key, Compare, Alloc>& v) noexcept(stdx::is_nothrow_hash_combinable_v<T>)
    {
        return stdx::ranges::hash_v(v);
    }
};

} // namespace std
