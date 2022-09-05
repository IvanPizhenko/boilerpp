// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include <concepts>
#include <utility>

namespace stdx {

template <typename C, typename T>
concept pushable_back = requires (C c, T t) {
    c.push_back(t);
};

}  // namespace stdx
