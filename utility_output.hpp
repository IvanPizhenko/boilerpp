// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include <ostream>
#include <utility>

template<typename First, typename Second>
inline std::ostream& operator<<(std::ostream& os, const std::pair<First, Second>& p)
{
    return os << '{' << p.first << ", " << p.second << '}';
}
