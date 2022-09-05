// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "xfunctional.hpp"

#include <array>

namespace std {

template<typename T, size_t N>
struct hash<array<T, N>> {
    size_t operator()(const array<T, N>& v) noexcept(stdx::is_nothrow_hash_combinable_v<T>)
    {
        return stdx::ranges::hash_v(v);
    }
};

} // namespace std
