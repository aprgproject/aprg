#include <Common/Container/AlbaUniqueVariant.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;

namespace alba {

class DestructorClass : public BaseVariantDataType {
public:
    DestructorClass() = default;
    ~DestructorClass() override { s_destructorInvoked = true; }
    DestructorClass(DestructorClass const&) = delete;
    DestructorClass(DestructorClass&&) noexcept = delete;
    DestructorClass& operator=(DestructorClass const&) = delete;
    DestructorClass& operator=(DestructorClass&&) noexcept = delete;
    static bool s_destructorInvoked;
};

bool DestructorClass::s_destructorInvoked = false;

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

TEST(AlbaUniqueVariantTest, AcquiringVariantTypeDifferentThanAlreadyInVariantInvokesDestructor) {
    // Given
    DestructorClass::s_destructorInvoked = false;

    {
        // When
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
        explicit Base(int const value) : m_value(value) {}
        ~Base() override = default;  // 'virtual' is redundant since the function is already declared 'override'
        Base(Base const&) = delete;
        Base(Base&&) noexcept = delete;
        Base& operator=(Base const&) = delete;
        Base& operator=(Base&&) noexcept = delete;
        [[nodiscard]] virtual int getValue() const { return m_value; }
    };

    class Derived : public Base {
    public:
        Derived() : Base(0) {}
        ~Derived() override = default;
        Derived(Derived const&) = delete;
        Derived(Derived&&) noexcept = delete;
        Derived& operator=(Derived const&) = delete;
        Derived& operator=(Derived&&) noexcept = delete;
        [[nodiscard]] int getValue() const override { return valueFromTest; }
    };

    // When
    UniqueVariant<Derived> variant;
    Base const& baseRef = variant.acquire<Derived>();

    // Then
    EXPECT_EQ(valueFromTest, baseRef.getValue());
}

}  // namespace alba
