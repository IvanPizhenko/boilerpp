#pragma once

#if __cplusplus < 201703L
#error scope.hpp requires C++17.
#endif

namespace stdx {

template<typename F>
class scope_exit_hook {
public:
    scope_exit_hook(F&& f) : m_f(std::move(f)) {}
    scope_exit_hook(const scope_exit_hook& src) = delete;
    ~scope_exit_hook() noexcept { if (m_active) m_f(); }
    scope_exit_hook& operator=(const scope_exit_hook& src) = delete;
    void reset() noexcept { m_active = false; }
private:
    F m_f;
    bool m_active = true;
};

template<typename F>
class scope_success_hook {
public:
    scope_success_hook(F&& f) : m_f(std::move(f)) {}
    scope_success_hook(const scope_success_hook& src) = delete;
    ~scope_success_hook() noexcept { if (m_active && std::uncaught_exceptions() == m_initial_count) m_f(); }
    scope_success_hook& operator=(const scope_success_hook& src) = delete;
    void reset() noexcept { m_active = false; }
private:
    F m_f;
    const int m_initial_count = std::uncaught_exceptions();
    bool m_active = true;
};

template<typename F>
class scope_failure_hook {
public:
    scope_failure_hook(F&& f) : m_f(std::move(f)) {}
    scope_failure_hook(const scope_failure_hook& src) = delete;
    ~scope_failure_hook() noexcept { if (m_active && std::uncaught_exceptions() > m_initial_count) m_f(); }
    scope_failure_hook& operator=(const scope_failure_hook& src) = delete;
    void reset() noexcept { m_active = false; }
private:
    F m_f;
    const int m_initial_count = std::uncaught_exceptions();
    bool m_active = true;
};

}  // namespace stdx
