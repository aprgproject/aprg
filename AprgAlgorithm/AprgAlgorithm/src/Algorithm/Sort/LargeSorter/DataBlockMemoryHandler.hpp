#pragma once

#include <deque>

namespace alba::algorithm {

template <typename ObjectToSort>
using DataBlockMemoryContainer = std::deque<ObjectToSort>;

template <typename ObjectToSort>
class DataBlockMemoryHandler {
    using MemoryContainer = DataBlockMemoryContainer<ObjectToSort>;

public:
    [[nodiscard]] MemoryContainer const& getContainerConstReference() const { return m_DataBlockMemoryContainer; }
    void add(ObjectToSort const& objectToSort) { m_DataBlockMemoryContainer.push_back(objectToSort); }
    void addAtTheStart(ObjectToSort const& objectToSort) { m_DataBlockMemoryContainer.push_front(objectToSort); }
    MemoryContainer& getContainerReference() { return m_DataBlockMemoryContainer; }

private:
    MemoryContainer m_DataBlockMemoryContainer;
};

}  // namespace alba::algorithm
