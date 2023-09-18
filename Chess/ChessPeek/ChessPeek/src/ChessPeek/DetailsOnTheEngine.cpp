#include "DetailsOnTheEngine.hpp"

using namespace std;

namespace alba::chess::ChessPeek {
BoardWithContext const& DetailsOnTheEngine::getBoardWithContext() const { return m_boardWithContext; }
void DetailsOnTheEngine::save(BoardWithContext const& boardWithContext) { m_boardWithContext = boardWithContext; }
}  // namespace alba::chess::ChessPeek
