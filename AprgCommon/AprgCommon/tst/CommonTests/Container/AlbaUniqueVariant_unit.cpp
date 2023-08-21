#include <Common/Container/AlbaUniqueVariant.hpp>

#include <gtest/gtest.h>

namespace alba {

TEST(AlbaUniqueVariantTest, AcquiringVariantTypeInvokesDefaultConstructor) {
    // Given
    struct ExampleStructure1 : public VariantDataType {
        ExampleStructure1() = default;

        uint8_t unsignedField{};
        float floatField{0.F};
    };

    struct ExampleStructure2 : public VariantDataType {
        ExampleStructure2() = default;

        double doubleField{};
        char charField{};
    };

    UniqueVariant<ExampleStructure1, ExampleStructure2> variant;

    // When
    auto& exampleStructure1 = variant.acquire<ExampleStructure1>();
    auto& exampleStructure2 = variant.acquire<ExampleStructure2>();

    // Then
    ASSERT_EQ(0U, exampleStructure1.unsignedField);
    // ASSERT_FLOAT_EQ(0.F, exampleStructure1.floatField); // commented out because of warning: 4th function call
    // argument is an uninitialized value [clang-analyzer-core.CallAndMessage]
    ASSERT_DOUBLE_EQ(0.0, exampleStructure2.doubleField);
    ASSERT_EQ('\0', exampleStructure2.charField);
}

class DestructorClass : public VariantDataType {
public:
    static bool s_destructorInvoked;

    DestructorClass() = default;
    DestructorClass(DestructorClass const&) = delete;
    DestructorClass& operator=(DestructorClass const&) = delete;
    DestructorClass(DestructorClass&&) = delete;
    DestructorClass& operator=(DestructorClass&&) = delete;

    ~DestructorClass() override { s_destructorInvoked = true; }
};
bool DestructorClass::s_destructorInvoked = false;

TEST(AlbaUniqueVariantTest, AcquiringVariantTypeDifferentThanAlreadyInVariantInvokesDestructor) {
    // Given
    UniqueVariant<DestructorClass, VariantDataType> variant;

    // When
    variant.acquire<DestructorClass>();
    variant.acquire<VariantDataType>();

    // Then
    ASSERT_TRUE(DestructorClass::s_destructorInvoked);
}

TEST(AlbaUniqueVariantTest, PolymorphismIsSupportedByUniqueVariant) {
    // Given
    constexpr int valueFromTest = 467;

    class Base : public VariantDataType {
        int m_value;

    public:
        explicit Base(int value) : m_value(value) {}
        Base(Base const&) = delete;
        Base& operator=(Base const&) = delete;
        Base(Base&&) = delete;
        Base& operator=(Base&&) = delete;
        ~Base() override = default;  // 'virtual' is redundant since the function is already declared 'override'

        [[nodiscard]] virtual int getValue() const { return m_value; }
    };

    class Derived : public Base {
    public:
        Derived() : Base(0) {}
        Derived(Derived const&) = delete;
        Derived& operator=(Derived const&) = delete;
        Derived(Derived&&) = delete;
        Derived& operator=(Derived&&) = delete;
        ~Derived() override = default;

        [[nodiscard]] int getValue() const override { return valueFromTest; }
    };

    // When
    UniqueVariant<Derived> variant;
    Base& baseRef = variant.acquire<Derived>();

    // Then
    ASSERT_EQ(valueFromTest, baseRef.getValue());
}

}  // namespace alba
