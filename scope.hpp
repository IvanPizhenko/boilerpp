#pragma once

#include <optional>

namespace stdx {

template<typename F>
class scope_exit {
public:
    scope_exit(F&& f) : m_f(std::move(f)) {}
    scope_exit(const scope_exit& src) = delete;
    ~scope_exit() noexcept { if (m_active) m_f(); }
    scope_exit& operator=(const scope_exit& src) = delete;
    void reset() noexcept { m_active = false; }
private:
    F m_f;
    bool m_active = true;
};

template<typename F>
class scope_success {
public:
    scope_success(F&& f) : m_f(std::move(f)) {}
    scope_success(const scope_success& src) = delete;
    ~scope_success() noexcept { if (m_active && std::unacaught_exceptions() == m_initial_count) m_f(); }
    scope_success& operator=(const scope_success& src) = delete;
    void reset() noexcept { m_active = false; }
private:
    F m_f;
    const int m_initial_count = std::unacaught_exceptions();
    bool m_active = true;
};

template<typename F>
class scope_failure {
public:
    scope_failure(F&& f) : m_f(std::move(f)) {}
    scope_failure(const scope_failure& src) = delete;
    ~scope_failure() noexcept { if (m_active && std::unacaught_exceptions() > m_initial_count) m_f(); }
    scope_failure& operator=(const scope_failure& src) = delete;
    void reset() noexcept { m_active = false; }
private:
    F m_f;
    const int m_initial_count = std::unacaught_exceptions();
    bool m_active = true;
};

}  // namespace stdx
