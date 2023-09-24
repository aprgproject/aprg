#pragma once

#include <Common/Macros/AlbaMacros.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>

namespace alba {

// Internal macros
// This is a revised approach in printing because of MSVC limitation on macros.
#define Z_ALBA_PRINT_START(out)                                                    \
    alba::printLogHeader(                                                          \
        out, static_cast<const char*>(ALBA_MACROS_GET_FILE), ALBA_MACROS_GET_LINE, \
        static_cast<const char*>(ALBA_MACROS_GET_FUNCTION));

#define Z_ALBA_PRINT_END(out) out << std::endl

#define Z_ALBA_PRINT_PARAMETER_ONLY(out, parameter) \
    alba::printParameterWithName(out, static_cast<const char*>(ALBA_MACROS_GET_STRING_LITERAL(parameter)), parameter);

#define Z_ALBA_PRINT_SEPARATOR(out) out << " ";
#define Z_ALBA_PRINT_PARAMETER(out, parameter) Z_ALBA_PRINT_PARAMETER_ONLY(out, parameter) Z_ALBA_PRINT_SEPARATOR(out)

#define Z_ALBA_PRINT_7(out, p1, p2, p3, p4, p5, p6, p7) \
    Z_ALBA_PRINT_PARAMETER(out, p1) Z_ALBA_PRINT_6(out, p2, p3, p4, p5, p6, p7)

#define Z_ALBA_PRINT_6(out, p1, p2, p3, p4, p5, p6) \
    Z_ALBA_PRINT_PARAMETER(out, p1) Z_ALBA_PRINT_5(out, p2, p3, p4, p5, p6)

#define Z_ALBA_PRINT_5(out, p1, p2, p3, p4, p5) Z_ALBA_PRINT_PARAMETER(out, p1) Z_ALBA_PRINT_4(out, p2, p3, p4, p5)
#define Z_ALBA_PRINT_4(out, p1, p2, p3, p4) Z_ALBA_PRINT_PARAMETER(out, p1) Z_ALBA_PRINT_3(out, p2, p3, p4)
#define Z_ALBA_PRINT_3(out, p1, p2, p3) Z_ALBA_PRINT_PARAMETER(out, p1) Z_ALBA_PRINT_2(out, p2, p3)
#define Z_ALBA_PRINT_2(out, p1, p2) Z_ALBA_PRINT_PARAMETER(out, p1) Z_ALBA_PRINT_PARAMETER(out, p2)
// Print macros to use
#define ALBA_PRINT1(out, p1) Z_ALBA_PRINT_START(out) Z_ALBA_PRINT_PARAMETER(out, p1) Z_ALBA_PRINT_END(out)
#define ALBA_PRINT2(out, p1, p2) Z_ALBA_PRINT_START(out) Z_ALBA_PRINT_2(out, p1, p2) Z_ALBA_PRINT_END(out)
#define ALBA_PRINT3(out, p1, p2, p3) Z_ALBA_PRINT_START(out) Z_ALBA_PRINT_3(out, p1, p2, p3) Z_ALBA_PRINT_END(out)

#define ALBA_PRINT4(out, p1, p2, p3, p4) \
    Z_ALBA_PRINT_START(out) Z_ALBA_PRINT_4(out, p1, p2, p3, p4) Z_ALBA_PRINT_END(out)

#define ALBA_PRINT5(out, p1, p2, p3, p4, p5) \
    Z_ALBA_PRINT_START(out) Z_ALBA_PRINT_5(out, p1, p2, p3, p4, p5) Z_ALBA_PRINT_END(out)

#define ALBA_PRINT6(out, p1, p2, p3, p4, p5, p6) \
    Z_ALBA_PRINT_START(out) Z_ALBA_PRINT_6(out, p1, p2, p3, p4, p5, p6) Z_ALBA_PRINT_END(out)

#define ALBA_PRINT7(out, p1, p2, p3, p4, p5, p6, p7) \
    Z_ALBA_PRINT_START(out) Z_ALBA_PRINT_7(out, p1, p2, p3, p4, p5, p6, p7) Z_ALBA_PRINT_END(out)

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)

#define ALBA_PRINT_ALL(out, ...) \
    ALBA_MACROS_CONCATENATE(ALBA_PRINT, ALBA_MACROS_COUNT_ARGUMENTS(__VA_ARGS__))(out, __VA_ARGS__)

#endif

}  // namespace alba
