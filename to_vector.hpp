#pragma once

#include <vector>

namespace stdx {

template<typename Range, typename T, typename Alloc=std::allocator<T>>
auto to_vector()
{
    return [](const Range& range) {
        std::vector<T, Alloc> result;
        result.reserve(std::distance(std::cbegin(range), std::cend(range)));
        for (const auto& e: range)
            result.emplace_back(e);
        return result;
    };
}

}  // namespace stdx
