#pragma once

#include <Database.hpp>

namespace alba {

class SackFileReader {
public:
    explicit SackFileReader(Database& database);
    void readFile(std::string const& fileFullPath);

private:
    Database& m_database;
};

}  // namespace alba
