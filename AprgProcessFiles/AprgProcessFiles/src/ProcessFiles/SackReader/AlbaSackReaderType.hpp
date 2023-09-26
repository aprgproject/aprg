#pragma once

#include <ProcessFiles/SackReader/AlbaSackReaderParameter.hpp>

#include <set>
#include <string>
#include <vector>

namespace alba {

class AlbaSackReaderType {
public:
    using Parameters = std::vector<AlbaSackReaderParameter>;
    using TypeNames = std::set<std::string>;
    AlbaSackReaderType() = default;
    [[nodiscard]] Parameters getParameters() const;
    [[nodiscard]] TypeNames getOtherTypes() const;
    [[nodiscard]] bool isUnion() const;
    void printAll() const;
    void clear();
    void copyContents(AlbaSackReaderType const& type);
    void addParameter(AlbaSackReaderParameter const& parameter);
    void addOtherTypeName(std::string const& otherTypeName);
    void setAsUnion();

private:
    bool m_isUnion{false};
    Parameters m_parameters;
    TypeNames m_otherTypes;
};

}  // namespace alba
