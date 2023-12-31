#pragma once

#include <Common/Container/AlbaSingleton.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>
#include <sstream>
#include <utility>

namespace alba {

template <typename TypeToShadow>
struct AlbaFundamentalOperationsCounts : public AlbaSingleton<AlbaFundamentalOperationsCounts<TypeToShadow>> {

struct Counts {
size_t userConstructionCount;
size_t defaultConstructionCount;
size_t destructionCount;
size_t copyConstructionCount;
size_t copyAssignmentCount;
size_t moveConstructionCount;
size_t moveAssignmentCount;
};

[[nodiscard]] std::string getReport() const {
        std::stringstream outputStream;
        outputStream << "userConstructionCount: " << counts.userConstructionCount;
        outputStream << " defaultConstructionCount: " << counts.defaultConstructionCount;
        outputStream << " destructionCount: " << counts.destructionCount;
        outputStream << " copyConstructionCount: " << counts.copyConstructionCount;
        outputStream << " copyAssignmentCount: " << counts.copyAssignmentCount;
        outputStream << " moveConstructionCount: " << counts.moveConstructionCount;
        outputStream << " moveAssignmentCount: " << counts.moveAssignmentCount;
        return outputStream.str();
    }

void resetCounts() { counts = {}; }
Counts counts;

};

template <typename TypeToShadow>
class AlbaFundamentalOperationsCounter : public TypeToShadow {
public:
#define COUNTS AlbaFundamentalOperationsCounts<TypeToShadow>::getInstance().counts

// NOTE: COMMENT OUT operation if not needed
template <typename... Params>
    explicit AlbaFundamentalOperationsCounter(Params&&... params) : TypeToShadow(std::forward<Params>(params)...) {
        // enable_if for isConstructible is not used here, because it still cause compiler error when not used
++COUNTS.userConstructionCount;
    }

AlbaFundamentalOperationsCounter()
        : std::enable_if_t<typeHelper::isDefaultConstructible<TypeToShadow>(), TypeToShadow>() {
        ++COUNTS.defaultConstructionCount;
    }

~AlbaFundamentalOperationsCounter() {
        // enable_if for isConstructible is not used here, because this is just debug tool
++COUNTS.destructionCount;
    }

AlbaFundamentalOperationsCounter(AlbaFundamentalOperationsCounter const& parameter)
        : std::enable_if_t<typeHelper::isCopyConstructible<TypeToShadow>(), TypeToShadow>(
              static_cast<TypeToShadow const&>(parameter)) {
        ++COUNTS.copyConstructionCount;
    }

AlbaFundamentalOperationsCounter(AlbaFundamentalOperationsCounter&& parameter) noexcept
        : std::enable_if_t<typeHelper::isMoveConstructible<TypeToShadow>(), TypeToShadow>(
              static_cast<TypeToShadow&&>(parameter)) {
        ++COUNTS.moveConstructionCount;
    }

AlbaFundamentalOperationsCounter& operator=(AlbaFundamentalOperationsCounter const& parameter) {
        if (this != &parameter) {
            using EnabledTypeToShadow = std::enable_if_t<typeHelper::isCopyAssignable<TypeToShadow>(), TypeToShadow>;
            static_cast<EnabledTypeToShadow&>(*this) = static_cast<EnabledTypeToShadow const&>(parameter);
            ++COUNTS.copyAssignmentCount;
        }
        return *this;
    }

AlbaFundamentalOperationsCounter& operator=(AlbaFundamentalOperationsCounter&& parameter) noexcept {
        using EnabledTypeToShadow = std::enable_if_t<typeHelper::isMoveAssignable<TypeToShadow>(), TypeToShadow>;
        static_cast<EnabledTypeToShadow&>(*this) = static_cast<EnabledTypeToShadow&&>(parameter);
        ++COUNTS.moveAssignmentCount;
        return *this;
    }

#undef COUNTS

};

// Note: CRTP (curiously recurring template pattern) can also be an approach
// But it does not track user defined construction.
// Example:
//   template <typename T>
//   struct counter
//   {
//       static inline int objects_created = 0;
//       static inline int objects_alive = 0;
//
//       counter()
//       {
//           ++objects_created;
//           ++objects_alive;
//       }
//
//       counter(const counter&)
//       {
//           ++objects_created;
//           ++objects_alive;
//       }
//   protected:
//       ~counter() // objects should never be removed through pointers of this type
//       {
//           --objects_alive;
//       }
//   };
//
//   class X : counter<X>
//   {
//       // ...
//   };
//
//   class Y : counter<Y>
//   {
//       // ...
//   };
// Note: counter<x> and counter<y> have different instances so they have set of different values.

}  // namespace alba
