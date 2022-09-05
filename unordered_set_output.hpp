// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "range_output.hpp"

#include <unordered_set>

template <class CharT, class CharTraits,
    typename Key, typename Hash, typename Eq, typename Alloc>
inline std::basic_ostream<CharT, CharTraits>& operator<<(
    std::basic_ostream<CharT, CharTraits>& os,
    const std::unordered_set<Key, Hash, Eq, Alloc>& s)
{
    return stdx::ranges::output_range(os, s, CharT('{'), CharT('}'));
}
