#include "SackReader.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <algorithm>
#include <fstream>

#include <Debug/AlbaDebug.hpp>


using namespace alba::stringHelper;
using namespace std;

namespace alba
{

ostream& operator<<(ostream & out, ConstantDetails const& constantDetails)
{
    bool isExisting(false);
    isExisting = !constantDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << constantDetails.name << endl;
    }
    isExisting = !constantDetails.value.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << constantDetails.value << endl;
    }
    isExisting = !constantDetails.description.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << constantDetails.description << endl;
    }
    isExisting = !constantDetails.descriptionFromUser.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << constantDetails.descriptionFromUser << endl;
    }
    return out;
}

istream& operator>>(istream & in, ConstantDetails& constantDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, constantDetails.name);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, constantDetails.value);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, constantDetails.description);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, constantDetails.descriptionFromUser);
    }
    return in;
}

ostream& operator<<(ostream & out, EnumParameterDetails const& enumParameterDetails)
{
    bool isExisting(false);
    isExisting = !enumParameterDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumParameterDetails.name << endl;
    }
    isExisting = !enumParameterDetails.value.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumParameterDetails.value << endl;
    }
    isExisting = !enumParameterDetails.description.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumParameterDetails.description << endl;
    }
    isExisting = !enumParameterDetails.descriptionFromUser.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumParameterDetails.descriptionFromUser << endl;
    }
    return out;
}

istream& operator>>(istream & in, EnumParameterDetails& enumParameterDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumParameterDetails.name);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumParameterDetails.value);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumParameterDetails.description);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumParameterDetails.descriptionFromUser);
    }
    return in;
}

ostream& operator<<(ostream & out, EnumDetails const& enumDetails)
{
    bool isExisting(false);
    isExisting = !enumDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumDetails.name << endl;
    }
    out << enumDetails.parameters.size() << endl;
    for(EnumDetails::ParameterPair parameter : enumDetails.parameters)
    {
        out << parameter.second << endl;
    }
    return out;
}

istream& operator>>(istream & in, EnumDetails& enumDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumDetails.name);
    }
    unsigned int size(0);
    in >> size;
    for(unsigned int i=0; i<size; i++)
    {
        EnumParameterDetails enumParameterDetails;
        in >> enumParameterDetails;
        enumDetails.parameters.emplace(enumParameterDetails.name, enumParameterDetails);
    }
    return in;
}

ostream& operator<<(ostream & out, ParameterDetails const& parameterDetails)
{
    bool isExisting(false);
    isExisting = !parameterDetails.type.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.type << endl;
    }
    isExisting = !parameterDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.name << endl;
    }
    isExisting = !parameterDetails.description.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.description << endl;
    }
    isExisting = !parameterDetails.descriptionFromUser.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.descriptionFromUser << endl;
    }
    out << parameterDetails.isAnArray << endl;
    isExisting = !parameterDetails.arraySize.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.arraySize;
    }
    return out;
}

istream& operator>>(istream & in, ParameterDetails& parameterDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.type);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.name);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.description);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.descriptionFromUser);
    }
    in >> parameterDetails.isAnArray;
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.arraySize);
    }
    return in;
}

ostream& operator<<(ostream & out, StructureDetails const& structureDetails)
{
    bool isExisting(false);
    isExisting = !structureDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << structureDetails.name << endl;
    }
    out << structureDetails.parameters.size() << endl;
    for(std::pair<std::string, ParameterDetails> const& parameter : structureDetails.parameters)
    {
        out << parameter.second << endl;
    }
    out << structureDetails.parametersWithCorrectOrder.size() << endl;
    for(std::string const& parameterName : structureDetails.parametersWithCorrectOrder)
    {
        out << parameterName << endl;
    }

    return out;
}
istream& operator>>(istream & in, StructureDetails& structureDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, structureDetails.name);
    }
    unsigned int size(0);
    in >> size;
    for(unsigned int i=0; i<size; i++)
    {
        ParameterDetails parameterDetails;
        in >> parameterDetails;
        structureDetails.parameters.emplace(parameterDetails.name, parameterDetails);
    }
    in >> size;
    for(unsigned int i=0; i<size; i++)
    {
        string parameterName;
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterName);
        structureDetails.parametersWithCorrectOrder.emplace_back(parameterName);
    }
    return in;
}
SackReader::SackReader(string const& path)
    : m_path(path)
{
    m_path = AlbaLocalPathHandler(path).getFullPath();
}

void SackReader::checkAllFiles()
{
    AlbaLocalPathHandler pathHandler(m_path);
    ListOfPaths files;
    ListOfPaths directories;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for(string const& file : files)
    {
        AlbaLocalPathHandler filePathHandler(file);
        string extension(filePathHandler.getExtension());
        if("c" == extension || "cpp" == extension || "h" == extension || "hpp" == extension || "sig" == extension)
        {
            m_fileToPathMap.emplace(filePathHandler.getFile(), filePathHandler.getFullPath());
        }
    }
}

