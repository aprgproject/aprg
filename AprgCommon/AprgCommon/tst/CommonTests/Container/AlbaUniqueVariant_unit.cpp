#include <Common/Container/AlbaUniqueVariant.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;

namespace alba {

TEST(AlbaUniqueVariantTest, AcquiringVariantTypeInvokesDefaultConstructor) {
    // Given
    struct ExampleStructure1 : public BaseVariantDataType {
        ExampleStructure1() = default;

        uint8_t unsignedField{2};
        float floatField{2.3};
    };

    struct ExampleStructure2 : public BaseVariantDataType {
        ExampleStructure2() = default;

        double doubleField{4.5};
        char charField{'a'};
    };

    // When
    UniqueVariant<ExampleStructure1, ExampleStructure2> variant;

    // Then
    auto& exampleStructure1 = variant.acquire<ExampleStructure1>();
    EXPECT_EQ(2U, exampleStructure1.unsignedField);
    EXPECT_FLOAT_EQ(2.3F, exampleStructure1.floatField);
#if !defined(_MSC_VER)
    auto& exampleStructure2 = variant.acquire<ExampleStructure2>();
    EXPECT_DOUBLE_EQ(4.5, exampleStructure2.doubleField);
    EXPECT_EQ('a', exampleStructure2.charField);
#endif
}

class DestructorClass : public BaseVariantDataType {
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
        UniqueVariant<DestructorClass, BaseVariantDataType> variant;
        variant.acquire<DestructorClass>();
        variant.acquire<BaseVariantDataType>();
    }

    // Then
    EXPECT_TRUE(DestructorClass::s_destructorInvoked);
}

TEST(AlbaUniqueVariantTest, PolymorphismIsSupportedByUniqueVariant) {
    // Given
    constexpr int valueFromTest = 467;

    class Base : public BaseVariantDataType {
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
    EXPECT_EQ(valueFromTest, baseRef.getValue());
}

}  // namespace alba
