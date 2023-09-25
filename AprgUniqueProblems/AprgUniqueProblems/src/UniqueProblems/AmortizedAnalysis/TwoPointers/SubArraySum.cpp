#include "SubArraySum.hpp"

using namespace std;

namespace alba {

SubArraySum::SubArraySum(Values const& valuesToCheck) : m_valuesToCheck(valuesToCheck) {}
SubArraySum::SubArraySum(Values&& valuesToCheck) : m_valuesToCheck(valuesToCheck) {}

SubArraySum::Values SubArraySum::getSubArrayWithSum(Value const targetSum) const {
    Values result;
    if (!m_valuesToCheck.empty()) {
        bool isFound(false);
        Index start = 0;
        Index end = 0;
        auto const size = static_cast<Index>(m_valuesToCheck.size());
        Value currentSum = m_valuesToCheck[0];
        while (start < size && end < size) {
            if (currentSum == targetSum) {
                isFound = true;
                break;
            }
            if (currentSum > targetSum) {
                if (start < end) {
                    currentSum -= m_valuesToCheck[start];
                    ++start;
                } else if (end + 1 < size) {
                    ++start;
                    ++end;
                    currentSum = m_valuesToCheck[end];
                } else {
                    break;
                }
            } else {
                if (end + 1 < size) {
                    ++end;
                    currentSum += m_valuesToCheck[end];
                } else {
                    break;
                }
            }
        }
        if (isFound) {
            // empty if not found
            result = Values(m_valuesToCheck.cbegin() + start, m_valuesToCheck.begin() + end + 1);
        }
    }
    return result;
}

}  // namespace alba
