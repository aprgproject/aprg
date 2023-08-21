#pragma once

#include <functional>

namespace alba {

class AlbaScopeGuard {
public:
    using OnExitFunction = std::function<void(void)>;

    explicit AlbaScopeGuard(OnExitFunction const& functionParameter);
    explicit AlbaScopeGuard(OnExitFunction&& functionParameter);
    ~AlbaScopeGuard() noexcept;

    void operator()();

private:
    OnExitFunction m_onExitFunction;
};

}  // namespace alba
