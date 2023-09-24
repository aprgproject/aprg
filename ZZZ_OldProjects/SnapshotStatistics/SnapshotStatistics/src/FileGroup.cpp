#include "FileGroup.hpp"

using namespace std;

namespace alba {

FileGroup::FileGroup(string const& wildcardName, ConditionFunction const& condition)
    : m_wildcardName(wildcardName), m_condition(condition) {}

FileGroup::FileGroup(string&& wildcardName, ConditionFunction&& condition)
    : m_wildcardName(wildcardName), m_condition(condition) {}

string FileGroup::getWildcardName() const { return m_wildcardName; }
bool FileGroup::isInFileGroup(string const& fileName) const { return m_condition(fileName); }

}  // namespace alba
