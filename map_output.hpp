// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "range_output.hpp"

#include <map>

template <class CharT, class CharTraits,
    typename Key, typename Value, typename Compare, typename Alloc>
inline std::basic_ostream<CharT, CharTraits>& operator<<(
    std::basic_ostream<CharT, CharTraits>& os,
    const std::map<Key, Value, Compare, Alloc>& m)
{
    return stdx::ranges::output_range(os, m, CharT('{'), CharT('}'));
}