void SackReader::saveDatabaseToFile(std::string const& path)
{
    ofstream fileStream(path);
    bool isExisting(false);
    isExisting = !m_path.empty();
    fileStream << isExisting << endl;
    if(isExisting)
    {
        fileStream << m_path << endl;
    }
    fileStream << m_fileToPathMap.size() << endl;
    for(FileToPathPair const& pair: m_fileToPathMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        isExisting = !pair.second.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.second << endl;
        }
    }
    fileStream << m_constantNameToConstantDetailsMap.size() << endl;
    for(ConstantNameToConstantDetailsPair const& pair: m_constantNameToConstantDetailsMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        fileStream << pair.second << endl;
    }
    fileStream << m_messageNameToStructureNameMap.size() << endl;
    for(MessageNameToStructureNamePair const& pair: m_messageNameToStructureNameMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        fileStream << pair.second << endl;
    }
    fileStream << m_structureNameToStructureDetailsMap.size() << endl;
    for(StructureNameToStructureDetailsPair const& pair: m_structureNameToStructureDetailsMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        fileStream << pair.second << endl;
    }
    fileStream << m_enumNameToEnumDetailsMap.size() << endl;
    for(EnumNameToEnumDetailsPair const& pair: m_enumNameToEnumDetailsMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        fileStream << pair.second << endl;
    }
}

void SackReader::loadDatabaseFromFile(std::string const& path)
{
    ifstream fileStream(path);
    bool isExisting(false);
    unsigned int size(0);
    fileStream >> isExisting;
    if(isExisting)
    {
        while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
        getline(fileStream, m_path);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        FileToPathPair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.second);
        }
        m_fileToPathMap.emplace(pair);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        ConstantNameToConstantDetailsPair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> pair.second;
        m_constantNameToConstantDetailsMap.emplace(pair);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        MessageNameToStructureNamePair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> pair.second;
        m_messageNameToStructureNameMap.emplace(pair);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        StructureNameToStructureDetailsPair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> pair.second;
        m_structureNameToStructureDetailsMap.emplace(pair);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        EnumNameToEnumDetailsPair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> pair.second;
        m_enumNameToEnumDetailsMap.emplace(pair);
    }
}

void SackReader::checkOamTcomTupcMessages()
{
    readFile("MessageId_OamAtm.sig");
    readFile("MessageId_OamTcom.sig");
    readFile("MessageId_TassuTtm.sig");
    readFile("MessageId_OamFault.h");
    readFile("MessageId_Platform.h");
    readFile("Oam_Atm.h");
    readFile("oam_tcom.h");
    readFile("Oam_Tcom_TestModelService.h");
    readFile("Oam_Tcom_LoopTestService.h");
    readFile("tassu_ttm.h");
    readFile("SFaultInd.h");
    readFile("SModeChangeReq.h");
    readFile("SModeChangeResp.h");
    for(MessageNameToStructureNamePair const& pair: m_messageNameToStructureNameMap)
    {
        if(!pair.second.empty())
        {
            string structureFileName(pair.second+".h");
            readDefinitionFileFromStructureRecursively(structureFileName);
        }
    }
}

void SackReader::readDefinitionFileFromStructureRecursively(string const& structureFileName)
{
    readFile(structureFileName);
    AlbaLocalPathHandler pathHandler(structureFileName);
    string structureName(pathHandler.getFilenameOnly());
    if(doesThisStructureExists(structureName))
    {
        for(StructureDetails::ParameterPair const& parameterPair: m_structureNameToStructureDetailsMap[structureName].parameters)
        {
            if(!parameterPair.second.type.empty())
            {
                string structureFileNameInStructure(parameterPair.second.type+".h");
                readDefinitionFileFromStructureRecursively(structureFileNameInStructure);
            }
        }
    }
}

