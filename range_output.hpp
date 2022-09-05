// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include <ostream>

namespace stdx {

template <typename CharT, typename CharTraits, typename ForwardIter, typename Sentinel>
std::basic_ostream<CharT, CharTraits>& output_range(
    std::basic_ostream<CharT, CharTraits>& os,
    ForwardIter first,
    Sentinel last,
    CharT opening_brace = CharT('['),
    CharT closing_brace = CharT(']'))
{
    os << opening_brace;
    bool is_first = true;
    for (; first != last; ++first) {
        if (!is_first) os << CharT(',') << CharT(' ');
        os << *first;
        is_first = false;
    }
    return os << closing_brace;
}

namespace ranges {

template <typename CharT, typename CharTraits, typename Range>
std::basic_ostream<CharT, CharTraits>& output_range(
    std::basic_ostream<CharT, CharTraits>& os,
    const Range& r,
    CharT opening_brace = CharT('['),
    CharT closing_brace = CharT(']'))
{
    return ::stdx::output_range(os, std::cbegin(r), std::cend(r), opening_brace, closing_brace);
}

}  // namespace ranges

}  // namespace stdx
