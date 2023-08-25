#pragma once

#include <ProcessFiles/SackReader/AlbaSackReaderParameter.hpp>

#include <set>
#include <string>
#include <vector>

namespace alba {

class AlbaSackReaderType {
public:
    typedef std::vector<AlbaSackReaderParameter> Parameters;
    typedef std::set<std::string> TypeNames;

    AlbaSackReaderType();
    [[nodiscard]] bool isUnion() const;
    [[nodiscard]] Parameters getParameters() const;
    [[nodiscard]] TypeNames getOtherTypes() const;
    void clear();
    void copyContents(AlbaSackReaderType const& type);
    void addParameter(AlbaSackReaderParameter const& parameter);
    void addOtherTypeName(std::string const& otherTypeName);
    void setAsUnion();
    void printAll() const;

private:
    bool m_isUnion{false};
    Parameters m_parameters;
    TypeNames m_otherTypes;
};

}  // namespace alba
