#pragma once

#include <Common/Print/AlbaPrintMacros.hpp>

namespace alba {

// INF(Information) print macros to use
#define ALBA_INF_HEADER(out) out << "[INF] ";
#define ALBA_INF_PRINT1(out, p1) ALBA_INF_HEADER(out) ALBA_PRINT1(out, p1)
#define ALBA_INF_PRINT2(out, p1, p2) ALBA_INF_HEADER(out) ALBA_PRINT2(out, p1, p2)
#define ALBA_INF_PRINT3(out, p1, p2, p3) ALBA_INF_HEADER(out) ALBA_PRINT3(out, p1, p2, p3)
#define ALBA_INF_PRINT4(out, p1, p2, p3, p4) ALBA_INF_HEADER(out) ALBA_PRINT4(out, p1, p2, p3, p4)
#define ALBA_INF_PRINT5(out, p1, p2, p3, p4, p5) ALBA_INF_HEADER(out) ALBA_PRINT5(out, p1, p2, p3, p4, p5)
#define ALBA_INF_PRINT6(out, p1, p2, p3, p4, p5, p6) ALBA_INF_HEADER(out) ALBA_PRINT6(out, p1, p2, p3, p4, p5, p6)

#define ALBA_INF_PRINT7(out, p1, p2, p3, p4, p5, p6, p7) \
    ALBA_INF_HEADER(out) ALBA_PRINT7(out, p1, p2, p3, p4, p5, p6, p7)

// WRN(Warning) print macros to use
#define ALBA_WRN_HEADER(out) out << "[WRN] ";
#define ALBA_WRN_PRINT1(out, p1) ALBA_WRN_HEADER(out) ALBA_PRINT1(out, p1)
#define ALBA_WRN_PRINT2(out, p1, p2) ALBA_WRN_HEADER(out) ALBA_PRINT2(out, p1, p2)
#define ALBA_WRN_PRINT3(out, p1, p2, p3) ALBA_WRN_HEADER(out) ALBA_PRINT3(out, p1, p2, p3)
#define ALBA_WRN_PRINT4(out, p1, p2, p3, p4) ALBA_WRN_HEADER(out) ALBA_PRINT4(out, p1, p2, p3, p4)
#define ALBA_WRN_PRINT5(out, p1, p2, p3, p4, p5) ALBA_WRN_HEADER(out) ALBA_PRINT5(out, p1, p2, p3, p4, p5)
#define ALBA_WRN_PRINT6(out, p1, p2, p3, p4, p5, p6) ALBA_WRN_HEADER(out) ALBA_PRINT6(out, p1, p2, p3, p4, p5, p6)

#define ALBA_WRN_PRINT7(out, p1, p2, p3, p4, p5, p6, p7) \
    ALBA_WRN_HEADER(out) ALBA_PRINT7(out, p1, p2, p3, p4, p5, p6, p7)

// ERR(Error) print macros to use
#define ALBA_ERR_HEADER(out) out << "[ERR] ";
#define ALBA_ERR_PRINT1(out, p1) ALBA_ERR_HEADER(out) ALBA_PRINT1(out, p1)
#define ALBA_ERR_PRINT2(out, p1, p2) ALBA_ERR_HEADER(out) ALBA_PRINT2(out, p1, p2)
#define ALBA_ERR_PRINT3(out, p1, p2, p3) ALBA_ERR_HEADER(out) ALBA_PRINT3(out, p1, p2, p3)
#define ALBA_ERR_PRINT4(out, p1, p2, p3, p4) ALBA_ERR_HEADER(out) ALBA_PRINT4(out, p1, p2, p3, p4)
#define ALBA_ERR_PRINT5(out, p1, p2, p3, p4, p5) ALBA_ERR_HEADER(out) ALBA_PRINT5(out, p1, p2, p3, p4, p5)
#define ALBA_ERR_PRINT6(out, p1, p2, p3, p4, p5, p6) ALBA_ERR_HEADER(out) ALBA_PRINT6(out, p1, p2, p3, p4, p5, p6)

#define ALBA_ERR_PRINT7(out, p1, p2, p3, p4, p5, p6, p7) \
    ALBA_ERR_HEADER(out) ALBA_PRINT7(out, p1, p2, p3, p4, p5, p6, p7)

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#define ALBA_INF_PRINT(out, ...) ALBA_INF_HEADER(out) ALBA_PRINT_ALL(out, __VA_ARGS__)
#define ALBA_WRN_PRINT(out, ...) ALBA_WRN_HEADER(out) ALBA_PRINT_ALL(out, __VA_ARGS__)
#define ALBA_ERR_PRINT(out, ...) ALBA_ERR_HEADER(out) ALBA_PRINT_ALL(out, __VA_ARGS__)
#endif

}  // namespace alba
