#pragma once

#include <User/AlbaDisplayTable.hpp>

#include <map>
#include <set>
#include <string>
#include <vector>

namespace alba
{

struct ConstantDetails
{
    std::string name;
    std::string value;
    std::string description;
    std::string descriptionFromUser;
    void clear()
    {
        name.clear();
        value.clear();
        description.clear();
        descriptionFromUser.clear();
    }
    friend std::ostream & operator<<(std::ostream & out, ConstantDetails const& constantDetails);
    friend std::istream & operator>>(std::istream & in, ConstantDetails& constantDetails);
};

struct EnumParameterDetails
{
    std::string name;
    std::string value;
    std::string description;
    std::string descriptionFromUser;
    void clear()
    {
        name.clear();
        value.clear();
        description.clear();
        descriptionFromUser.clear();
    }
    friend std::ostream & operator<<(std::ostream & out, EnumParameterDetails const& enumParameterDetails);
    friend std::istream & operator>>(std::istream & in, EnumParameterDetails& enumParameterDetails);
};

struct EnumDetails
{
    using ParameterMap = std::map<std::string, EnumParameterDetails>;
    using ParameterPair = std::pair<std::string, EnumParameterDetails>;
    std::string name;
    ParameterMap parameters;
    bool isUsedInIfs;
    void clear()
    {
        name.clear();
        parameters.clear();
        isUsedInIfs=false;
    }
    friend std::ostream & operator<<(std::ostream & out, EnumDetails const& enumDetails);
    friend std::istream & operator>>(std::istream & in, EnumDetails& enumDetails);
};

struct ParameterDetails
{
    std::string type;
    std::string name;
    std::string description;
    std::string descriptionFromUser;
    bool isAnArray;
    std::string arraySize;
    void clear()
    {
        type.clear();
        name.clear();
        description.clear();
        descriptionFromUser.clear();
        isAnArray=false;
        arraySize.clear();
    }
    friend std::ostream & operator<<(std::ostream & out, ParameterDetails const& parameterDetails);
    friend std::istream & operator>>(std::istream & in, ParameterDetails& parameterDetails);
};

struct StructureDetails
{
    using ParameterMap = std::map<std::string, ParameterDetails>;
    using ParameterPair = std::pair<std::string, ParameterDetails>;
    std::string name;
    ParameterMap parameters;
    std::vector<std::string> parametersWithCorrectOrder; // unordered_map
    bool isMessage;
    bool isUsedInIfs;
    void clear()
    {
        name.clear();
        parameters.clear();
        isMessage=false;
        isUsedInIfs=false;
    }
};



using FileToPathMap = std::map<std::string, std::string>;
using FileToPathPair = std::pair<std::string, std::string>;
using ConstantNameToConstantDetailsMap = std::map<std::string, ConstantDetails>;
using ConstantNameToConstantDetailsPair = std::pair<std::string, ConstantDetails>;
using MessageNameToStructureNameMap = std::map<std::string, std::string>;
using MessageNameToStructureNamePair = std::pair<std::string, std::string>;
using StructureNameToStructureDetailsMap = std::map<std::string, StructureDetails>;
using StructureNameToStructureDetailsPair = std::pair<std::string, StructureDetails>;
using EnumNameToEnumDetailsMap = std::map<std::string, EnumDetails>;
using EnumNameToEnumDetailsPair = std::pair<std::string, EnumDetails>;



class SackReader
{
public:
    SackReader(std::string const& path);
    void checkAllFiles();
    void saveDatabaseToFile(std::string const& path);
    void loadDatabaseFromFile(std::string const& path);
    void checkOamTcomTupcMessages();
    void readDefinitionFileFromStructureRecursively(std::string const& structureFileName);
    void readFile(std::string const& fileName);
    void saveSubsection(std::string const& subsectionName, std::ofstream & lyxOutputFileStream) const;
    void saveMessageDefinitions(std::ofstream & lyxOutputFileStream);
    void saveStructureDefinitions(std::ofstream & lyxOutputFileStream);
    void saveEnumDefinitions(std::ofstream & lyxOutputFileStream);
    void saveMessageDefinitionSubsubsection(std::string const& messageName, std::ofstream & messageTableStream);
    void saveStructureDefinitionSubsubsection(std::string const& structureName, std::ofstream & structureDefinitionsStream);
    void saveEnumDefinitionSubsubsection(std::string const& enumName, std::ofstream & enumDefinitionsStream);
    void saveMessageTable(std::string const& messageName, std::ofstream & messageTableStream);
    void saveStructureTable(std::string const& structureName, std::ofstream & structureTableStream);
    void saveEnumTable(std::string const& enumName, std::ofstream & enumTableStream);
    void saveDisplayTable(DisplayTable const& messageTable, std::ofstream & messageTableStream) const;
    void generateStructureForDisplayTablesIfNeeded(std::string const& structureName, DisplayTable & messageTable, std::string const& indentionInType, bool const areInnerStructuresGenerated);
    void generateEnumForDisplayTablesIfNeeded(std::string const& enumName, DisplayTable & displayTable);
    void generateLyxDocument(std::string const& templatePath, std::string const& finalDocumentPath);
    void loadMessagesToGenerate(std::string const& path);
    void loadDescriptionToAdd(std::string const& path);
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
    void performHacks();

private:
    std::string m_path;
    FileToPathMap m_fileToPathMap;
    ConstantNameToConstantDetailsMap m_constantNameToConstantDetailsMap;
    MessageNameToStructureNameMap m_messageNameToStructureNameMap;
    StructureNameToStructureDetailsMap m_structureNameToStructureDetailsMap;
    EnumNameToEnumDetailsMap m_enumNameToEnumDetailsMap;
    std::set<std::string> m_messagesToGenerate;
};

}
