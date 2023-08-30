#include <Common/Container/AlbaUniqueVariant.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;

namespace alba {

TEST(AlbaUniqueVariantTest, AcquiringVariantTypeInvokesDefaultConstructor) {
    // Given
    struct ExampleStructure1 : public VariantDataType {
        ExampleStructure1() = default;

        uint8_t unsignedField{};
        float floatField{};
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
    ASSERT_FLOAT_EQ(0.F, exampleStructure1.floatField);
    ASSERT_TRUE(isAlmostEqual(0.0, exampleStructure2.doubleField));
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
    DestructorClass::s_destructorInvoked = false;

    // When
    {
        UniqueVariant<DestructorClass, VariantDataType> variant;
        variant.acquire<DestructorClass>();
        variant.acquire<VariantDataType>();
    }

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
