#include "SackFileReader.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <SackFileReader/CommentStateMachine.hpp>
#include <SackFileReader/SackFileReaderStateMachine.hpp>
#include <String/AlbaStringHelper.hpp>

#include <fstream>


#include <Debug/AlbaDebug.hpp>


using namespace alba::CommentStateMachineNamespace;
using namespace alba::SackFileReaderStateMachineNamespace;
using namespace alba::stringHelper;
using namespace std;

namespace alba
{

SackFileReader::SackFileReader(Database & database)
    : m_database(database)
{}

void SackFileReader::readFile(string const& fileFullPath)
{
    CommentStateMachine commentStateMachine;
    ifstream fileStream(fileFullPath);
    AlbaLocalPathHandler fileFullPathHandler(fileFullPath);
    AlbaFileReader fileReader(fileStream);
    SackFileReaderStateMachine sackFileReaderStateMachine(m_database, fileFullPathHandler.getFilenameOnly());
    sackFileReaderStateMachine.setIsMessageIdFileFlag(isStringFoundInsideTheOtherStringNotCaseSensitive(fileFullPathHandler.getFilenameOnly(), "MessageId_"));
    while(fileReader.isNotFinished())
    {        string line(getStringWithoutRedundantWhiteSpace(fileReader.getLineAndIgnoreWhiteSpaces()));
        strings tokens;
        splitToStrings<SplitStringType::WithDelimeters>(tokens, line, " ()[]{};\r\n:;/*/,");
        CommentStateMachineNamespace::InputToken commentStateMachineInputToken;
        commentStateMachineInputToken.isNewLine = true;

        for(string const& token : tokens)
        {
            commentStateMachineInputToken.token = token;
            commentStateMachine.processInput(commentStateMachineInputToken);

            SackFileReaderStateMachineNamespace::InputToken sackFileReaderStateMachineInputToken;
            sackFileReaderStateMachineInputToken.isInMultilineComment = commentStateMachine.isInMultilineComment();
            sackFileReaderStateMachineInputToken.isNotInComment = !commentStateMachine.isInComment();
            sackFileReaderStateMachineInputToken.token = token;
            sackFileReaderStateMachineInputToken.line = line;
            sackFileReaderStateMachine.processInput(sackFileReaderStateMachineInputToken);

            commentStateMachineInputToken.isNewLine = false;
            if(sackFileReaderStateMachine.isNextLineNeeded())
            {
                 break;
            }
        }
    }
}


}
