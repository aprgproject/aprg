#pragma once

#include <Database.hpp>

namespace alba {

class SackFileReader {
public:
    explicit SackFileReader(Database& database);
    void readFile(std::string const& fileName);

private:
    Database& m_database;
};

}  // namespace alba
