#pragma once

#include <Common/Math/Number/Interval/AlbaNumberIntervalEndpoint.hpp>

namespace alba {

class AlbaNumberInterval {
public:
    AlbaNumberInterval(
        AlbaNumberIntervalEndpoint const& firstEndpoint, AlbaNumberIntervalEndpoint const& secondEndpoint);

    // rule of zero
    bool operator==(AlbaNumberInterval const& second) const;
    [[nodiscard]] AlbaNumberIntervalEndpoint const& getLowerEndpoint() const;
    [[nodiscard]] AlbaNumberIntervalEndpoint const& getHigherEndpoint() const;
    [[nodiscard]] bool isValueInsideTheInterval(AlbaNumber const& value) const;
    [[nodiscard]] bool isValueInsideTheIntervalExceptAtTheEndpoints(AlbaNumber const& value) const;
    [[nodiscard]] bool isEndpointInsideTheInterval(AlbaNumberIntervalEndpoint const& endpoint) const;
    [[nodiscard]] bool isIntervalInsideTheInterval(AlbaNumberInterval const& interval) const;
    void setNewEndpoint(AlbaNumberIntervalEndpoint const& endpoint);
    friend std::ostream& operator<<(std::ostream& out, AlbaNumberInterval const& interval);

private:
    AlbaNumberIntervalEndpoint m_lowerEndpoint;
    AlbaNumberIntervalEndpoint m_higherEndpoint;
};

}  // namespace alba
