#pragma once

#include <concepts>
#include <utility>

namespace stdx {

template <typename C, typename T>
concept pushable_back = requires (C c, T t) {
    c.push_back(t);
};

}  // namespace stdx
