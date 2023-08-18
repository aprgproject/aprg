#include <SailIt.hpp>

#include <gtest/gtest.h>

#include <fstream>

using namespace codeReview;
using namespace std;

// TEST(Sct, DISABLED_ActualTest)
TEST(Sct, ActualTest) {
    SailIt sailIt;
    sailIt.getFileDirectoryDatabaseReference().addFileOrDirectory(APRG_DIR
                                                                  "/ZZZ_OldProjects/ACodeReview/FilesForTests/include");
    // sailIt.addAndAnalyzeThisFileToCPlusPlusDatabase (APRG_DIR
    // "/ZZZ_OldProjects/ACodeReview/FilesForTests/include/c++/iostream");
    sailIt.addAndAnalyzeThisFileToCPlusPlusDatabase(APRG_DIR
                                                    "/ZZZ_OldProjects/ACodeReview/FilesForTests/include/stdio.h");
    // sailIt.addAndAnalyzeThisFileToCPlusPlusDatabase(APRG_DIR
    // "/ZZZ_OldProjects/ACodeReview/FilesForTests/include/_mingw.h");
    // sailIt.addAndAnalyzeThisFileToCPlusPlusDatabase(APRG_DIR
    // "/ZZZ_OldProjects/ACodeReview/FilesForTests/include/_mingw_off_t.h");
    ofstream outputFile(APRG_DIR "/ZZZ_OldProjects/ACodeReview/FilesForTests/outputFile.txt");
    sailIt.printAll(outputFile);
    ofstream unprocessedTermFile(APRG_DIR "/ZZZ_OldProjects/ACodeReview/FilesForTests/unprocessedTerm.txt");
    sailIt.printFindings(unprocessedTermFile, "Unprocessed term");
}