void SackReader::readFile(string const& fileName){
    //this should be a class

    string fileFullPath(getFileFullPath(fileName));
    ifstream fileStream(fileFullPath);
    AlbaLocalPathHandler fileFullPathHandler(fileFullPath);
    AlbaFileReader fileReader(fileStream);
    unsigned int state=0;
    unsigned int innerState=0;
    unsigned int paramDescriptionState=0;
    string partialString;
    bool isMessageIdFile = isStringFoundInsideTheOtherStringNotCaseSensitive(fileFullPathHandler.getFilenameOnly(), "MessageId_");
    ConstantDetails commentDetails;
    StructureDetails structureDetails;
    ParameterDetails parameterDetails;    EnumDetails enumDetails;
    EnumParameterDetails enumParameterDetails;
    unsigned int commentState=0;
    string arraySize;

    string previousStructureName;
    string previousEnumName;
    while(fileReader.isNotFinished())
    {
        string line(getStringWithoutRedundantWhiteSpace(fileReader.getLineAndIgnoreWhiteSpaces()));
        strings tokens;
        splitToStrings<SplitStringType::WithDelimeters>(tokens, line, " ()[]{};\r\n:;/*/,");

        if(commentState==2)
        {
            commentState=0;
        }

        for(string const& token : tokens)
        {
            if(commentState==0)
            {
                if(token=="/")
                {
                    commentState=1;
                }
            }
            else if(commentState==1)
            {
                if(token=="/")
                {
                    commentState=2; // ->//
                }
                else if(token=="*")
                {
                    commentState=3; // ->/*
                }
                else
                {
                    commentState=0;
                }
            }
            else if(commentState==3)
            {
                if(token=="*")
                {
                    commentState=4; // -> *
                }
                else
                {
                    commentState=3;
                }
            }
            else if(commentState==4)
            {
                if(token=="/")
                {
                    commentState=0; // -> */
                }
                else if(token=="*")
                {
                    commentState=4; // -> **
                }
                else
                {
                    commentState=3;
                }
            }
            bool isInSingleLineComment = commentState==2;
            bool isInMultilineComment = commentState==3 || commentState==4;
            bool isNotInComment = !isInSingleLineComment && !isInMultilineComment;
            if(state==0) //Idle state
            {
                if(token == "#define" && isNotInComment)
                {
                    if(isMessageIdFile)
                    {
                        state=3;
                    }                    else
                    {
                        state=1;
                    }
                }
                else if(token == "@def" && isInMultilineComment)
                {
                    state=2;
                }
                else if(token == "struct" && isNotInComment)
                {
                    state=4;
                }
                else if(token == "@param" && isInMultilineComment)
                {
                    state=5;
                }
                else if(token == "@struct" && isInMultilineComment)
                {
                    state=6;
                }
                else if(token == "@enum" && isInMultilineComment)
                {
                    state=7;
                }
                else if(token == "enum" && isNotInComment)
                {
                    state=8;
                }
                innerState=0;
            }
            else if(state == 1) //#define
            {
                if(!isWhiteSpace(token) && isNotInComment)
                {
                    if(innerState==0)
                    {
                        commentDetails.name = token;
                        innerState=1;
                    }
                    else if(innerState==1)
                    {
                        commentDetails.value = token;
                        innerState=0;
                        state=0;
                        m_constantNameToConstantDetailsMap[commentDetails.name].name = commentDetails.name;
                        m_constantNameToConstantDetailsMap[commentDetails.name].value = commentDetails.value;
                    }
                }
            }
            else if(state == 2) //@def
            {
                if(token == "@def" || token == "Additional")
                {
                    m_constantNameToConstantDetailsMap[commentDetails.name].name = commentDetails.name;
                    m_constantNameToConstantDetailsMap[commentDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
                    partialString.clear();
                    innerState=0;
                    if(token == "Additional")
                    {
                        state=0;
                    }
                }
                else if(innerState==0)
                {
                    if(!isWhiteSpace(token))
                    {
                        commentDetails.name = token;
                        innerState=1;
                    }
                }
                else if(innerState==1)
                {
                    if(":" == token)
                    {
                        innerState=2;
                        partialString.clear();
                    }
                }
                else if(innerState==2)
                {
                    if("*" != token)
                    {
                        partialString+=token;
                    }
                }
            }
            else if(state == 3) //#define in sig file
            {
                if(!isWhiteSpace(token) && isNotInComment)
                {
                    if(innerState==0)
                    {
                        m_messageNameToStructureNameMap.emplace(token, getStringInBetweenTwoStrings(line, "/* !- SIGNO(struct ", ") -! */"));
                        state=0;
                        innerState=0;
                        break;
                    }
                }
            }
            else if(state == 4) //struct
            {
                if(!isWhiteSpace(token) && isNotInComment && token!="/")
                {
                    if(innerState==0)
                    {
                        structureDetails.name = token;
                        innerState=1;
                    }
                    else if(innerState==1)
                    {
                        if("{" == token)
                        {
                            innerState=2;
                        }
                        else if(";" == token)
                        {
                            structureDetails.clear();
                            state=0;
                            innerState=0;
                        }
                    }
                    else if(innerState>=2)
                    {
                        if("MESSAGEHEADER" == token)
                        {
                            m_structureNameToStructureDetailsMap[structureDetails.name].isMessage = true;
                            break;
                        }
                        else if("}" == token)                        {
                            previousStructureName=structureDetails.name;
                            structureDetails.clear();
                            state = 0;
                            innerState=0;
                        }
                        else if(";" == token)
                        {
                            innerState=2;
                            if(!parameterDetails.name.empty())
                            {
                                if(!doesThisStructureAndParameterExistsInVector(structureDetails.name, parameterDetails.name))
                                {
                                    m_structureNameToStructureDetailsMap[structureDetails.name].parametersWithCorrectOrder.emplace_back(parameterDetails.name);
                                }
                                m_structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].name = parameterDetails.name;
                                m_structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].type = parameterDetails.type;
                                if(!arraySize.empty())                                {
                                    m_structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].isAnArray = true;
                                    m_structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].arraySize = arraySize;
                                    arraySize.clear();
                                }
                                parameterDetails.clear();
                            }
                        }
                        else
                        {
                            if(innerState==2)
                            {
                                parameterDetails.type = token;
                                innerState = 3;
                            }
                            else if(innerState==3)
                            {
                                parameterDetails.name = token;
                                innerState = 4;
                            }
                            else if(innerState==4)
                            {
                                if("[" == token)
                                {
                                    innerState = 5;
                                }
                            }
                            else if(innerState==5)
                            {
                                if("]" == token)
                                {
                                    arraySize = partialString;
                                    partialString.clear();
                                    innerState = 6;
                                }
                                else
                                {
                                    partialString += token;
                                }
                            }
                        }
                    }
                }
            }
            else if(state == 5) //@param
            {
                if(token == "@param" || token == "Additional")
                {
                    if(paramDescriptionState==1)
                    {
                        if(doesThisStructureAndParameterExists(previousStructureName, parameterDetails.name))
                        {
                            m_structureNameToStructureDetailsMap[previousStructureName].parameters[parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
                        }
                    }
                    else if(paramDescriptionState==2)
                    {
                        if(doesThisEnumAndParameterExists(previousEnumName, parameterDetails.name))
                        {
                            m_enumNameToEnumDetailsMap[previousEnumName].parameters[parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
                        }
                        string anotherParameterName = previousEnumName+"_"+parameterDetails.name;
                        if(doesThisEnumAndParameterExists(previousEnumName, anotherParameterName))
                        {
                            m_enumNameToEnumDetailsMap[previousEnumName].parameters[anotherParameterName].description = getStringWithoutRedundantWhiteSpace(partialString);
                        }
                    }

                    partialString.clear();                    innerState=0;
                    if(token == "Additional")
                    {
                        paramDescriptionState=0;
                        state=0;
                    }
                }
                else if(innerState==0)
                {
                    if(!isWhiteSpace(token))
                    {
                        parameterDetails.name = token;
                        innerState=1;
                    }
                }
                else if(innerState==1)
                {
                    if(":" == token)
                    {
                        innerState=2;
                        partialString.clear();
                    }
                }
                else if(innerState==2)
                {
                    if("*" != token)
                    {
                        partialString+=token;
                    }
                }
            }
            else if(state == 6) //@struct
            {
                if(!isWhiteSpace(token) && isInMultilineComment)
                {
                    previousStructureName = token;
                    state=0;
                    paramDescriptionState=1;
                }
            }
            else if(state == 7) //@enum
            {
                if(!isWhiteSpace(token) && isInMultilineComment)
                {
                    previousEnumName = token;
                    state=0;
                    paramDescriptionState=2;
                }
            }
            else if(state == 8) //enum
            {
                if(!isWhiteSpace(token) && isNotInComment && token!="/")
                {
                    if(innerState==0)
                    {
                        enumDetails.name = token;
                        innerState=1;
                    }
                    else if(innerState==1)
                    {
                        if("{" == token)
                        {
                            innerState=2;
                        }
                        else if(";" == token)
                        {
                            enumDetails.clear();
                            state=0;
                            innerState=0;
                        }
                    }
                    else if(innerState>=2)
                    {
                        if("}" == token || "," == token)
                        {
                            innerState=2;
                            if(!enumParameterDetails.name.empty())
                            {
                                m_enumNameToEnumDetailsMap[enumDetails.name].parameters[enumParameterDetails.name].name = enumParameterDetails.name;
                                m_enumNameToEnumDetailsMap[enumDetails.name].parameters[enumParameterDetails.name].value = enumParameterDetails.value;
                                m_enumNameToEnumDetailsMap[enumDetails.name].parameters[enumParameterDetails.name].description = enumParameterDetails.description;
                                enumParameterDetails.clear();
                            }
                            if("}" == token)
                            {
                                previousEnumName=enumDetails.name;
                                enumDetails.clear();
                                state = 0;
                                innerState=0;
                            }
                        }
                        else
                        {
                            if(innerState==2)
                            {
                                enumParameterDetails.name = token;
                                innerState = 3;
                            }
                            else if(innerState==3)
                            {
                                if("=" == token)
                                {
                                    innerState = 4;
                                }
                            }
                            else if(innerState==4)
                            {
                                enumParameterDetails.value = token;
                                innerState = 5;
                            }
                        }
                    }
                }
            }
        }
    }
}

