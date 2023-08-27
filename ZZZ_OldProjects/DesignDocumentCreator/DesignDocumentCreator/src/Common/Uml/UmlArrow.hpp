#pragma once

#include <string>

namespace DesignDocumentCreator::UmlArrow {
std::string getRedArrow();
std::string getBlueArrow();
std::string getGreenArrow();
std::string getDarkerGreenArrow();
std::string getBlackArrow();
std::string getLostMessageArrow();
std::string getArrowBaseFromMessageName(std::string const& messageName);
}  // namespace DesignDocumentCreator::UmlArrow
