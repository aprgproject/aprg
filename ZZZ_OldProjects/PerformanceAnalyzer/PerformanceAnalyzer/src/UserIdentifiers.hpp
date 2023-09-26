#pragma once

#include <optional>
#include <string>

namespace alba {

struct UserIdentifiers {
    UserIdentifiers() = default;
    explicit UserIdentifiers(std::string const& lineInLogs);
    bool operator<(UserIdentifiers const& userIdentifiers) const;
    [[nodiscard]] unsigned int getNbccId() const;
    [[nodiscard]] unsigned int getCrnccId() const;
    [[nodiscard]] unsigned int getTransactionId() const;
    void saveUserIndentfiers(std::string const& lineInLogs);

private:
    void saveNbccId(std::string const& lineInLogs);
    void saveCrnccId(std::string const& lineInLogs);
    void saveTransactionId(std::string const& lineInLogs);
    std::optional<unsigned int> m_nbccIdOptional;
    std::optional<unsigned int> m_crnccIdOptional;
    std::optional<unsigned int> m_transactionIdOptional;
};

}  // namespace alba
