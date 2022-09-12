// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#include "vector_hash.hpp"
#include "vector_output.hpp"
#include "xfunctional.hpp"
#include "xnumeric.hpp"
#include "scope.hpp"

#include <iostream>
#include <iterator>
#include <stdexcept>

void test1();
void test2();

int main()
{
    test2();
    return 0;
}

void test1()
{
    std::vector<int> v;
    stdx::iota_n(std::back_inserter(v), 5, 1);
    std::cout << v << " -> " << stdx::hash_v(v) << std::endl;
}

void g(int x)
{
    if (x > 0 && x < 4)
        throw std::invalid_argument("invalid x");
}

void test2()
{
    for (int x = 0; x < 5; ++x)
    {
        try {
            std::cout << "x=" << x << ": entered" << std::endl;
            stdx::scope_exit_hook on_exit([x]() { std::cout << "x=" << x << ": exited" << std::endl; });
            stdx::scope_failure_hook on_failure([x]() { std::cout << "x=" << x << ": failed" << std::endl; });
            stdx::scope_success_hook on_success([x]() { std::cout << "x=" << x << ": success" << std::endl; });
            switch (x) {
                case 2: {
                    on_exit.reset();
                    break;
                }
                case 3: {
                    on_failure.reset();
                    break;
                }
                case 4: {
                    on_success.reset();
                    break;
                }
                default: break;
            }
            g(x);
        } catch (std::exception& ex) {
            std::cout << "x=" << x << ": error: " << ex.what() << std::endl;
        }
    }
}
