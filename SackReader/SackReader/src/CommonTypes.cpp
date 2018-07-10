#include "CommonTypes.hpp"

#include <File/AlbaFileParameterReader.hpp>
#include <File/AlbaFileParameterWriter.hpp>

using namespace std;

namespace alba
{

ostream& operator<<(ostream & out, ConstantDetails const& constantDetails)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(constantDetails.name);
    writer.writeData<string>(constantDetails.value);
    writer.writeData<string>(constantDetails.description);
    writer.writeData<string>(constantDetails.descriptionFromUser);
    writer.writeData<string>(constantDetails.path);
    writer.writeData<bool>(constantDetails.isUsedInIfs);
    return out;
}

istream& operator>>(istream & in, ConstantDetails& constantDetails)
{
    AlbaFileParameterReader reader(in);
    constantDetails.name = reader.readData<string>();
    constantDetails.value = reader.readData<string>();
    constantDetails.description = reader.readData<string>();
    constantDetails.descriptionFromUser = reader.readData<string>();
    constantDetails.path = reader.readData<string>();
    constantDetails.isUsedInIfs = reader.readData<bool>();
    return in;
}

ostream& operator<<(ostream & out, MessageDetails const& messageDetails)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(messageDetails.name);
    writer.writeData<string>(messageDetails.structureName);
    writer.writeData<string>(messageDetails.path);
    writer.writeData<bool>(messageDetails.isUsedInIfs);
    return out;
}

istream& operator>>(istream & in, MessageDetails& messageDetails)
{
    AlbaFileParameterReader reader(in);
    messageDetails.name = reader.readData<string>();
    messageDetails.structureName = reader.readData<string>();
    messageDetails.path = reader.readData<string>();
    messageDetails.isUsedInIfs = reader.readData<bool>();
    return in;
}

ostream& operator<<(ostream & out, EnumParameterDetails const& enumParameterDetails)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(enumParameterDetails.name);
    writer.writeData<string>(enumParameterDetails.value);
    writer.writeData<string>(enumParameterDetails.description);
    writer.writeData<string>(enumParameterDetails.descriptionFromUser);
    return out;
}

istream& operator>>(istream & in, EnumParameterDetails& enumParameterDetails)
{
    AlbaFileParameterReader reader(in);
    enumParameterDetails.name = reader.readData<string>();
    enumParameterDetails.value = reader.readData<string>();
    enumParameterDetails.description = reader.readData<string>();
    enumParameterDetails.descriptionFromUser = reader.readData<string>();
    return in;
}

ostream& operator<<(ostream & out, EnumDetails const& enumDetails)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(enumDetails.name);
    writer.writeData(enumDetails.parameters);
    writer.writeData<string>(enumDetails.path);
    writer.writeData<bool>(enumDetails.isUsedInIfs);
    return out;
}

istream& operator>>(istream & in, EnumDetails& enumDetails)
{
    AlbaFileParameterReader reader(in);
    enumDetails.name = reader.readData<string>();
    reader.readData(enumDetails.parameters);
    enumDetails.path = reader.readData<string>();
    enumDetails.isUsedInIfs = reader.readData<bool>();
    return in;
}

ostream& operator<<(ostream & out, ParameterDetails const& parameterDetails)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(parameterDetails.type);
    writer.writeData<string>(parameterDetails.name);
    writer.writeData<string>(parameterDetails.description);
    writer.writeData<string>(parameterDetails.descriptionFromUser);
    writer.writeData<bool>(parameterDetails.isAnArray);
    writer.writeData<string>(parameterDetails.arraySize);
    return out;
}

istream& operator>>(istream & in, ParameterDetails& parameterDetails)
{
    AlbaFileParameterReader reader(in);
    parameterDetails.type = reader.readData<string>();
    parameterDetails.name = reader.readData<string>();
    parameterDetails.description = reader.readData<string>();
    parameterDetails.descriptionFromUser = reader.readData<string>();
    parameterDetails.isAnArray = reader.readData<bool>();
    parameterDetails.arraySize = reader.readData<string>();
    return in;
}

ostream& operator<<(ostream & out, StructureDetails const& structureDetails)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(structureDetails.name);
    writer.writeData(structureDetails.parameters);
    writer.writeData(structureDetails.parametersWithCorrectOrder);
    writer.writeData(structureDetails.path);
    writer.writeData<bool>(structureDetails.isMessage);
    writer.writeData<bool>(structureDetails.isUsedInIfs);
    return out;
}

istream& operator>>(istream & in, StructureDetails& structureDetails)
{
    AlbaFileParameterReader reader(in);
    structureDetails.name = reader.readData<string>();
    reader.readData(structureDetails.parameters);
    reader.readData(structureDetails.parametersWithCorrectOrder);
    structureDetails.path = reader.readData<string>();
    structureDetails.isMessage = reader.readData<bool>();
    structureDetails.isUsedInIfs = reader.readData<bool>();
    return in;
}

ostream& operator<<(ostream & out, UnionDetails const& unionDetails)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(unionDetails.name);
    writer.writeData(unionDetails.parameters);
    writer.writeData(unionDetails.parametersWithCorrectOrder);
    writer.writeData(unionDetails.path);
    writer.writeData<bool>(unionDetails.isUsedInIfs);
    return out;
}

istream& operator>>(istream & in, UnionDetails& unionDetails)
{
    AlbaFileParameterReader reader(in);
    unionDetails.name = reader.readData<string>();
    reader.readData(unionDetails.parameters);
    reader.readData(unionDetails.parametersWithCorrectOrder);
    unionDetails.path = reader.readData<string>();
    unionDetails.isUsedInIfs = reader.readData<bool>();
    return in;
}

ostream& operator<<(ostream & out, TypedefDetails const& typedefDetails)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(typedefDetails.name);
    writer.writeData<string>(typedefDetails.typedefDerivedName);
    writer.writeData<string>(typedefDetails.path);
    writer.writeData<bool>(typedefDetails.isUsedInIfs);
    return out;
}

istream& operator>>(istream & in, TypedefDetails& typedefDetails)
{
    AlbaFileParameterReader reader(in);
    typedefDetails.name = reader.readData<string>();
    typedefDetails.typedefDerivedName = reader.readData<string>();
    typedefDetails.path = reader.readData<string>();
    typedefDetails.isUsedInIfs = reader.readData<bool>();
    return in;
}

}
