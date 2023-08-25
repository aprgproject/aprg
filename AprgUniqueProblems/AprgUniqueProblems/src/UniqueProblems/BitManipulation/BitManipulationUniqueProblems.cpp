#include "BitManipulationUniqueProblems.hpp"

using namespace std;

namespace alba::BitManipulation {

uint64_t changeKthBitToOne(uint64_t const value, uint64_t const k) { return value | (1 << k); }

uint64_t changeKthBitToZero(uint64_t const value, uint64_t const k) { return value & ~(1 << k); }

uint64_t invertKthBit(uint64_t const value, uint64_t const k) { return value ^ (1 << k); }

uint64_t changeLastOneToZero(uint64_t const value) { return value & (value - 1); }

uint64_t changeAllOnesToZeroExceptForLast(uint64_t const value) { return value & (-value); }

uint64_t invertAllBitsAfterTheLastOne(uint64_t const value) { return value | (value - 1); }

}  // namespace alba::BitManipulation
