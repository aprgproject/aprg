#include <RevisionEditor/RevisionEditor.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SampleTest, EditCommitDatesTest) {
    RevisionEditor entity;

    entity.setRevisionDataFromFile();
    entity.editCommitDates();
    entity.editCommitMessages();
    entity.saveNewRevisionHistory();
}

}  // namespace alba
