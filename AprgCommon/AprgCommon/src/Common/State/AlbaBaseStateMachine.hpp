#pragma once

#include <cassert>

namespace alba {

template <typename State, typename Input>
class AlbaBaseStateMachine {
public:
    explicit AlbaBaseStateMachine(State const initialState) : m_state(initialState) {}
    virtual ~AlbaBaseStateMachine() = default;  // virtual destructor because of virtual functions (vtable exists)
    AlbaBaseStateMachine(AlbaBaseStateMachine const &stateMachine) = default;
    AlbaBaseStateMachine(AlbaBaseStateMachine &&stateMachine) noexcept = default;
    AlbaBaseStateMachine &operator=(AlbaBaseStateMachine const &stateMachine) = default;
    AlbaBaseStateMachine &operator=(AlbaBaseStateMachine &&stateMachine) noexcept = default;
    virtual void processInput(Input const &) = 0;
    [[nodiscard]] State getState() const { return m_state; }

protected:
    virtual void saveNextState(State const newState) { m_state = newState; }
    State m_state;
};

// This different from the "State" design pattern.

}  // namespace alba
