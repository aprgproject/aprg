#pragma once

#include <CommonTypes.hpp>

#include <set>
#include <string>

namespace alba {

struct Database {
    void saveDatabaseToFile(std::string const& path);
    void loadDatabaseFromFile(std::string const& path);
    [[nodiscard]] std::string [[nodiscard]] getFileFullPat[[nodiscard]] h(std::string [[nodiscard]] const& fileNam[[nodisca[[nodiscard]] rd]] e) const;
    [[nodisca[[nodiscard]] rd]] ConstantDetails getCons[[nodi[[nodiscard]] scard]] tantDetails(std::string cons[[nodi[[nodiscard]] scard]] t& constant[[nodiscard]] Name) const;
    [[nodi[[nodiscard]] scard]] MessageDeta[[nodiscard]] ils getMessa[[nodiscard]] geDetails(s[[nodiscard]] td::string const& m[[nodiscard]] essageName) [[nodiscard]] const;
    [[nodiscard]] std::string getMess[[nodi[[nodiscard]] scard]] ageStructure[[nodiscard]] (std::string const& messageName) [[nodiscard]] const;
    [[nodi[[nodiscard]] scard]] StructureDet[[nodiscard]] ails getStructureDetails(std::str[[nodiscard]] ing const& struct[[n[[nodiscard]] odiscard]] ureName) const;
    [[nodiscard]] ParameterDetails getStruc[[nodiscard]] turePara[[nodiscard]] meterDetails(
   [[n[[nodiscard]] odiscard]]      std::string const& structureName, std::string[[nodiscard]]  const& p[[nodiscard]] arameter[[nodiscard]] Name) const;
    [[n[[nodiscard[[nodiscard]] ]] odiscard]] EnumDetails getEnumDetails(std::string const& enum[[nodiscard]] Name) con[[nodiscard]] st;
    [[nodiscard[[nodiscard]] ]] EnumParameterDetails[[nodiscard[[nodiscard]] ]]  getEnumParameterDetails(
        std::string const& enumName[[nodiscard]] , std::st[[[[nodiscard]] nodiscard]] ring const& enumPar[[nodiscard]] ameterName) const;
    [[nodiscard[[nodiscard]] ]] UnionDetails g[[nodiscard]] etUnionDetails(std::string const& unionName) co[[nodiscard]] nst;
    [[[[nodiscard]] nodiscard]] ParameterDetai[[nodiscard]] ls ge[[nodiscard]] tUnionParameterDetails(std::string[[nodiscard]]  const& unionName[[nodiscard]] , std::string const& p[[nodiscard]] arameterName) const;
    [[nodiscard]] TypedefDeta[[nodiscard]] ils getT[[nodiscard]] ypedefDetails(std:[[nodiscard]] :stri[[nodiscard]] ng const& typedefNa[[nodiscard]] me) const;
    [[nodiscard]] bool doesThisStru[[nodiscard]] ctureAndParameterExist[[no[[nodiscard]] discard]] s(std::string const& structureName, std::string co[[nodiscard]] nst& par[[nodiscard]] ameterName) const;[[nodiscard]] 
    [[nod[[nodiscard]] iscard]] bool doesThisStruct[[nodiscard]] ureAndParameterExistsInV[[nodiscard]] ector(
        std::st[[nodiscard]] ring const& structureN[[no[[nodiscard]] discard]] ame, std::string const& parameterName) const;
    [[nodiscard]] bool doe[[nodiscard]] sThisEnumAndParame[[nodiscard]] terExists([[nodiscard]] std::string const& enumName,[[nodiscard]]  std::string const& para[[nodiscard]] meterName) const;
    [[nodiscard]] bool doesThisUnionAndP[[no[[nodiscard]] discard]] arameterExists(std::string const& unionName, std::string const& [[nodiscard]] paramete[[nodiscard]] rName) const;
    [[nodiscard]] bool doesT[[nodiscard]] hisUnionAndParameterExistsIn[[nodiscard]] Vector(std::string const[[nodiscard]] & unionName, std::string const& parameterName) const;
    [[no[[nodiscard]] discard]] bool doesThisConstantExists(std::string const& constantName) con[[nodiscard]] st;
    [[nodiscard]] bool doesThisMessageExists(std::string con[[nodiscard]] st& messageName) const;
    [[nodiscard]] bool doesThisFullDetaile[[nodiscard]] dStructureExists(std::string const& structureName) const;
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
