#include "SackFileReader.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <SackFileReader/CommentStateMachine.hpp>
#include <String/AlbaStringHelper.hpp>

#include <fstream>


#include <Debug/AlbaDebug.hpp>


using namespace alba::CommentStateMachineNamespace;
using namespace alba::stringHelper;
using namespace std;

namespace alba
{

SackFileReader::SackFileReader(Database & database)
    : m_database(database)
{}

void SackFileReader::readFile(string const& fileFullPath)
{
    CommentStateMachine commentStateMachine(State::NotInComment);
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
    ParameterDetails parameterDetails;
    EnumDetails enumDetails;
    EnumParameterDetails enumParameterDetails;
    string arraySize;

    string previousStructureName;
    string previousEnumName;
    while(fileReader.isNotFinished())
    {
        string line(getStringWithoutRedundantWhiteSpace(fileReader.getLineAndIgnoreWhiteSpaces()));
        strings tokens;
        splitToStrings<SplitStringType::WithDelimeters>(tokens, line, " ()[]{};\r\n:;/*/,");

        InputToken inputToken;
        inputToken.isNewLine = true;

        for(string const& token : tokens)
        {
            inputToken.token = token;
            commentStateMachine.processInput(inputToken);
            bool isInMultilineComment = commentStateMachine.isInMultilineComment();
            bool isNotInComment = !commentStateMachine.isInComment();
            if(state==0) //Idle state
            {
                if(token == "#define" && isNotInComment)
                {
                    if(isMessageIdFile)
                    {
                        state=3;
                    }
                    else
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
                        m_database.constantNameToConstantDetailsMap[commentDetails.name].name = commentDetails.name;
                        m_database.constantNameToConstantDetailsMap[commentDetails.name].value = commentDetails.value;
                    }
                }
            }
            else if(state == 2) //@def
            {
                if(token == "@def" || token == "Additional")
                {
                    m_database.constantNameToConstantDetailsMap[commentDetails.name].name = commentDetails.name;
                    m_database.constantNameToConstantDetailsMap[commentDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
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
                        m_database.messageNameToStructureNameMap.emplace(token, getStringInBetweenTwoStrings(line, "/* !- SIGNO(struct ", ") -! */"));
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
                            m_database.structureNameToStructureDetailsMap[structureDetails.name].isMessage = true;
                            break;
                        }
                        else if("}" == token)
                        {
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
                                if(!m_database.doesThisStructureAndParameterExistsInVector(structureDetails.name, parameterDetails.name))
                                {
                                    m_database.structureNameToStructureDetailsMap[structureDetails.name].parametersWithCorrectOrder.emplace_back(parameterDetails.name);
                                }
                                m_database.structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].name = parameterDetails.name;
                                m_database.structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].type = parameterDetails.type;
                                if(!arraySize.empty())
                                {
                                    m_database.structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].isAnArray = true;
                                    m_database.structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].arraySize = arraySize;
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
                        if(m_database.doesThisStructureAndParameterExists(previousStructureName, parameterDetails.name))
                        {
                            m_database.structureNameToStructureDetailsMap[previousStructureName].parameters[parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
                        }
                    }
                    else if(paramDescriptionState==2)
                    {
                        if(m_database.doesThisEnumAndParameterExists(previousEnumName, parameterDetails.name))
                        {
                            m_database.enumNameToEnumDetailsMap[previousEnumName].parameters[parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
                        }
                        string anotherParameterName = previousEnumName+"_"+parameterDetails.name;
                        if(m_database.doesThisEnumAndParameterExists(previousEnumName, anotherParameterName))
                        {
                            m_database.enumNameToEnumDetailsMap[previousEnumName].parameters[anotherParameterName].description = getStringWithoutRedundantWhiteSpace(partialString);
                        }
                    }

                    partialString.clear();
                    innerState=0;
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
                                m_database.enumNameToEnumDetailsMap[enumDetails.name].parameters[enumParameterDetails.name].name = enumParameterDetails.name;
                                m_database.enumNameToEnumDetailsMap[enumDetails.name].parameters[enumParameterDetails.name].value = enumParameterDetails.value;
                                m_database.enumNameToEnumDetailsMap[enumDetails.name].parameters[enumParameterDetails.name].description = enumParameterDetails.description;
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

            inputToken.isNewLine = false;
        }
    }
}


}
