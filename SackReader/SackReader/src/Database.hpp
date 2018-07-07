#pragma once

#include <CommonTypes.hpp>

#include <set>
#include <string>

namespace alba
{

struct Database
{
    void saveDatabaseToFile(std::string const& path);
    void loadDatabaseFromFile(std::string const& path);
    std::string getFileFullPath(std::string const& fileName) const;
    ConstantDetails getConstantDetails(std::string const& constantName) const;
    std::string getMessageStructure(std::string const& messageName) const;
    StructureDetails getStructureDetails(std::string const& structureName) const;
    ParameterDetails getParameterDetails(std::string const& structureName, std::string const& parameterName) const;
    EnumDetails getEnumDetails(std::string const& enumName) const;
    EnumParameterDetails getEnumParameterDetails(std::string const& enumName, std::string const& enumParameterName) const;
    bool doesThisStructureAndParameterExists(std::string const& structureName, std::string const& parameterName) const;
    bool doesThisStructureAndParameterExistsInVector(std::string const& structureName, std::string const& parameterName) const;
    bool doesThisEnumAndParameterExists(std::string const& enumName, std::string const& parameterName) const;
    bool doesThisStructureExists(std::string const& structureName) const;
    bool doesThisEnumExists(std::string const& structureName) const;
    FileToPathMap fileToPathMap;
    ConstantNameToConstantDetailsMap constantNameToConstantDetailsMap;
    MessageNameToStructureNameMap messageNameToStructureNameMap;
    StructureNameToStructureDetailsMap structureNameToStructureDetailsMap;
    EnumNameToEnumDetailsMap enumNameToEnumDetailsMap;
    std::set<std::string> messagesToGenerate;
};

} // namespace alba
