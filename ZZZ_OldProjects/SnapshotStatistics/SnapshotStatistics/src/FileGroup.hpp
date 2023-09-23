#pragma once

#include <functional>
#include <string>

namespace alba {

class FileGroup {
public:
    using ConditionFunction = std::function<bool(std::string const&)>;
    FileGroup(std::string const& wildcardName, ConditionFunction const& condition);
    FileGroup(std::string&& wildcardName, ConditionFunction&& condition);
    [[nodiscard]] std::string getWildcardName() const;
    [[nodiscard]] bool isInFileGroup(std::string const& fileName) const;

private:
    std::string m_wildcardName;
    ConditionFunction m_condition;
};

}  // namespace alba
