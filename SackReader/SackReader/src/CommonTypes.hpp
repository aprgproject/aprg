#pragma once

#include <map>
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
    friend std::ostream & operator<<(std::ostream & out, StructureDetails const& structureDetails);
    friend std::istream & operator>>(std::istream & in, StructureDetails& structureDetails);
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

} // namespace alba
