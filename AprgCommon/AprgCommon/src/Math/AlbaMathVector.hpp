#pragma once

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <array>
#include <sstream>
#include <string>

using namespace alba::mathHelper;

namespace alba
{

template <typename DataType, unsigned int SIZE>
class AlbaMathVector
{
public:
    using MathVector=AlbaMathVector<DataType, SIZE>;
    using Values=std::array<double, SIZE>;

    AlbaMathVector()
    {
        std::fill(m_values.begin(), m_values.end(), 0);
    }

    AlbaMathVector(Values const& values)
    {
        std::copy(values.begin(), values.end(), m_values.begin());
    }

    AlbaMathVector(std::initializer_list<DataType> const& values)
    {
        static_assert(SIZE>0, "The SIZE of AlbaMathVector should be positive.");
        unsigned int limit = std::min(SIZE, static_cast<unsigned int>(values.size()));
        std::copy(values.begin(), values.begin()+limit, m_values.begin());
        std::fill(m_values.begin()+limit, m_values.end(), 0);
    }

    bool operator==(MathVector const& second) const
    {
        return std::equal(m_values.cbegin(), m_values.cend(), second.m_values.cbegin());
    }

    bool operator!=(MathVector const& second) const
    {
        MathVector const& first(*this);
        return !(first==second);
    }

    bool operator<(MathVector const& second) const // this is added so it can be used in map
    {
        auto mismatchPair = std::mismatch(m_values.cbegin(), m_values.cend(), second.m_values.cbegin());
        bool result(false);
        if(mismatchPair.first != m_values.cend())
        {
            result = *(mismatchPair.first) < *(mismatchPair.second);
        }
        return result;
    }

    MathVector operator+(MathVector const& second) const
    {
        Values resultValues;
        Values const& firstValues(m_values);
        Values const& secondValues(second.m_values);
        std::transform(firstValues.begin(), firstValues.end(), secondValues.begin(), resultValues.begin(), std::plus<DataType>());
        return MathVector(resultValues);
    }

    MathVector operator-(MathVector const& second) const
    {
        Values resultValues;
        Values const& firstValues(m_values);
        Values const& secondValues(second.m_values);
        std::transform(firstValues.begin(), firstValues.end(), secondValues.begin(), resultValues.begin(), std::minus<DataType>());
        return MathVector(resultValues);
    }

    MathVector operator+() const
    {
        return *this;
    }

    MathVector operator-() const
    {
        std::transform(m_values.begin(), m_values.end(), m_values.begin(), std::negate<DataType>());
    }

    MathVector& operator+=(MathVector const& second)
    {
        Values const& secondValues(second.m_values);
        std::transform(m_values.begin(), m_values.end(), secondValues.begin(), m_values.begin(), std::plus<DataType>());
        return *this;
    }

    MathVector& operator-=(MathVector const& second)
    {
        Values const& secondValues(second.m_values);
        std::transform(m_values.begin(), m_values.end(), secondValues.begin(), m_values.begin(), std::minus<DataType>());
        return *this;
    }

    unsigned int getSize() const
    {
        return SIZE;
    }

    DataType getValueAt(unsigned int const index) const
    {
        assert(index<SIZE);
        return m_values.at(index);
    }

    Values const& getValues() const
    {
        return m_values;
    }

    std::string getDisplayableString() const
    {
        std::stringstream ss;
        bool isFirst(true);
        ss << "{";
        for(AlbaNumber const& value : m_values)
        {
            if(isFirst)
            {
                isFirst = false;
            }
            else
            {
                ss << ", ";
            }
            ss << value;
        }
        ss << "}";
        return ss.str();
    }

private:
    Values m_values;
};

template <typename DataType, unsigned int SIZE>
std::ostream & operator<<(std::ostream & out, AlbaMathVector<DataType, SIZE> const& mathVector)
{
    out << mathVector.getDisplayableString();
    return out;
}

}
