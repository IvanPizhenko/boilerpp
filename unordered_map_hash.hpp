// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include "utility_hash.hpp"

#include <unordered_map>
#include <vector>

namespace std {

template<typename Key, typename Value, typename Hash, typename Eq, typename Alloc>
struct hash<unordered_map<Key, Value, Hash, Eq, Alloc>> {
    using ContainerT = std::unordered_map<Key, Value, Hash, Eq, Alloc>;
    using IterT = typename ContainerT::const_iterator;
    size_t operator()(const ContainerT& v)
    {
        if (!v.empty()) {
            std::vector<IterT> vs;
            vs.reserve(v.size());
            for (auto it = v.cbegin(); it != v.cend(); ++it)
                vs.push_back(it);
            std::sort(vs.begin(), vs.end(), [](const auto& lhs, const auto& rhs) {
                return lhs->first < rhs->first;
            });
            return stdx::ranges::hash_v(vs, [](const auto& iter) {
                return stdx::hash_v(*iter);
            });
        }
        return 0;
    }
};

} // namespace std
