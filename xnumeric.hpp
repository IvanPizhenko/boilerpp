// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include <cstddef>

namespace stdx {

template<typename ForwardIter, typename T>
ForwardIter iota_n(ForwardIter first, std::size_t n, T value)
{
    if (n != 0) {
        *first = value;
        for (++first, --n; n != 0; ++first, --n) {
            *first = ++value;
        }
        ++first;
    }
    return first;
}

}  // namespace stdx
