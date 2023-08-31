#include "SampleClassWithStatic.hpp"

namespace alba {

int SampleClassWithStatic::staticData = 200;  // definition (complete type)

int SampleClassWithStatic::nonStaticFunctionWithClassDeclaration() const { return nonStaticData; }

int SampleClassWithStatic::staticFunctionWithClassDeclaration() { return staticData; }

}  // namespace alba
