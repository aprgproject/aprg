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
    return out;
}

istream& operator>>(istream & in, ConstantDetails& constantDetails)
{
    AlbaFileParameterReader reader(in);
    constantDetails.name = reader.readData<string>();
    constantDetails.value = reader.readData<string>();
    constantDetails.description = reader.readData<string>();
    constantDetails.descriptionFromUser = reader.readData<string>();
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
    return out;
}

istream& operator>>(istream & in, EnumDetails& enumDetails)
{
    AlbaFileParameterReader reader(in);
    enumDetails.name = reader.readData<string>();
    reader.readData(enumDetails.parameters);
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
    writer.writeData<bool>(structureDetails.isMessage);
    return out;
}

istream& operator>>(istream & in, StructureDetails& structureDetails)
{
    AlbaFileParameterReader reader(in);
    structureDetails.name = reader.readData<string>();
    reader.readData(structureDetails.parameters);
    reader.readData(structureDetails.parametersWithCorrectOrder);
    structureDetails.isMessage = reader.readData<bool>();
    return in;
}

ostream& operator<<(ostream & out, UnionDetails const& unionDetails)
{
    AlbaFileParameterWriter writer(out);
    writer.writeData<string>(unionDetails.name);
    writer.writeData(unionDetails.parameters);
    writer.writeData(unionDetails.parametersWithCorrectOrder);
    return out;
}

istream& operator>>(istream & in, UnionDetails& unionDetails)
{
    AlbaFileParameterReader reader(in);
    unionDetails.name = reader.readData<string>();
    reader.readData(unionDetails.parameters);
    reader.readData(unionDetails.parametersWithCorrectOrder);
    return in;
}

}
