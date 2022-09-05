// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#include "vector_hash.hpp"
#include "vector_output.hpp"
#include "xfunctional.hpp"
#include "xnumeric.hpp"

#include <iostream>
#include <iterator>

int main()
{
    std::vector<int> v;
    stdx::iota_n(std::back_inserter(v), 5, 1);
    std::cout << v << " -> " << stdx::hash_v(v) << std::endl;
    return 0;
}
