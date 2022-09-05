// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "range_output.hpp"

#include <array>

template <class CharT, class CharTraits, typename T, std::size_t N>
inline std::basic_ostream<CharT, CharTraits>& operator<<(
    std::basic_ostream<CharT, CharTraits>& os,
    const std::array<T, N>& a)
{
    return stdx::ranges::output_range(os, a);
}
