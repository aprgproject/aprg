#pragma once

#include <Common/Macros/AlbaMacros.hpp>
#include <Common/Print/AlbaPrintMacros.hpp>

#include <iomanip>
#include <iostream>
#include <string_view>

namespace alba {

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#warning("The class AlbaDebug is used. Please remove after your done debugging.") // GCC extension
#elif defined(_MSC_VER)
#pragma message("The class AlbaDebug is used. Please remove after your done debugging.")  // MSVC extension
#endif
#if defined(ALBA_DBG_PRINT_EXTERNAL_OUTPUT_STREAM_FILE_PATH)
#include <ofstream>
inline std::ofstream debugStream(ALBA_DBG_PRINT_EXTERNAL_OUTPUT_STREAM_FILE_PATH);
#define ALBA_DBG_STREAM debugStream
#elif defined(ALBA_DBG_PRINT_EXTERNAL_OUTPUT_STREAM_OBJECT)
#define ALBA_DBG_STREAM ALBA_DBG_PRINT_EXTERNAL_OUTPUT_STREAM_OBJECT
#else
#define ALBA_DBG_STREAM std::cout
#endif
// DBG(Debug) print macros to use
#define ALBA_DBG_HEADER ALBA_DBG_STREAM << "[DBG] ";
#define ALBA_DBG_PRINT1(p1) ALBA_DBG_HEADER ALBA_PRINT1(ALBA_DBG_STREAM, p1)
#define ALBA_DBG_PRINT2(p1, p2) ALBA_DBG_HEADER ALBA_PRINT2(ALBA_DBG_STREAM, p1, p2)
#define ALBA_DBG_PRINT3(p1, p2, p3) ALBA_DBG_HEADER ALBA_PRINT3(ALBA_DBG_STREAM, p1, p2, p3)
#define ALBA_DBG_PRINT4(p1, p2, p3, p4) ALBA_DBG_HEADER ALBA_PRINT4(ALBA_DBG_STREAM, p1, p2, p3, p4)
#define ALBA_DBG_PRINT5(p1, p2, p3, p4, p5) ALBA_DBG_HEADER ALBA_PRINT5(ALBA_DBG_STREAM, p1, p2, p3, p4, p5)
#define ALBA_DBG_PRINT6(p1, p2, p3, p4, p5, p6) ALBA_DBG_HEADER ALBA_PRINT6(ALBA_DBG_STREAM, p1, p2, p3, p4, p5, p6)

#define ALBA_DBG_PRINT7(out, p1, p2, p3, p4, p5, p6, p7) \
    ALBA_DBG_HEADER ALBA_PRINT7(ALBA_DBG_STREAM, p1, p2, p3, p4, p5, p6, p7)

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#define ALBA_DBG_PRINT(...) ALBA_DBG_HEADER ALBA_PRINT_ALL(ALBA_DBG_STREAM, __VA_ARGS__)
#endif
#define ALBA_DBG_PRINT_PRECISION(parameter) ALBA_DBG_STREAM.precision(parameter)
#define ALBA_DBG_PRINT_MANIPULATE_OUTPUT(ioParameter) ALBA_DBG_STREAM << ioParameter
// Macros for debug scope
#define ALBA_DBG_SCOPE_START {
#define ALBA_DBG_SCOPE_END }

// Macros for output operator
// Note: Dont include "friend" keyword in macro just include in the class.
#define ALBA_DBG_CLASS_OUTPUT_OPERATOR_DECLARATION(ParameterSignature) \
    std::ostream& operator<<(std::ostream& out, ParameterSignature);

// NOLINTBEGIN(bugprone-macro-parentheses)
#define ALBA_DBG_CLASS_OUTPUT_OPERATOR_DEFINITION(ParameterSignature, OutputOperation) \
    std::ostream& operator<<(std::ostream& out, ParameterSignature) {                  \
        out << OutputOperation;                                                        \
        return out;                                                                    \
    }

// NOLINTEND(bugprone-macro-parentheses)
// #define ALBA_DBG_COMMENTED_LINE #warning("Uncomment this line after your done debugging.");

}  // namespace alba
