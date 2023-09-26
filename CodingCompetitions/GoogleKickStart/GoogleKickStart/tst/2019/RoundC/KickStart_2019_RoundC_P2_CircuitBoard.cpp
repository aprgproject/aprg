// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// #define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundC_P2_CircuitBoard.hpp"

#include <Fake/FakeNames.hpp>
#endif
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#include <cmath>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION

using namespace alba;

#endif

namespace KickStart_2019_RoundC_P2_CircuitBoard {

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

// my solution it works
template <typename Values>
class RangeQueryWithSelector {
public:
    // Example for "range query with selector" is minimum queries
    // Minimum queries are more difficult to process than sum queries.
    // Still, there is a quite simple O(nlogn) time preprocessing method after which we can answer any minimum query in
    // O(1) time.
    // Note that since minimum and maximum queries can be processed similarly, we can focus on minimum queries.
    using Index = int;
    using Value = typename Values::value_type;
    using ValueMatrix = vector<Value>;
    using SelectorFunction = std::function<Value(Value const&, Value const&)>;

    RangeQueryWithSelector(Values const& valuesToCheck, SelectorFunction const& selector)
        : m_selectedValueMatrix(), m_selector(selector) {
        initialize(valuesToCheck);
    }

    RangeQueryWithSelector(Values const& valuesToCheck, SelectorFunction&& selector)
        : m_selectedValueMatrix(), m_selector(selector) {
        initialize(valuesToCheck);
    }

    [[nodiscard]] Value getSelectedValueOnInterval(Index const start, Index const end) const {
        // This is on constant time
        Value result{};
        if (start < m_columns && end < m_columns) {
            // this condition is correct
            if (start < end) {
                Index exponentOfDelta = getCeilOfLogarithmWithBase2Of(end + 1 - start) - 1;
                Index delta = get2ToThePowerOf(exponentOfDelta);  // numberOfRowsalf of the distance that would fit
                result = m_selector(
                    m_selectedValueMatrix[getMatrixIndex(start, exponentOfDelta)],
                    m_selectedValueMatrix[getMatrixIndex(end + 1 - delta, exponentOfDelta)]);
            } else if (start == end) {
                result = m_selectedValueMatrix[getMatrixIndex(start, 0)];
            }
        }
        return result;
    }

private:
    [[nodiscard]] Index getMatrixIndex(Index const x, Index const y) const { return y * m_columns + x; }
    [[nodiscard]] Index get2ToThePowerOf(Index const exponent) const { return static_cast<Index>(1) << exponent; }

    [[nodiscard]] Index getCeilOfLogarithmWithBase2Of(Index const index) const {
        /* constexpr Index numberOfBits = sizeof(Index) * 8;
        Index result = numberOfBits - __builtin_clz(index);
        result = (result == 0) ? 0 : isPowerOfTwo(index) ? result - 1 : result;
        return result;*/
        return 0;
    }

    [[nodiscard]] bool isPowerOfTwo(Index const index) const { return (index & (index - 1)) == 0; }

    void initialize(Values const& valuesToCheck) {
        if (!valuesToCheck.empty()) {
            Index lastExponentOf2(getCeilOfLogarithmWithBase2Of(valuesToCheck.size()));
            m_columns = valuesToCheck.size();
            m_rows = lastExponentOf2 + 1;
            m_selectedValueMatrix =
                ValueMatrix(m_columns * m_rows);  // column is index, row is exponent of size with base 2
            for (Index index = 0; index < static_cast<int>(valuesToCheck.size()); ++index) {
                // put values in first column
                m_selectedValueMatrix[getMatrixIndex(index, 0)] = valuesToCheck[index];
            }
            for (Index exponentOf2 = 0; exponentOf2 < lastExponentOf2; ++exponentOf2) {
                // put remaining values with "powers of 2 sized" ranges
                Index offset = get2ToThePowerOf(exponentOf2);
                Index limit = valuesToCheck.size() - offset;
                for (Index index = 0; index < limit; ++index) {
                    Value selectedValue(m_selector(
                        m_selectedValueMatrix[getMatrixIndex(index, exponentOf2)],
                        m_selectedValueMatrix[getMatrixIndex(index + offset, exponentOf2)]));
                    m_selectedValueMatrix[getMatrixIndex(index, exponentOf2 + 1)] = selectedValue;
                }
            }
        }
    }

