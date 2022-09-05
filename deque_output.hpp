// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "range_output.hpp"

#include <deque>

template <class CharT, class CharTraits, typename T, typename Alloc>
inline std::basic_ostream<CharT, CharTraits>& operator<<(
    std::basic_ostream<CharT, CharTraits>& os,
    const std::deque<T, Alloc>& d)
{
    return stdx::ranges::output_range(os, d);
}
