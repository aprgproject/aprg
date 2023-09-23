#pragma once

#include "BtsLogTime.hpp"

#include <string>

namespace wcdmaToolsBackend {

namespace BtsLogPrintStateMachine {

enum class State {
    UnknownState,
    PcTimeState1_Number,
    PcTimeState2_Period,
    PcTimeState3_Space,
    PcTimeState4_Colon,
    PcTimeState5_Colon,
    PcTimeState6_Period,
    hardwareAddressState1_Letters,
    hardwareAddressState2_Dash,
    hardwareAddressState2_Underscore,
    hardwareAddressState3_HexNumbers,
    hardwareAddressState3_Letters,
    BtsTimeState,
    StopCheckingState
};

struct TransactionData {
    TransactionData() = default;
    bool isPcTimeSaved{false};
    bool isHardwareAddressSaved{false};
    bool isBtsTimeSaved{false};
    int pcTimeStartIndex{0};
    int pcTimeEndIndex{0};
    int hardwareAddressStartIndex{0};
    int hardwareAddressEndIndex{0};
    int btsTimeStartIndex{0};
    int btsTimeEndIndex{0};
    int count{0};
};

}  // namespace BtsLogPrintStateMachine

class BtsLogPrint {
public:
    BtsLogPrint() = default;
    explicit BtsLogPrint(std::string const& lineInLogs);
    BtsLogPrint(std::string const& filename, std::string const& lineInLogs);
    BtsLogPrint(std::string&& filename, std::string const& lineInLogs);
    bool operator<(BtsLogPrint const& btsLogPrintToCompare) const;
    bool operator>(BtsLogPrint const& btsLogPrintToCompare) const;
    bool operator==(BtsLogPrint const& btsLogPrintToCompare) const;
    [[nodiscard]] BtsLogTime getBtsTime() const;
    [[nodiscard]] BtsLogTime getPcTime() const;
    [[nodiscard]] std::string getHardwareAddress() const;
    [[nodiscard]] std::string getPrint() const;
    [[nodiscard]] std::string getPrintWithAllDetails() const;
    [[nodiscard]] bool isEmpty() const;
    void clear();
    void updatePcTimeAndFileNameDetails(BtsLogPrint const& logPrint);
    friend std::istream& operator>>(std::istream& in, BtsLogPrint& btsLogPrint);
    friend std::ostream& operator<<(std::ostream& out, BtsLogPrint const& btsLogPrint);

private:
    static inline void handleUnknownState(
        BtsLogPrintStateMachine::State& state, BtsLogPrintStateMachine::TransactionData& transactionData,
        int const index, char const character);

    static inline void handlePcTimeState1(BtsLogPrintStateMachine::State& state, char const character);
    static inline void handlePcTimeState2(BtsLogPrintStateMachine::State& state, char const character);
    static inline void handlePcTimeState3(BtsLogPrintStateMachine::State& state, char const character);
    static inline void handlePcTimeState4(BtsLogPrintStateMachine::State& state, char const character);
    static inline void handlePcTimeState5(BtsLogPrintStateMachine::State& state, char const character);

    static inline void handlePcTimeState6(
        BtsLogPrintStateMachine::State& state, BtsLogPrintStateMachine::TransactionData& transactionData,
        int const index, char const character);

    static inline void handleHardWareAddressState1_Letters(
        BtsLogPrintStateMachine::State& state, BtsLogPrintStateMachine::TransactionData& transactionData,
        char const character);

    static inline void handleHardWareAddressState2_Dash(
        BtsLogPrintStateMachine::State& state, BtsLogPrintStateMachine::TransactionData& transactionData,
        char const character);

    static inline void handleHardWareAddressState2_Underscore(
        BtsLogPrintStateMachine::State& state, BtsLogPrintStateMachine::TransactionData& transactionData,
        char const character);

    static inline void handleHardWareAddressState3_HexNumbers(
        BtsLogPrintStateMachine::State& state, BtsLogPrintStateMachine::TransactionData& transactionData,
        int const index, char const character);

    static inline void handleHardWareAddressState3_Letters(
        BtsLogPrintStateMachine::State& state, BtsLogPrintStateMachine::TransactionData& transactionData,
        int const index, char const character);

    static inline void handleBtsTimeState(
        BtsLogPrintStateMachine::State& state, BtsLogPrintStateMachine::TransactionData& transactionData,
        int const index, char const character);

    void analyzeLineInLogs(std::string const& lineInLogs);
    BtsLogTime m_btsTime;
    BtsLogTime m_pcTime;
    std::string m_hardwareAddress;
    std::string m_print;
    std::string m_fileName;
};

}  // namespace wcdmaToolsBackend