    // Index getCeilOfLogarithmWithBase2Of(Index const index) const
    //{
    //    return static_cast<Index>(ceil(log(index)/log(2)));
    //}
    ValueMatrix m_selectedValueMatrix;  // index by exponent matrix
    SelectorFunction m_selector;
    Index m_columns{0};
    Index m_rows{0};
};

int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

int numberOfRows, numberOfColumns;

void runTestCase(int const testCaseNumber) {
    int maxAllowableThickness = 0;
    my_cin >> numberOfRows >> numberOfColumns >> maxAllowableThickness;
    vector<int> thicknessPerCell(numberOfRows * numberOfColumns);

    for (int i = 0; i < numberOfColumns * numberOfRows; ++i) {
        my_cin >> thicknessPerCell[i];
    }
    vector<int> subRowThicknessMatrix(numberOfRows * numberOfColumns);
    for (int y = 0; y < numberOfRows; ++y) {
        vector<int> rowThickness(
            thicknessPerCell.cbegin() + getIndex(0, y), thicknessPerCell.cbegin() + getIndex(0, y + 1));
        RangeQueryWithSelector minimumSelector(rowThickness, minimumSelectorFunction);
        RangeQueryWithSelector maximumSelector(rowThickness, maximumSelectorFunction);
        for (int left = 0; left < numberOfColumns; ++left) {
            int right = numberOfColumns - 1;
            for (; right > left; --right) {
                int possibleSubRowThickness = maximumSelector.getSelectedValueOnInterval(left, right) -
                                              minimumSelector.getSelectedValueOnInterval(left, right);
                if (possibleSubRowThickness <= maxAllowableThickness) {
                    break;
                }
            }
            subRowThicknessMatrix[getIndex(left, y)] = right - left + 1;
        }
    }

    int maxThickness = 0;
    for (int x = 0; x < numberOfColumns; ++x) {
        for (int top = 0; top < numberOfRows; ++top) {
            int commonRowThickness = subRowThicknessMatrix[getIndex(x, top)];
            int maxSubMatrixThickness = commonRowThickness;
            int rowLength = 2;
            for (int bottom = top + 1; bottom < numberOfRows; ++bottom) {
                commonRowThickness = min(commonRowThickness, subRowThicknessMatrix[getIndex(x, bottom)]);
                maxSubMatrixThickness = max(maxSubMatrixThickness, commonRowThickness * rowLength++);
            }
            maxThickness = max(maxThickness, maxSubMatrixThickness);
        }
    }

    my_cout << "Case #" << testCaseNumber << ": " << maxThickness << '\n';
}

/*
// top scorer solution
int numberOfRows, numberOfColumns;
constexpr int MAX_LENGTH = 309;

int getIndex(int const x, int const y)
{
    return y*numberOfColumns + x;
}

int getIndexFromMaxLength(int const x, int const y, int const z)
{
    return z*MAX_LENGTH*MAX_LENGTH + y*MAX_LENGTH + x;
}

void runTestCase(int const)
{
    int maxAllowableThickness;
    my_cin >> numberOfRows >> numberOfColumns >> maxAllowableThickness;
    vector<int> thicknessPerCell(numberOfRows*numberOfColumns);

    for(int i=0; i<numberOfColumns*numberOfRows; i++)
    {
        my_cin >> thicknessPerCell[i];
    }

    vector<int> ok(MAX_LENGTH*MAX_LENGTH*MAX_LENGTH, false);
    for (int i = 0; i < numberOfRows; ++i) {
        for (int j = 0; j < numberOfColumns; ++j) {
            int cl = numeric_limits<int>::max(), cr = numeric_limits<int>::min();
            for (int k = j; k < numberOfColumns; ++k) {
                cl = min(cl, thicknessPerCell[getIndex(k, i]));
                cr = max(cr, thicknessPerCell[getIndex(k, i]));
                if (cr - cl <= maxAllowableThickness) {
                    ok[getIndexFromMaxLength(i,j,k)] = true;
                }
                else {
                    ok[getIndexFromMaxLength(i,j,k)] = false;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < numberOfColumns; ++i) {
        for (int j = i; j < numberOfColumns; ++j) {
            int count = 0;
            for (int k = 0; k < numberOfRows; ++k) {
                if (ok[getIndexFromMaxLength(k,i,j)]) ++count;
                else count = 0;
                ans = max(ans, count * (j - i + 1));
            }
        }
    }

    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';
}*/
void runAllTestCases() {
    int numberOfTestCases = 0;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber) {
        runTestCase(testCaseNumber);
    }
}

RangeQueryWithSelector<vector<int>>::SelectorFunction minimumSelectorFunction = [](int const value1, int const value2) {
    return min(value1, value2);
};

RangeQueryWithSelector<vector<int>>::SelectorFunction maximumSelectorFunction = [](int const value1, int const value2) {
    return max(value1, value2);
};

int getIndex(int const x, int const y) { return y * numberOfColumns + x; }
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~

}  // namespace KickStart_2019_RoundC_P2_CircuitBoard

#undef FOR_SUBMISSION

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
