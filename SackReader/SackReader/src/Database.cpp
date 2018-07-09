#include "Database.hpp"

#include <File/AlbaFileParameterReader.hpp>
#include <File/AlbaFileParameterWriter.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

void Database::saveDatabaseToFile(string const& path)
{
    ofstream fileStream(path);
    AlbaFileParameterWriter writer(fileStream);
    writer.writeData(fileToPathMap);
    writer.writeData(constantNameToConstantDetailsMap);
    writer.writeData(messageNameToMessageDetailsMap);
    writer.writeData(structureNameToStructureDetailsMap);
    writer.writeData(unionNameToUnionDetailsMap);
    writer.writeData(enumNameToEnumDetailsMap);}

void Database::loadDatabaseFromFile(string const& path)
{
    ifstream fileStream(path);
    AlbaFileParameterReader reader(fileStream);
    reader.readData(fileToPathMap);
    reader.readData(constantNameToConstantDetailsMap);
    reader.readData(messageNameToMessageDetailsMap);
    reader.readData(structureNameToStructureDetailsMap);
    reader.readData(unionNameToUnionDetailsMap);
    reader.readData(enumNameToEnumDetailsMap);}

string Database::getFileFullPath(string const& fileName) const
{
    string result;
    if(fileToPathMap.find(fileName)!=fileToPathMap.cend())
    {
        result = fileToPathMap.at(fileName);
    }
    return result;
}

ConstantDetails Database::getConstantDetails(string const& constantName) const
{
    ConstantDetails result;
    if(constantNameToConstantDetailsMap.find(constantName)!=constantNameToConstantDetailsMap.cend())
    {
        result = constantNameToConstantDetailsMap.at(constantName);
    }
    return result;
}

string Database::getMessageStructure(string const& messageName) const
{
    string result;
    if(messageNameToMessageDetailsMap.find(messageName)!=messageNameToMessageDetailsMap.cend())
    {
        result = messageNameToMessageDetailsMap.at(messageName).structureName;
    }
    return result;
}
StructureDetails Database::getStructureDetails(string const& structureName) const
{
    StructureDetails result;
    if(structureNameToStructureDetailsMap.find(structureName)!=structureNameToStructureDetailsMap.cend())
    {
        result = structureNameToStructureDetailsMap.at(structureName);
    }
    return result;
}

ParameterDetails Database::getParameterDetails(string const& structureName, string const& parameterName) const
{
    ParameterDetails result;
    if(doesThisStructureAndParameterExists(structureName, parameterName))
    {
        result = structureNameToStructureDetailsMap.at(structureName).parameters.at(parameterName);
    }
    return result;
}

EnumDetails Database::getEnumDetails(string const& enumName) const
{
    EnumDetails result;
    if(enumNameToEnumDetailsMap.find(enumName)!=enumNameToEnumDetailsMap.cend())
    {
        result = enumNameToEnumDetailsMap.at(enumName);
    }
    return result;
}

EnumParameterDetails Database::getEnumParameterDetails(string const& enumName, string const& parameterName) const
{
    EnumParameterDetails result;
    if(doesThisEnumAndParameterExists(enumName, parameterName))
    {
        result = enumNameToEnumDetailsMap.at(enumName).parameters.at(parameterName);
    }
    return result;
}

UnionDetails Database::getUnionDetails(string const& unionName) const
{
    UnionDetails result;
    if(unionNameToUnionDetailsMap.find(unionName)!=unionNameToUnionDetailsMap.cend())
    {
        result = unionNameToUnionDetailsMap.at(unionName);
    }
    return result;
}

ParameterDetails Database::getUnionParameterDetails(string const& unionName, string const& parameterName) const
{
    ParameterDetails result;
    if(doesThisUnionAndParameterExists(unionName, parameterName))
    {
        result = unionNameToUnionDetailsMap.at(unionName).parameters.at(parameterName);
    }
    return result;
}

bool Database::doesThisStructureAndParameterExists(string const& structureName, string const& parameterName) const
{
    bool result(false);
    if(doesThisStructureExists(structureName))
    {
        StructureDetails const & structureDetails = structureNameToStructureDetailsMap.at(structureName);
        StructureDetails::ParameterMap const & parameters(structureDetails.parameters);
        if(parameters.find(parameterName)!=parameters.cend())
        {
            result = true;
        }
    }
    return result;}

bool Database::doesThisStructureAndParameterExistsInVector(string const& structureName, string const& parameterName) const
{
    bool result(false);
    if(doesThisStructureExists(structureName))
    {
        StructureDetails const & structureDetails = structureNameToStructureDetailsMap.at(structureName);
        vector<string> const & parametersWithCorrectOrder(structureDetails.parametersWithCorrectOrder);
        if(find(parametersWithCorrectOrder.cbegin(), parametersWithCorrectOrder.cend(), parameterName)!=parametersWithCorrectOrder.cend())
        {
            result = true;
        }
    }
    return result;}

bool Database::doesThisEnumAndParameterExists(string const& enumName, string const& parameterName) const
{
    bool result(false);
    if(doesThisEnumExists(enumName))
    {
        EnumDetails const & enumDetails = enumNameToEnumDetailsMap.at(enumName);
        EnumDetails::ParameterMap const & parameters(enumDetails.parameters);
        if(parameters.find(parameterName)!=parameters.cend())
        {
            result=true;
        }
    }
    return result;
}

bool Database::doesThisUnionAndParameterExists(string const& unionName, string const& parameterName) const
{
    bool result(false);
    if(doesThisUnionExists(unionName))
    {
        UnionDetails const & unionDetails = unionNameToUnionDetailsMap.at(unionName);
        UnionDetails::ParameterMap const & parameters(unionDetails.parameters);
        if(parameters.find(parameterName)!=parameters.cend())
        {
            result = true;
        }
    }
    return result;}

bool Database::doesThisUnionAndParameterExistsInVector(string const& unionName, string const& parameterName) const
{
    bool result(false);
    if(doesThisUnionExists(unionName))
    {
        UnionDetails const & unionDetails = unionNameToUnionDetailsMap.at(unionName);
        vector<string> const & parametersWithCorrectOrder(unionDetails.parametersWithCorrectOrder);
        if(find(parametersWithCorrectOrder.cbegin(), parametersWithCorrectOrder.cend(), parameterName)!=parametersWithCorrectOrder.cend())
        {
            result = true;
        }
    }
    return result;}

bool Database::doesThisConstantExists(string const& constantName) const
{
    bool result(false);
    if(constantNameToConstantDetailsMap.find(constantName)!=constantNameToConstantDetailsMap.cend())
    {
        result = true;
    }
    return result;
}

bool Database::doesThisFullDetailedStructureExists(string const& structureName) const
{
    bool result(false);
    if(doesThisStructureExists(structureName))
    {
        result = !getStructureDetails(structureName).name.empty();
    }
    return result;
}

bool Database::doesThisStructureExists(string const& structureName) const
{
    bool result(false);
    if(structureNameToStructureDetailsMap.find(structureName)!=structureNameToStructureDetailsMap.cend())
    {
        result = true;
    }
    return result;
}
bool Database::doesThisEnumExists(string const& enumName) const
{
    bool result(false);
    if(enumNameToEnumDetailsMap.find(enumName)!=enumNameToEnumDetailsMap.cend())
    {
        result = true;
    }
    return result;
}
bool Database::doesThisUnionExists(string const& unionName) const
{
    bool result(false);
    if(unionNameToUnionDetailsMap.find(unionName)!=unionNameToUnionDetailsMap.cend())
    {
        result = true;
    }
    return result;
}

}
