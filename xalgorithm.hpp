// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2022, Ivan Pizhenko < ivan dot pizhenko at gmail dot com >. All rights reserved.

#pragma once

#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace stdx {

// std::list to something

template<class T1, class Alloc1, class F, class T2, class Alloc2 = std::allocator<T2>>
std::list<T2, Alloc2> map(const std::list<T1, Alloc1>& src, F&& f)
{
    std::list<T2, Alloc2> result;
    for (const auto& e: src) {
        result.push_back(f(e));
    }
    return result;
}

template<class T1, class Alloc1, class F, class T2, class Alloc2 = std::allocator<T2>>
std::vector<T2, Alloc2> map_to_vector(const std::list<T1, Alloc1>& src, F&& f)
{
    std::vector<T2, Alloc2> result;
    if (!src.empty()) {
        for (const auto& e: src) {
            result.push_back(f(e));
        }
    }
    return result;
}

// std::vector to something

template<class T1, class Alloc1, class F, class T2, class Alloc2 = std::allocator<T2>>
std::vector<T2, Alloc2> map(const std::vector<T1, Alloc1>& src, F&& f)
{
    std::vector<T2, Alloc2> result;
    if (!src.empty()) {
        result.reserve(src.size());
        for (const auto& e: src) {
            result.push_back(f(e));
        }
    }
    return result;
}

template<class T1, class Alloc1, class F, class T2, class Alloc2 = std::allocator<T2>>
std::list<T2, Alloc2> map_to_list(const std::vector<T1, Alloc1>& src, F&& f)
{
    std::list<T2, Alloc2> result;
    for (const auto& e: src) {
        result.push_back(f(e));
    }
    return result;
}

template<class T1, class Alloc1, class F, class T2, class Compare2, class Alloc2 = std::allocator<T2>>
std::set<T2, Compare2, Alloc2> map_to_set(const std::vector<T1, Alloc1>& src, F&& f)
{
    std::set<T2, Compare2, Alloc2> result;
    for (const auto& e: src) {
        result.push_back(f(e));
    }
    return result;
}

// std::set to something

template<class T1, class Compare1, class Alloc1, class F, class T2, class Compare2, class Alloc2 = std::allocator<T2>>
std::set<T2, Compare2, Alloc2> map_value(const std::set<T1, Compare1, Alloc1>& src, F&& f)
{
    std::set<T2, Compare2, Alloc2> result;
    for (const auto& e: src) {
        result.insert(f(e));
    }
    return result;
}

template<class T1, class Compare1, class Alloc1, class F, class T2, class Alloc2 = std::allocator<T2>>
std::vector<T2, Alloc2> map_to_vector(const std::set<T1, Compare1, Alloc1>& src, F&& f)
{
    std::vector<T2, Alloc2> result;
    if (!src.empty()) {
        result.reserve(src.size());
        for (const auto& e: src) {
            result.push_back(f(e));
        }
    }
    return result;
}

// std::map to something

template<
    class Key,
    class Value1,
    class Compare,
    class Alloc1,
    class F,
    class Value2,
    class Alloc2 = std::map<Key, Value2, Compare>::allocator>
std::map<Key, Value2, Compare, Alloc2> map_values(const std::map<Key, Value1, Compare, Alloc1>& src, F&& f)
{
    std::map<Key, Value2, Compare, Alloc2> result;
    for (const auto& e: src) {
        result.emplace(e.first, f(e.second));
    }
    return result;
}

template<
    class Key1,
    class Value,
    class Compare1,
    class Alloc1,
    class F,
    class Key2,
    class Compare2,
    class Alloc2 = std::map<Key2, Value, Compare2>::allocator>
std::map<Key1, Value, Compare2, Alloc2> map_keys(const std::map<Key1, Value, Compare1, Alloc1>& src, F&& f)
{
    std::map<Key2, Value, Compare2, Alloc2> result;
    for (const auto& e: src) {
        result.emplace(f(e.first), e.second);
    }
    return result;
}

template<
    class Key1,
    class Value,
    class Compare1,
    class Alloc1,
    class F,
    class Key2,
    class Compare2,
    class Alloc2 = std::map<Key2, Value, Compare2>::allocator>
std::map<Key1, Value, Compare2, Alloc2> map_keys(std::map<Key1, Value, Compare1, Alloc1>&& src, F&& f)
{
    std::map<Key2, Value, Compare2, Alloc2> result;
    for (const auto& e: src) {
        result.emplace(f(e.first), std::move(e.second));
    }
    return result;
}

template<
    class Key1,
    class Value1,
    class Compare1,
    class Alloc1,
    class F,
    class Key2,
    class Alloc2 = std::allocator<Key2>>
std::vector<Key2, Alloc2> map_keys_to_vector(const std::map<Key1, Value1, Compare1, Alloc1>& src, F&& f)
{
    std::vector<Key2, Alloc2> result;
    if (!src.empty()) {
        result.reserve(src.size());
        for (const auto& e: src) {
            result.push_back(f(e.first));
        }
    }
    return result;
}

template<
    class T1, class Hash1, class Eq1, class Alloc1,
    class F, class T2, class Hash2, class Eq2, class Alloc2 = std::allocator<T2>>
std::unordered_set<T2, Hash2, Eq2, Alloc2> map(const std::unordered_set<T1, Hash1, Eq1, Alloc1>& src, F&& f)
{
    std::unordered_set<T2, Hash2, Eq2, Alloc2> result;
    for (const auto& e: src) {
        result.insert(f(e));
    }
    return result;
}

}  // namespace stdx
