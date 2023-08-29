#include <CPlusPlus/Utilities.hpp>

#include <map>

namespace codeReview {

using namespace std;

class Looper;
typedef int LooperIndex;
typedef unsigned int UniqueId;
typedef map<UniqueId, Looper*> ActiveLoopersMap;

struct ModifyDetails {
    ModifyDetails() : m_startIndex(0), m_lengthAdded(0) {}
    ModifyDetails(int startIndex, int lengthAdded) : m_startIndex(startIndex), m_lengthAdded(lengthAdded) {}
    void setModifyDetails(int startIndex, int lengthAdded) {
        m_startIndex = startIndex;
        m_lengthAdded = lengthAdded;
    }
    int m_startIndex;
    int m_lengthAdded;
};

class Looper {
public:
    Looper(DequeOfTerms& terms, UniqueId const uniqueFileId);
    Looper(Looper const& copyLooper);
    Looper(Looper const& startLooper, Looper const& endLooper);
    ~Looper();

    friend ostream& operator<<(ostream& out, Looper const& looper);

    Looper operator+(int const offset) const;
    Looper operator-(int const offset) const;
    void operator++(int);
    void operator--(int);

    [[nodiscard]] bool isFinished() const;
    [[nodiscard]] bool isNotFinished() const;
    [[nodiscard]] bool isNotFinishedWhenBackward() const;
    [[nodiscard]] DequeOfTerms const& getTermsConstReference() const;
    [[nodiscard]] Term& getContentReference() const;
    [[nodiscard]] int getCurrentIndex() const;
    [[nodiscard]] TermsIterator getCurrentIterator() const;
    [[nodiscard]] int getEndIndex() const;
    [[nodiscard]] TermsIterator getEndIterator() const;
    [[nodiscard]] int getLength() const;
    [[nodiscard]] UniqueId getUniqueFileId() const;

    void setCurrentIndex(Looper const& indexLooper);
    void hardSetCurrentIndex(LooperIndex const index);
    void copyLooper(Looper const& copyLooper);
    void setContent(Term const& term);
    void setEndIndex(Looper const& indexLooper);
    static void fixLoopers(UniqueId const uniqueFileId, ModifyDetails const& modifyDetails);

private:
    void fixIndexes(ModifyDetails const& modifyDetails);
    static int getFixedIndex(int const indexToFix, ModifyDetails const& modifyDetails);
    void doAtConstruction();
    void doAtDestruction();
    LooperIndex m_currentIndex;
    LooperIndex m_endIndex;
    DequeOfTerms& m_terms;
    UniqueId m_uniqueGroupId;
    UniqueId m_uniqueId{};
    static UniqueId s_objectCount;
    static ActiveLoopersMap s_activeLoopers;
};

}  // namespace codeReview
