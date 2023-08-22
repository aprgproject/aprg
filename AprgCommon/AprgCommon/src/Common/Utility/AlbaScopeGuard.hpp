#pragma once

#include <functional>

namespace alba {

class AlbaScopeGuard {
public:
    using OnExitFunction = std::function<void(void)>;

    explicit AlbaScopeGuard(OnExitFunction const& functionParameter);
    explicit AlbaScopeGuard(OnExitFunction&& functionParameter);
    ~AlbaScopeGuard() noexcept;
    AlbaScopeGuard(AlbaScopeGuard const& scopeGuard) = delete;
    AlbaScopeGuard(AlbaScopeGuard&& scopeGuard) = delete;
    AlbaScopeGuard& operator=(AlbaScopeGuard const& scopeGuard) = delete;
    AlbaScopeGuard& operator=(AlbaScopeGuard&& scopeGuard) = delete;

    void operator()();

private:
    OnExitFunction m_onExitFunction;
};

}  // namespace alba
