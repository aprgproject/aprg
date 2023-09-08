#include "AlbaStreamParameterWriter.hpp"

using namespace std;

namespace alba {

AlbaStreamParameterWriter::AlbaStreamParameterWriter(ostream& stream) : m_stream(stream) {}

template <>
void AlbaStreamParameterWriter::writeData(string const& data) const {
    writeStringViewData(data);
}

void AlbaStreamParameterWriter::writeData(string_view const data) const { writeStringViewData(data); }
void AlbaStreamParameterWriter::flush() { m_stream.flush(); }

void AlbaStreamParameterWriter::writeStringViewData(string_view const data) const {
    bool isExisting(!data.empty());
    m_stream << isExisting << "\n";
    if (isExisting) {
        m_stream << data << "\n";
    }
}

}  // namespace alba
