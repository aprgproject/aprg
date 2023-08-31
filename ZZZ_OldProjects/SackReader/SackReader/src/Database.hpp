#pragma once

#include <CommonTypes.hpp>

#include <set>
#include <string>

namespace alba {

struct Database {
    void saveDatabaseToFile(std::string const& path) const;
    void loadDatabaseFromFile(std::string const& path);
    [[nodiscard]] std::string getFileFullPath(std::string const& fileName) const;
    [[nodiscard]] ConstantDetails getConstantDetails(std::string const& constantName) const;
    [[nodiscard]] MessageDetails getMessageDetails(std::string const& messageName) const;
    [[nodiscard]] std::string getMessageStructure(std::string const& messageName) const;
    [[nodiscard]] StructureDetails getStructureDetails(std::string const& structureName) const;
    [[nodiscard]] ParameterDetails getStructureParameterDetails(
        std::string const& structureName, std::string const& parameterName) const;
    [[nodiscard]] EnumDetails getEnumDetails(std::string const& enumName) const;
    [[nodiscard]] EnumParameterDetails getEnumParameterDetails(
        std::string const& enumName, std::string const& enumParameterName) const;
    [[nodiscard]] UnionDetails getUnionDetails(std::string const& unionName) const;
    [[nodiscard]] ParameterDetails getUnionParameterDetails(
        std::string const& unionName, std::string const& parameterName) const;
    [[nodiscard]] TypedefDetails getTypedefDetails(std::string const& typedefName) const;
    [[nodiscard]] bool doesThisStructureAndParameterExists(
        std::string const& structureName, std::string const& parameterName) const;
    [[nodiscard]] bool doesThisStructureAndParameterExistsInVector(
        std::string const& structureName, std::string const& parameterName) const;
    [[nodiscard]] bool doesThisEnumAndParameterExists(
        std::string const& enumName, std::string const& parameterName) const;
    [[nodiscard]] bool doesThisUnionAndParameterExists(
        std::string const& unionName, std::string const& parameterName) const;
    [[nodiscard]] bool doesThisUnionAndParameterExistsInVector(
        std::string const& unionName, std::string const& parameterName) const;
    [[nodiscard]] bool doesThisConstantExists(std::string const& constantName) const;
    [[nodiscard]] bool doesThisMessageExists(std::string const& messageName) const;
    [[nodiscard]] bool doesThisFullDetailedStructureExists(std::string const& structureName) const;
    [[nodiscard]] bool doesThisStructureExists(std::string const& structureName) const;
    [[nodiscard]] bool doesThisEnumExists(std::string const& enumName) const;
    [[nodiscard]] bool doesThisUnionExists(std::string const& unionName) const;
    [[nodiscard]] bool doesThisTypedefExists(std::string const& typedefName) const;
    FileToPathMap fileToPathMap;
    ConstantNameToConstantDetailsMap constantNameToConstantDetailsMap;
    MessageNameToMessageDetailsMap messageNameToMessageDetailsMap;
    StructureNameToStructureDetailsMap structureNameToStructureDetailsMap;
    UnionNameToUnionDetailsMap unionNameToUnionDetailsMap;
    EnumNameToEnumDetailsMap enumNameToEnumDetailsMap;
    TypedefNameToTypedefDetailsMap typedefNameToTypedefDetailsMap;
    std::set<std::string> messagesToGenerate;
};

}  // namespace alba
