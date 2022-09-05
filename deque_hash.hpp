// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "xfunctional.hpp"

#include <deque>

namespace std {

template<typename T, typename Alloc>
struct hash<deque<T, Alloc>> {
    size_t operator()(const vector<T, Alloc>& v) noexcept(stdx::is_nothrow_hash_combinable_v<T>)
    {
        return stdx::ranges::hash_v(v);
    }
};

} // namespace std
