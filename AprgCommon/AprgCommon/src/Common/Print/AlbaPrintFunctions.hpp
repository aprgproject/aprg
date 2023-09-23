#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <optional>
#include <ostream>
#include <string>
#include <tuple>

namespace alba {

void printLogHeader(
    std::ostream& out, std::string_view const fileName, int const lineNumber, std::string_view const functionName);
void printCurrentDateTime(std::ostream& out);
void printStringAndShortenIfPossible(
    std::ostream& out, std::string_view const longStr, size_t const prefixLength, size_t const suffixLength);
// printParameter declaration
void printParameter(std::ostream& out, std::string const& parameter);
void printParameter(std::ostream& out, char const* const parameter);
template <typename ParameterType>
void printParameter(std::ostream& out, ParameterType const& parameter);
template <typename ParameterType>
void printParameter(std::ostream& out, std::optional<ParameterType> const& parameter);
template <typename... UnderlyingTypes>
void printParameter(std::ostream& out, std::pair<UnderlyingTypes...> const& parameter);
template <typename... UnderlyingTypes>
void printParameter(std::ostream& out, std::tuple<UnderlyingTypes...> const& parameter);

template <typename ValueType, size_t const SIZE, template <typename, size_t> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEnd<TemplateType<ValueType, SIZE>>(), void> printParameter(
    std::ostream& out, TemplateType<ValueType, SIZE> const& parameter);

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEndAndSize<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& out, TemplateType<UnderlyingTypes...> const& parameter);

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEndAndWithoutSize<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& out, TemplateType<UnderlyingTypes...> const& parameter);

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasContainerType<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& out, TemplateType<UnderlyingTypes...> const& parameter);

// printParameterWithName declaration
template <typename ParameterType>
void printParameterWithName(std::ostream& out, std::string_view const parameterName, ParameterType const& parameter);

template <typename ParameterPointerType>
void printParameterWithName(
    std::ostream& out, std::string_view const parameterName, ParameterPointerType* parameterPointer);

template <>
void printParameterWithName(std::ostream& out, std::string_view, char const* const parameter);

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithDereference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(
    std::ostream& out, std::string_view const parameterName, TemplateType<UnderlyingTypes...> const& parameter);

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithoutDereference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(
    std::ostream& out, std::string_view const parameterName, TemplateType<UnderlyingTypes...> const& parameter);

// Utilities
template <typename... ValueTypes>
void printTupleParameters(std::ostream& out, std::tuple<ValueTypes...> const& parameter) {
    std::apply  // C++17, applies a function by unpacking a tuple to its tupleParameters
        (
            [&out](ValueTypes const&... tupleParameters) {
                std::size_t tupleIndex{};
                auto printTupleParameter = [&out](auto&& tupleParameter, auto& tupleIndex) {
                    printParameter(out, tupleParameter);
                    out << (++tupleIndex != sizeof...(ValueTypes) ? ", " : "");
                };
                (printTupleParameter(tupleParameters, tupleIndex), ...);  // Folding expressions in C++17
            },
            parameter);
}

template <typename ContainerType>
void printParametersByForEachTraversal(std::ostream& out, ContainerType const& container) {
    for (auto const& parameter : container) {
        printParameter(out, parameter);
        out << ", ";
    }
}

template <typename Adapter>
typename Adapter::container_type const& getUnderlyingContainerForPrinting(Adapter const& adapter) {
    // copied from parameter to lessen dependencies
    struct AdapterParent : Adapter {
        static typename Adapter::container_type const& get(Adapter const& adapterAsParameter) {
            return adapterAsParameter.*&AdapterParent::c;
        }
    };
    return AdapterParent::get(adapter);
}

// printParameter
template <typename ParameterType>
void printParameter(std::ostream& out, ParameterType const& parameter) {
    out << parameter;
}

template <typename ParameterType>
void printParameter(std::ostream& out, std::optional<ParameterType> const& parameter) {
    if (parameter) {
        out << parameter.value();
    } else {
        out << "empty";
    }
}

template <typename... UnderlyingTypes>
void printParameter(std::ostream& out, std::pair<UnderlyingTypes...> const& parameter) {
    out << "(";
    printParameter(out, parameter.first);
    out << ", ";
    printParameter(out, parameter.second);
    out << ")";
}

template <typename... UnderlyingTypes>
void printParameter(std::ostream& out, std::tuple<UnderlyingTypes...> const& parameter) {
    out << "(";
    printTupleParameters<UnderlyingTypes...>(out, parameter);
    out << ")";
}

template <typename ValueType, size_t const SIZE, template <typename, size_t> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEnd<TemplateType<ValueType, SIZE>>(), void> printParameter(
    std::ostream& out, TemplateType<ValueType, SIZE> const& parameter) {
    out << "{Constant size: " << SIZE << " | ";
    printParametersByForEachTraversal(out, parameter);
    out << "}";
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEndAndSize<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& out, TemplateType<UnderlyingTypes...> const& parameter) {
    out << "{size: " << parameter.size() << " | ";
    printParametersByForEachTraversal(out, parameter);
    out << "}";
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEndAndWithoutSize<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& out, TemplateType<UnderlyingTypes...> const& parameter) {
    out << "{";
    printParametersByForEachTraversal(out, parameter);
    out << "}";
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasContainerType<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& out, TemplateType<UnderlyingTypes...> const& parameter) {
    out << "{adapter: ";
    printParameter(out, getUnderlyingContainerForPrinting(parameter));
    out << "}";
}

// printParameterWithName
template <typename ParameterType>
void printParameterWithName(std::ostream& out, std::string_view const parameterName, ParameterType const& parameter) {
    out << parameterName << " : [";
    printParameter(out, parameter);
    out << "]";
}

template <typename ParameterPointerType>
void printParameterWithName(
    std::ostream& out, std::string_view const parameterName, ParameterPointerType* parameterPointer) {
    if (parameterPointer == nullptr) {
        out << parameterName << " : [nullptr]";
    } else {
        out << "*" << parameterName << " : [";
        printParameter(out, *parameterPointer);
        out << "]";
    }
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithDereference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(
    std::ostream& out, std::string_view const parameterName, TemplateType<UnderlyingTypes...> const& parameter) {
    printParameterWithName(out, parameterName, parameter.get());
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithoutDereference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(
    std::ostream& out, std::string_view const parameterName, TemplateType<UnderlyingTypes...> const& parameter) {
    out << parameterName << " has use count: [" << parameter.use_count() << "]";
}

}  // namespace alba
