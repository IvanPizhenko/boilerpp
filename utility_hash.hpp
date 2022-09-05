// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "xfunctional.hpp"

#include <utility>

namespace std {

template<typename First, typename Second>
struct hash<pair<First, Second>> {
    size_t operator()(const pair<First, Second>& p)
        noexcept(stdx::is_nothrow_hashable_v<First> && stdx::is_nothrow_hash_combinable_v<Second>)
    {
        return stdx::hash_val(p.first, p.second);
    }
};

} // namespace std
