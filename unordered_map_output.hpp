// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "range_output.hpp"

#include <unordered_map>

template <class CharT, class CharTraits,
    typename Key, typename Value, typename Hash, typename Eq, typename Alloc>
inline std::basic_ostream<CharT, CharTraits>& operator<<(
    std::basic_ostream<CharT, CharTraits>& os,
    const std::unordered_map<Key, Value, Hash, Eq, Alloc>& m)
{
    return stdx::ranges::output_range(os, m, CharT('{'), CharT('}'));
}
