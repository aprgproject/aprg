#include "UserIdentifiers.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace std;

namespace alba {

UserIdentifiers::UserIdentifiers(std::string const& lineInLogs) { saveUserIndentfiers(lineInLogs); }

bool UserIdentifiers::operator<(UserIdentifiers const& userIdentifiers) const {
    bool result(true);
    unsigned int const nbccId1(getNbccId());
    unsigned int const nbccId2(userIdentifiers.getNbccId());
    unsigned int const crnccId1(getCrnccId());
    unsigned int const crnccId2(userIdentifiers.getCrnccId());
    unsigned int const transactionId1(getTransactionId());
    unsigned int const transactionId2(userIdentifiers.getTransactionId());
    if (nbccId1 == nbccId2) {
        if (crnccId1 == crnccId2) {
            result = transactionId1 < transactionId2;
        } else {
            result = crnccId1 < crnccId2;
        }
    } else {
        result = nbccId1 < nbccId2;
    }
    return result;
}

unsigned int UserIdentifiers::getNbccId() const {
    unsigned int result(0);
    if (m_nbccIdOptional) {
        result = m_nbccIdOptional.value();
    }
    return result;
}

unsigned int UserIdentifiers::getCrnccId() const {
    unsigned int result(0);
    if (m_crnccIdOptional) {
        result = m_crnccIdOptional.value();
    }
    return result;
}

unsigned int UserIdentifiers::getTransactionId() const {
    unsigned int result(0);
    if (m_transactionIdOptional) {
        result = m_transactionIdOptional.value();
    }
    return result;
}

void UserIdentifiers::saveUserIndentfiers(std::string const& lineInLogs) {
    saveNbccId(lineInLogs);
    saveCrnccId(lineInLogs);
    saveTransactionId(lineInLogs);
}

void UserIdentifiers::saveNbccId(std::string const& lineInLogs) {
    auto nbccid = stringHelper::convertStringToNumber<unsigned int>(
        stringHelper::getNumberAfterThisString(lineInLogs, "nbccid: "));
    auto nbccId = stringHelper::convertStringToNumber<unsigned int>(
        stringHelper::getNumberAfterThisString(lineInLogs, "nbccId: "));
    if (nbccid > 0) {
        m_nbccIdOptional = nbccid;
    }
    if (nbccId > 0) {
        m_nbccIdOptional = nbccId;
    }
}

void UserIdentifiers::saveCrnccId(std::string const& lineInLogs) {
    auto crncId = stringHelper::convertStringToNumber<unsigned int>(
        stringHelper::getNumberAfterThisString(lineInLogs, "crncId: "));
    auto crnccId = stringHelper::convertStringToNumber<unsigned int>(
        stringHelper::getNumberAfterThisString(lineInLogs, "crnccId: "));
    if (crncId > 0) {
        m_crnccIdOptional = crncId;
    }
    if (crnccId > 0) {
        m_crnccIdOptional = crnccId;
    }
}

void UserIdentifiers::saveTransactionId(std::string const& lineInLogs) {
    unsigned int transactionId =
        stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "transactionId: "));
    if (transactionId > 0) {
        m_transactionIdOptional = transactionId;
    }
}

}  // namespace alba