void SackReader::saveSubsection(string const& subsectionName, ofstream & lyxOutputFileStream) const
{
    ifstream subsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\Subsection.txt)");
    AlbaFileReader subsectionReader(subsectionStream);

    while(subsectionReader.isNotFinished())
    {
        string subsectionLine(subsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(subsectionLine,"LYX_SUBSECTION_NAME_REPLACE"))
        {
            lyxOutputFileStream << subsectionName << endl;
        }
        else
        {
            lyxOutputFileStream << subsectionLine << endl;
        }
    }
}

void SackReader::saveMessageDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Message Definitions", lyxOutputFileStream);
    for(string const& messageName : m_messagesToGenerate)
    {
        saveMessageDefinitionSubsubsection(messageName, lyxOutputFileStream);
    }
}

void SackReader::saveStructureDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Structure Definitions", lyxOutputFileStream);
    for(StructureNameToStructureDetailsPair const& pair : m_structureNameToStructureDetailsMap)
    {
        if(!pair.second.isMessage && pair.second.isUsedInIfs)
        {
            saveStructureDefinitionSubsubsection(pair.first, lyxOutputFileStream);
        }
    }
}

void SackReader::saveEnumDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Enum Definitions", lyxOutputFileStream);
    for(EnumNameToEnumDetailsPair const& pair : m_enumNameToEnumDetailsMap)
    {
        if(pair.second.isUsedInIfs)
        {
            saveEnumDefinitionSubsubsection(pair.first, lyxOutputFileStream);
        }
    }
}

