#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>
#include <Common/Types/AlbaTypeId.hpp>

namespace alba {

namespace detail {

// Purpose: Search type from list of types which have biggest size
template <class MaxType, class... Types>
struct MaxSizeTypeImpl;

template <class MaxType, class Type, class... Types>
struct MaxSizeTypeImpl<MaxType, Type, Types...> {
    using type = typeHelper::ConditionalType<
        (sizeof(MaxType) > sizeof(Type)), typename MaxSizeTypeImpl<MaxType, Types...>::type,
        typename MaxSizeTypeImpl<Type, Types...>::type>;
};

template <class MaxType>
struct MaxSizeTypeImpl<MaxType> {
    using type = MaxType;
};

template <class... Types>
struct MaxSizeType {
    using type = typename MaxSizeTypeImpl<char, Types...>::type;
};

// Purpose: Checks if all types derive from base type
template <class Base, class... Types>
struct CheckIfDerive;

template <class Base, class Derived, class... Types>
struct CheckIfDerive<Base, Derived, Types...> {
    static_assert(typeHelper::isBaseOf<Base, Derived>(), "Class in UniqueVariant does not derive from VariantDataType");
    using next = CheckIfDerive<Base, Types...>;
};

template <class Base>
struct CheckIfDerive<Base> {
    using next = void;
};

// Purpose: Checks if type is in types list
template <class Type, class... Types>
struct CheckIfInList;

template <class Type, class Head, class... Types>
struct CheckIfInList<Type, Head, Types...> {
    using type = typeHelper::ConditionalType<
        typeHelper::areSameTypes<Type, Head>(), std::integral_constant<bool, true>,
        typename CheckIfInList<Type, Types...>::type>;
};

template <class Type>
struct CheckIfInList<Type> {
    using type = std::integral_constant<bool, false>;
};

}  // namespace detail

// Purpose: Variant type base class
class BaseVariantDataType {
public:
    // rule of five or six
    BaseVariantDataType() = default;
    virtual ~BaseVariantDataType() = default;  // virtual destructor because derived classes need this
    BaseVariantDataType(BaseVariantDataType const &) = delete;
    BaseVariantDataType(BaseVariantDataType &&) noexcept = delete;
    BaseVariantDataType &operator=(BaseVariantDataType const &) = delete;
    BaseVariantDataType &operator=(BaseVariantDataType &&) noexcept = delete;
};

// Purpose: A compile-time checking unique variant class
template <class... Types>
// class [[deprecated("Use std::variant instead! (needs c++17)")]] UniqueVariant // lets remove [[deprecated]] to avoid
// unnecessary warnings
class UniqueVariant {
    using CheckIfAllClassesDerive = typename detail::CheckIfDerive<BaseVariantDataType, Types...>::next;
    using MaxSizeClass = typename detail::MaxSizeType<Types...>::type;

public:
    UniqueVariant() { allocate(); }

    ~UniqueVariant() {
        if (m_typeId != 0U) {
            delete m_ptr;
        } else {
            ::operator delete(m_ptr);
        }
    }

    UniqueVariant(UniqueVariant const &variant) = delete;
    UniqueVariant(UniqueVariant &&variant) noexcept = delete;
    UniqueVariant &operator=(UniqueVariant const &variant) = delete;
    UniqueVariant &operator=(UniqueVariant &&variant) noexcept = delete;

    template <class VariantDataType>
    VariantDataType &acquire() {
        static_assert(
            detail::CheckIfInList<VariantDataType, Types...>::type::value,
            "Aquiring type from unique variant that doesn't exists");
        constructIfNeeded<VariantDataType>();
        return getValue<VariantDataType>();
    }

    void clear() {
        if (m_typeId > 0) {
            m_ptr->~BaseVariantDataType();
        }
        m_typeId = 0;
    }

private:
    void allocate() {
        delete m_ptr;
        m_ptr = static_cast<BaseVariantDataType *>(::operator new(sizeof(MaxSizeClass)));
    }

    template <class VariantDataType>
    void constructIfNeeded() {
        if (!m_typeId) {
            placementNew<VariantDataType>();
        } else if (m_typeId != GetTypeId<VariantDataType>()) {
            m_ptr->~BaseVariantDataType();
            placementNew<VariantDataType>();
        }
    }

    template <class VariantDataType>
    void placementNew() {
        updateTypeId<VariantDataType>();
        m_ptr = static_cast<BaseVariantDataType *>(new (m_ptr) VariantDataType);
    }

    template <class VariantDataType>
    void updateTypeId() {
        m_typeId = GetTypeId<VariantDataType>();
    }

    template <class VariantDataType>
    VariantDataType &getValue() {
        return *static_cast<VariantDataType *>(m_ptr);
    }

    BaseVariantDataType *m_ptr{nullptr};
    TypeId m_typeId{};
};

}  // namespace alba
