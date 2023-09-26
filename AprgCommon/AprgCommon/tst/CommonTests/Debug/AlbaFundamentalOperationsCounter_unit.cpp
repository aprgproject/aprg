#include <Common/Debug/AlbaFundamentalOperationsCounter.hpp>

#include <gtest/gtest.h>

#include <memory>

using namespace std;

namespace alba {

namespace original {

class SampleClass {
public:
    SampleClass() = default;
    explicit SampleClass(int const data) : m_dataPointer(make_unique<int>(data)) {}
    ~SampleClass() = default;
    SampleClass(SampleClass const& parameter) : m_dataPointer(make_unique<int>(*parameter.m_dataPointer)) {}
    SampleClass(SampleClass&& parameter) noexcept : m_dataPointer(std::move(parameter.m_dataPointer)) {}

    SampleClass& operator=(SampleClass const& parameter) {
        if (this != &parameter) {
            m_dataPointer = make_unique<int>(*parameter.m_dataPointer);
        }
        return *this;
    }

    SampleClass& operator=(SampleClass&& parameter) noexcept {
        m_dataPointer = std::move(parameter.m_dataPointer);
        return *this;
    }

    unique_ptr<int> m_dataPointer;
};

}  // namespace original

inline namespace withCounter {
// [SampleClass with counter]
// inline this namespace to hoist it up and replace the [SampleClass] with the
using SampleClass = AlbaFundamentalOperationsCounter<original::SampleClass>;
using CountsForSampleClass = AlbaFundamentalOperationsCounts<original::SampleClass>;
}  // namespace withCounter

namespace {

SampleClass getRValue() {
    SampleClass namedReturnedObject(5678);
    return namedReturnedObject;
}

}  // namespace

TEST(AlbaFundamentalOperationsCounterTest, UserConstructionIsCounted) {
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass const object(1234);

    EXPECT_EQ(
        "userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 "
        "copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
        CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, DefaultConstructionIsCounted) {
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass const object;

    EXPECT_EQ(
        "userConstructionCount: 0 defaultConstructionCount: 1 destructionCount: 0 copyConstructionCount: 0 "
        "copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
        CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, DestructionIsCounted) {
    CountsForSampleClass::getInstance().resetCounts();

    { SampleClass const object; }

    EXPECT_EQ(
        "userConstructionCount: 0 defaultConstructionCount: 1 destructionCount: 1 copyConstructionCount: 0 "
        "copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
        CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, CopyConstructionIsCounted) {
    // NOLINTNEXTLINE(misc-const-correctness)
    SampleClass originalObject(1234);
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass const object(originalObject);

    EXPECT_EQ(
        "userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 "
        "copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
        CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, CopyAssignmentIsCounted) {
    SampleClass const originalObject(1234);
    SampleClass object(5678);
    CountsForSampleClass::getInstance().resetCounts();

    object = originalObject;

    EXPECT_EQ(
        "userConstructionCount: 0 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 "
        "copyAssignmentCount: 1 moveConstructionCount: 0 moveAssignmentCount: 0",
        CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, MoveConstructionIsCounted) {
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass const object(getRValue());

    EXPECT_EQ(
        "userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 "
        "copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
        CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, MoveAssignmentIsCounted) {
    SampleClass const originalObject(1234);
    SampleClass object(5678);
    CountsForSampleClass::getInstance().resetCounts();

    object = getRValue();

    EXPECT_EQ(
        "userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 1 copyConstructionCount: 0 "
        "copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 1",
        CountsForSampleClass::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, ObjectIsConstructedOnceDueToRvo) {
    CountsForSampleClass::getInstance().resetCounts();

    SampleClass const object(getRValue());

    EXPECT_EQ(
        "userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 "
        "copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
        CountsForSampleClass::getInstance().getReport());
}

}  // namespace alba
