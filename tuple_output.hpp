// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include <ostream>
#include <tuple>

template <typename CharT, typename CharTraits, typename... Types>
std::basic_ostream<CharT, CharTraits>& operator<<(
    std::basic_ostream<CharT, CharTraits>& os,
    const std::tuple<Types...>& t)
{
    os << '(';
    bool first = true;
    std::apply([&os, &first](auto&&... args) {
        auto output = [&] (auto&& val) {
            if (!first) os << CharT(',') << CharT(' ');
            os << val;
            first = false;
        };
        (output(args), ...);
    }, t);
    return os << ')';
}