void SackReader::saveMessageDefinitionSubsubsection(string const& messageName, ofstream & messageDefinitionsStream)
{
    ifstream messageSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\MessageSubsubsection.txt)");
    AlbaFileReader messageSubsubsectionReader(messageSubsubsectionStream);

    while(messageSubsubsectionReader.isNotFinished())
    {
        string messageSubsubsectionLine(messageSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_MESSAGE_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(messageSubsubsectionLine, "LYX_TABLE_MESSAGE_NAME_REPLACE", messageName);
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_MESSAGE_STRUCTURE_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(messageSubsubsectionLine, "LYX_TABLE_MESSAGE_STRUCTURE_NAME_REPLACE", getMessageStructure(messageName));
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveMessageTable(messageName, messageDefinitionsStream);
        }
        else
        {
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
    }
}

void SackReader::saveStructureDefinitionSubsubsection(string const& structureName, ofstream & structureDefinitionsStream)
{
    ifstream structureSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\StructureSubsubsection.txt)");
    AlbaFileReader structureSubsubsectionReader(structureSubsubsectionStream);

    while(structureSubsubsectionReader.isNotFinished())
    {
        string structureSubsubsectionLine(structureSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(structureSubsubsectionLine,"LYX_TABLE_STRUCTURE_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(structureSubsubsectionLine, "LYX_TABLE_STRUCTURE_NAME_REPLACE", structureName);
            structureDefinitionsStream << structureSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(structureSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveStructureTable(structureName, structureDefinitionsStream);
        }
        else
        {
            structureDefinitionsStream << structureSubsubsectionLine << endl;
        }
    }
}

void SackReader::saveEnumDefinitionSubsubsection(string const& enumName, ofstream & enumDefinitionsStream)
{
    ifstream enumSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\EnumSubsubsection.txt)");
    AlbaFileReader enumSubsubsectionReader(enumSubsubsectionStream);

    while(enumSubsubsectionReader.isNotFinished())
    {
        string enumSubsubsectionLine(enumSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(enumSubsubsectionLine,"LYX_TABLE_ENUM_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(enumSubsubsectionLine, "LYX_TABLE_ENUM_NAME_REPLACE", enumName);
            enumDefinitionsStream << enumSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(enumSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveEnumTable(enumName, enumDefinitionsStream);
        }
        else
        {
            enumDefinitionsStream << enumSubsubsectionLine << endl;
        }
    }
}

void SackReader::generateLyxDocument(string const& templatePath, string const& finalDocumentPath)
{
    ifstream lyxDocumentTemplate(templatePath);
    ofstream lyxFinalDocumentStream(finalDocumentPath);
    AlbaFileReader lyxDocumentTemplateReader(lyxDocumentTemplate);

    bool isInsideGeneratedCode(false);
    while(lyxDocumentTemplateReader.isNotFinished())
    {
        string line(lyxDocumentTemplateReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(line,"LYX_START_GENERATED_CODE"))
        {
            isInsideGeneratedCode = true;
            lyxFinalDocumentStream << line << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(line,"LYX_END_GENERATED_CODE"))
        {
            isInsideGeneratedCode = false;
            saveMessageDefinitions(lyxFinalDocumentStream);
            saveStructureDefinitions(lyxFinalDocumentStream);
            saveEnumDefinitions(lyxFinalDocumentStream);
            lyxFinalDocumentStream << line << endl;
        }
        else if(!isInsideGeneratedCode)
        {
            lyxFinalDocumentStream << line << endl;
        }
    }
}

void SackReader::loadMessagesToGenerate(string const& path)
{
    ifstream messageToGenerateStream(path);
    AlbaFileReader messageToGenerateReader(messageToGenerateStream);
    while(messageToGenerateReader.isNotFinished())
    {
        string line(messageToGenerateReader.getLine());
        if(!line.empty())
        {
            m_messagesToGenerate.emplace(line);
        }
    }
}

void SackReader::loadDescriptionToAdd(string const& path)
{
    ifstream messageToGenerateStream(path);
    AlbaFileReader messageToGenerateReader(messageToGenerateStream);
    string structureName, parameterName;
    while(messageToGenerateReader.isNotFinished())
    {
        string line(messageToGenerateReader.getLine());
        if(!line.empty())
        {
            if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&struct:"))
            {
                structureName = getStringAfterThisString(line, "&&&struct:");
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&param:"))
            {
                parameterName = getStringAfterThisString(line, "&&&param:");
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&description:"))
            {
                string description(getStringAfterThisString(line, "&&&description:"));
                m_structureNameToStructureDetailsMap[structureName].parameters[parameterName].name = parameterName;
                m_structureNameToStructureDetailsMap[structureName].parameters[parameterName].descriptionFromUser = description;
            }
        }
    }
}

void SackReader::saveMessageTable(string const& messageName, ofstream & messageTableStream)
{
    DisplayTable messageTable;
    messageTable.setBorders("-"," | ");
    messageTable.addRow();
    messageTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    messageTable.getLastRow().addCell("\\series bold \nIE Type");
    messageTable.getLastRow().addCell("\\series bold \nDescription");
    generateStructureForDisplayTablesIfNeeded(getMessageStructure(messageName), messageTable, "", true);
    //cout<<messageTable.drawOutput()<<endl;
    saveDisplayTable(messageTable, messageTableStream);
}

void SackReader::saveStructureTable(string const& structureName, ofstream & structureTableStream)
{
    DisplayTable structureTable;
    structureTable.setBorders("-"," | ");
    structureTable.addRow();
    structureTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    structureTable.getLastRow().addCell("\\series bold \nIE Type");
    structureTable.getLastRow().addCell("\\series bold \nDescription");
    generateStructureForDisplayTablesIfNeeded(structureName, structureTable, "", false);
    if(structureTable.getTotalRows()>1)
    {
        //cout<<structureTable.drawOutput()<<endl;
        saveDisplayTable(structureTable, structureTableStream);
    }
}

void SackReader::saveEnumTable(string const& enumName, ofstream & enumTableStream)
{
    DisplayTable enumTable;
    enumTable.setBorders("-"," | ");
    enumTable.addRow();
    enumTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    enumTable.getLastRow().addCell("\\series bold \n Value");
    enumTable.getLastRow().addCell("\\series bold \nDescription");
    generateEnumForDisplayTablesIfNeeded(enumName, enumTable);
    //cout<<enumTable.drawOutput()<<endl;
    saveDisplayTable(enumTable, enumTableStream);
}

void SackReader::saveDisplayTable(DisplayTable const& displayTable, ofstream & displayTableStream) const
{
    ifstream tableTemplateStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\Table.txt)");
    AlbaFileReader tableTemplateReader(tableTemplateStream);
    while(tableTemplateReader.isNotFinished())
    {        string tableTemplateLine(tableTemplateReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_REPLACE"))
        {
            for(unsigned int row=0; row<displayTable.getTotalRows(); row++)
            {
                ifstream tableRowTemplateStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\TableRow.txt)");
                AlbaFileReader tableRowTemplateReader(tableRowTemplateStream);
                while(tableRowTemplateReader.isNotFinished())
                {                    string tableRowTemplateLine(tableRowTemplateReader.getLine());
                    if(isStringFoundInsideTheOtherStringCaseSensitive(tableRowTemplateLine,"LYX_TABLE_ROW_REPLACE"))
                    {
                        for(unsigned int column=0; column<displayTable.getTotalColumns(); column++)
                        {
                            ifstream tableCellTemplateStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\TableCell.txt)");
                            AlbaFileReader tableCellTemplateReader(tableCellTemplateStream);
                            while(tableCellTemplateReader.isNotFinished())
                            {                                string tableCellTemplateLine(tableCellTemplateReader.getLine());
                                if(isStringFoundInsideTheOtherStringCaseSensitive(tableCellTemplateLine,"LYX_TABLE_CELL_REPLACE"))
                                {
                                    displayTableStream << displayTable.getCellConstReference(row, column).getText()<<endl;
                                }
                                else
                                {
                                    displayTableStream << tableCellTemplateLine << endl;
                                }
                            }
                        }                    }
                    else
                    {
                        displayTableStream << tableRowTemplateLine << endl;
                    }
                }
            }        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_NUM_ROW_REPLACE")
                || isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_NUM_COLUMN_REPLACE"))
        {
            NumberToStringConverter converter;
            transformReplaceStringIfFound(tableTemplateLine, "LYX_TABLE_NUM_ROW_REPLACE", converter.convert(displayTable.getTotalRows()));
            transformReplaceStringIfFound(tableTemplateLine, "LYX_TABLE_NUM_COLUMN_REPLACE", converter.convert(displayTable.getTotalColumns()));
            displayTableStream << tableTemplateLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_COLUMN_REPLACE"))
        {
            for(unsigned int i=0; i<displayTable.getTotalColumns()-1; i++) //until description
            {
                displayTableStream << tableTemplateLine << endl;
            }
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_DESCRIPTION_COLUMN_REPLACE"))
        {
            displayTableStream << tableTemplateLine << endl; //for description
        }
        else
        {
            displayTableStream << tableTemplateLine << endl;
        }
    }
}

void SackReader::generateStructureForDisplayTablesIfNeeded(string const& structureName, DisplayTable & displayTable, string const& indentionInType, bool const areInnerStructuresGenerated)
{
    string smallTextModifier("\\size footnotesize\n");
    if(doesThisStructureExists(structureName))
    {
        m_structureNameToStructureDetailsMap[structureName].isUsedInIfs=true;
        StructureDetails structureDetails(getStructureDetails(structureName));
        for(string const& parameterName : structureDetails.parametersWithCorrectOrder)
        {
            ParameterDetails parameterDetails = getParameterDetails(structureName, parameterName);
            displayTable.addRow();
            displayTable.getLastRow().addCell(smallTextModifier+indentionInType+" "+parameterDetails.name);
            string finalType(parameterDetails.type);
            if(parameterDetails.isAnArray)
            {
                finalType = finalType+" ["+parameterDetails.arraySize+"]";
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalType);

            string sackDescription(getStringWithoutStartingAndTrailingWhiteSpace(getStringWithFirstLetterCapital(parameterDetails.description)));
            string userDescription(getStringWithoutStartingAndTrailingWhiteSpace(getStringWithFirstLetterCapital(parameterDetails.descriptionFromUser)));
            string finalDescription;
            if(!userDescription.empty())
            {
                if(sackDescription!=userDescription)
                {
                    //cout <<"The description needs to be aligned with sack."<<endl;
                    /*cout<<"Structure: "<<structureName<<" Parameter: "<<parameterDetails.name<<endl;
                    cout<<"sackDescription: ["<<sackDescription<<"]"<<endl;
                    cout<<"userDescription: ["<<userDescription<<"]"<<endl;*/
                }
                finalDescription = userDescription;
            }
            else
            {
                finalDescription = sackDescription;
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
            if(areInnerStructuresGenerated)
            {
                string typeName(parameterDetails.type);
                if(doesThisEnumExists(typeName))
                {
                    m_enumNameToEnumDetailsMap[typeName].isUsedInIfs=true;
                }
                generateStructureForDisplayTablesIfNeeded(parameterDetails.type, displayTable, indentionInType+">", true);
            }
        }
    }
}

void SackReader::generateEnumForDisplayTablesIfNeeded(string const& enumName, DisplayTable & displayTable)
{
    string smallTextModifier("\\size footnotesize\n");
    if(doesThisEnumExists(enumName))
    {
        EnumDetails enumDetails(getEnumDetails(enumName));

        vector<string> sortedEnumParameterNamesByValue;
        for(EnumDetails::ParameterPair const& parameterPair : enumDetails.parameters)
        {
            sortedEnumParameterNamesByValue.emplace_back(parameterPair.first);
        }
        std::sort(sortedEnumParameterNamesByValue.begin(), sortedEnumParameterNamesByValue.end(), [&](string const& parameterName1, string const& parameterName2)
        {
            EnumParameterDetails parameterDetails1 = getEnumParameterDetails(enumName, parameterName1);
            EnumParameterDetails parameterDetails2 = getEnumParameterDetails(enumName, parameterName2);
            return convertHexStringToNumber<unsigned int>(parameterDetails1.value)<convertHexStringToNumber<unsigned int>(parameterDetails2.value);
        });

        for(string const& parameterName : sortedEnumParameterNamesByValue)
        {
            EnumParameterDetails parameterDetails = getEnumParameterDetails(enumName, parameterName);
            displayTable.addRow();
            displayTable.getLastRow().addCell(smallTextModifier+" "+parameterDetails.name);
            displayTable.getLastRow().addCell(smallTextModifier+parameterDetails.value);
            string sackDescription(getStringWithoutStartingAndTrailingWhiteSpace(getStringWithFirstLetterCapital(parameterDetails.description)));
            string userDescription(getStringWithoutStartingAndTrailingWhiteSpace(getStringWithFirstLetterCapital(parameterDetails.descriptionFromUser)));
            string finalDescription;
            if(!userDescription.empty())
            {
                if(sackDescription!=userDescription)
                {
                    //cout <<"The description needs to be aligned with sack."<<endl;
                    /*cout<<"Enum: "<<enumName<<" Parameter: "<<parameterDetails.name<<endl;
                    cout<<"sackDescription: ["<<sackDescription<<"]"<<endl;
                    cout<<"userDescription: ["<<userDescription<<"]"<<endl;*/
                }
                finalDescription = userDescription;
            }
            else
            {
                finalDescription = sackDescription;
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
        }
    }
}
string SackReader::getFileFullPath(string const& fileName) const
{
    string result;
    if(m_fileToPathMap.find(fileName)!=m_fileToPathMap.cend())
    {
        result = m_fileToPathMap.at(fileName);
    }
    return result;
}

ConstantDetails SackReader::getConstantDetails(string const& constantName) const
{
    ConstantDetails result;
    if(m_constantNameToConstantDetailsMap.find(constantName)!=m_constantNameToConstantDetailsMap.cend())
    {
        result = m_constantNameToConstantDetailsMap.at(constantName);
    }
    return result;
}

string SackReader::getMessageStructure(string const& messageName) const
{
    string result;
    if(m_messageNameToStructureNameMap.find(messageName)!=m_messageNameToStructureNameMap.cend())
    {
        result = m_messageNameToStructureNameMap.at(messageName);
    }
    return result;
}

StructureDetails SackReader::getStructureDetails(string const& structureName) const
{
    StructureDetails result;
    if(m_structureNameToStructureDetailsMap.find(structureName)!=m_structureNameToStructureDetailsMap.cend())
    {
        result = m_structureNameToStructureDetailsMap.at(structureName);
    }
    return result;
}

ParameterDetails SackReader::getParameterDetails(string const& structureName, string const& parameterName) const
{
    ParameterDetails result;
    if(doesThisStructureAndParameterExists(structureName, parameterName))
    {
        result = m_structureNameToStructureDetailsMap.at(structureName).parameters.at(parameterName);
    }
    return result;
}

EnumDetails SackReader::getEnumDetails(string const& enumName) const
{
    EnumDetails result;
    if(m_enumNameToEnumDetailsMap.find(enumName)!=m_enumNameToEnumDetailsMap.cend())
    {
        result = m_enumNameToEnumDetailsMap.at(enumName);
    }
    return result;
}

EnumParameterDetails SackReader::getEnumParameterDetails(string const& enumName, string const& parameterName) const
{
    EnumParameterDetails result;
    if(doesThisEnumAndParameterExists(enumName, parameterName))
    {
        result = m_enumNameToEnumDetailsMap.at(enumName).parameters.at(parameterName);
    }
    return result;
}

bool SackReader::doesThisStructureAndParameterExists(string const& structureName, string const& parameterName) const
{
    bool result(false);    if(doesThisStructureExists(structureName))
    {
        StructureDetails const & structureDetails = m_structureNameToStructureDetailsMap.at(structureName);
        StructureDetails::ParameterMap const & parameters(structureDetails.parameters);
        if(parameters.find(parameterName)!=parameters.cend())
        {
            result=true;
        }
    }
    return result;
}

bool SackReader::doesThisEnumAndParameterExists(string const& enumName, string const& parameterName) const
{
    bool result(false);
    if(doesThisEnumExists(enumName))
    {
        EnumDetails const & enumDetails = m_enumNameToEnumDetailsMap.at(enumName);
        EnumDetails::ParameterMap const & parameters(enumDetails.parameters);
        if(parameters.find(parameterName)!=parameters.cend())
        {
            result=true;
        }
    }
    return result;
}

bool SackReader::doesThisStructureAndParameterExistsInVector(string const& structureName, string const& parameterName) const
{
    bool result(false);
    if(doesThisStructureExists(structureName))
    {
        StructureDetails const & structureDetails = m_structureNameToStructureDetailsMap.at(structureName);
        vector<string> const & parametersWithCorrectOrder(structureDetails.parametersWithCorrectOrder);
        if(std::find(parametersWithCorrectOrder.cbegin(), parametersWithCorrectOrder.cend(), parameterName)!=parametersWithCorrectOrder.cend())
        {
            result=true;
        }
    }
    return result;
}

bool SackReader::doesThisStructureExists(string const& structureName) const
{
    bool result(false);    if(m_structureNameToStructureDetailsMap.find(structureName)!=m_structureNameToStructureDetailsMap.cend())
    {
        return true;
    }
    return result;
}

bool SackReader::doesThisEnumExists(string const& enumName) const
{
    bool result(false);
    if(m_enumNameToEnumDetailsMap.find(enumName)!=m_enumNameToEnumDetailsMap.cend())
    {
        return true;
    }
    return result;
}

void SackReader::performHacks()
{
    StructureDetails & structureDetails(m_structureNameToStructureDetailsMap["SMessageAddress"]);
    structureDetails.name = "SMessageAddress";
    structureDetails.isMessage = false;
    structureDetails.isUsedInIfs = true;
    structureDetails.parametersWithCorrectOrder.clear();
    structureDetails.parametersWithCorrectOrder.emplace_back("board");
    structureDetails.parametersWithCorrectOrder.emplace_back("cpu");
    structureDetails.parametersWithCorrectOrder.emplace_back("task");
    structureDetails.parameters["board"].name = "board";
    structureDetails.parameters["board"].type = "TBoard";
    structureDetails.parameters["board"].isAnArray = false;
    structureDetails.parameters["board"].descriptionFromUser = "Board in SMessageAddress";
    structureDetails.parameters["cpu"].name = "cpu";
    structureDetails.parameters["cpu"].type = "TCpu";
    structureDetails.parameters["cpu"].isAnArray = false;
    structureDetails.parameters["cpu"].descriptionFromUser = "Cpu in SMessageAddress";
    structureDetails.parameters["task"].name = "task";
    structureDetails.parameters["task"].type = "TTask";
    structureDetails.parameters["task"].isAnArray = false;
    structureDetails.parameters["task"].descriptionFromUser = "Task in SMessageAddress";
}



}