#pragma once

#ifdef OS_WINDOWS
#include <UserAutomation/AlbaWindowsUserAutomation.hpp>
#endif
#ifdef OS_LINUX
#include <UserAutomation/AlbaLinuxUserAutomation.hpp>
#endif
#if !defined(OS_WINDOWS) && !defined(OS_LINUX)
static_assert(false, "WINDOWS and LINUX are the only supported OS yet.");
#endif

namespace alba {
#ifdef OS_WINDOWS
namespace AlbaLocalUserAutomation = AlbaWindowsUserAutomation;
#endif
#ifdef OS_LINUX
namespace AlbaLocalUserAutomation = AlbaLinuxUserAutomation;
#endif
}  // namespace alba
