#pragma once

#include <Common/User/AlbaUserInterface.hpp>
#include <InputConfiguration.hpp>

#include <string>

namespace alba::soosa {

class UserInterface {
public:
    [[nodiscard]] InputConfiguration getSavedConfiguration() const;
    void setPath(std::string const& path);
    void askUserForMainDetails();
    void askUserForFormDetails();

private:
    void saveFormDetailsFromFormDetailPath(std::string const& formDetailsFilePath);
    std::string askUserForPathOfFormDetailToRead(std::string const& formDetailsDirectoryPath);
    InputConfiguration m_savedConfiguration;
    AlbaUserInterface m_userInterface;
};

}  // namespace alba::soosa
