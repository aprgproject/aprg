#pragma once

#if defined(OS_APPLE) || defined(OS_LINUX)
#include <Common/PathHandler/AlbaLinuxPathHandler.hpp>
#elif defined(OS_WINDOWS)  // you could also use __has_include as well
#include <Common/PathHandler/AlbaWindowsPathHandler.hpp>
#else
static_assert(false, "The OS is not supported.");
#endif

#include <Common/PathHandler/PathContantsAndTypes.hpp>

#include <functional>
#include <set>
#include <string>

namespace alba {

#if defined(OS_APPLE) || defined(OS_LINUX)
class AlbaLocalPathHandler : public AlbaLinuxPathHandler
#elif defined(OS_WINDOWS)
class AlbaLocalPathHandler : public AlbaWindowsPathHandler
#endif

{
public:
#if defined(OS_APPLE) || defined(OS_LINUX)
    template <typename... ArgumentTypes>
    AlbaLocalPathHandler(ArgumentTypes&&... arguments)
        : AlbaLinuxPathHandler(std::forward<ArgumentTypes>(arguments)...) {}
#elif defined(OS_WINDOWS)
    template <typename... ArgumentTypes>
    AlbaLocalPathHandler(ArgumentTypes&&... arguments)
        : AlbaWindowsPathHandler(std::forward<ArgumentTypes>(arguments)...) {}
#endif

    // rule of zero
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
};

}  // namespace alba
