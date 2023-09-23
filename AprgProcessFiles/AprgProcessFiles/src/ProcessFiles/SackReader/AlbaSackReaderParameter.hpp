#pragma once

#include <string>

namespace alba {

class AlbaSackReaderParameter {
public:
    AlbaSackReaderParameter(std::string const& typeName, std::string const& parameterName);
    AlbaSackReaderParameter(std::string&& typeName, std::string&& parameterName);
    [[nodiscard]] std::string getTypeName() const;
    [[nodiscard]] std::string getParameterName() const;

private:
    std::string m_typeName;
    std::string m_parameterName;
};

}  // namespace alba
