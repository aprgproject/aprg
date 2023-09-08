#include "SampleClassWithStatic.hpp"

namespace alba {
int SampleClassWithStatic::staticFunctionWithClassDeclaration() { return staticData; }
int SampleClassWithStatic::nonStaticFunctionWithClassDeclaration() const { return nonStaticData; }
int SampleClassWithStatic::staticData = 200;  // definition (complete type)
}  // namespace alba
