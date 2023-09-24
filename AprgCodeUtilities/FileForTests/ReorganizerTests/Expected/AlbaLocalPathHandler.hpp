#pragma once

#if defined(OS_LINUX)
#include <Common/PathHandler/AlbaLinuxPathHandler.hpp>
#elif defined(OS_WINDOWS)  // you could also use __has_include as well
#include <Common/PathHandler/AlbaWindowsPathHandler.hpp>
#else
static_assert(false, "The operating system is not supported.");
#endif
#include <Common/PathHandler/PathContantsAndTypes.hpp>
#include <functional>
#include <set>
#include <string>

namespace alba {

#if defined(OS_LINUX)

class AlbaLocalPathHandler : public AlbaLinuxPathHandler
#elif defined(OS_WINDOWS)

class AlbaLocalPathHandler : public AlbaWindowsPathHandler
#endif

{
public:
#if defined(OS_LINUX)
    template <typename... ArgumentTypes>
    explicit AlbaLocalPathHandler(ArgumentTypes&&... arguments)
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
: AlbaLinuxPathHandler(std::forward<ArgumentTypes>(arguments)...) {}
#elif defined(OS_WINDOWS)
    template <typename... ArgumentTypes>
    explicit AlbaLocalPathHandler(ArgumentTypes&&... arguments)
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
: AlbaWindowsPathHandler(std::forward<ArgumentTypes>(arguments)...) {}
#endif

    // rule of zero
// no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
};

}  // namespace alba
