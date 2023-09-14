#include "SampleClassWithStatic.hpp"

namespace alba {
int SampleClassWithStatic::nonStaticFunctionWithClassDeclaration() const { return nonStaticData; }
int SampleClassWithStatic::staticFunctionWithClassDeclaration() { return staticData; }
int SampleClassWithStatic::staticData = 200;  // definition (complete type)
}  // namespace alba
