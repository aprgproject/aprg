#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba {

class AlbaNumberIntervalEndpoint {
public:
    enum class Type { Open, Close };

    AlbaNumberIntervalEndpoint(Type const type, AlbaNumber const value);
    bool operator==(AlbaNumberIntervalEndpoint const& second) const;
    [[nodiscard]] AlbaNumber const& getValue() const;
    [[nodiscard]] Type getType() const;
    [[nodiscard]] std::string getTypeString() const;
    [[nodiscard]] bool isOpen() const;
    [[nodiscard]] bool isClose() const;
    void setType(Type const type);

private:
    friend std::ostream& operator<<(std::ostream& out, AlbaNumberIntervalEndpoint const& endpoint);
    Type m_type;
    AlbaNumber m_value;
};

}  // namespace alba
