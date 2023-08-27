# Assign project directory, this needs aprg directory
set(JSON_LIBRARY_DIR ${APRG_DIR}/jsonLibrary/jsonLibrary/)

# Set JSON variables specific to APRG
set(JSON_BuildTests OFF)
set(JSON_CI OFF)
set(JSON_Diagnostics ON)
set(JSON_Install OFF)
set(JSON_SystemInclude ON)

# Guide to JSON flags from CMakeLists.txt
# option(JSON_BuildTests                     "Build the unit tests when ${JSON_BuildTests_INIT} is enabled." )
# option(JSON_CI                             "Enable CI build targets." OFF)
# option(JSON_Diagnostics                    "Use extended diagnostic messages." OFF)
# option(JSON_GlobalUDLs                     "Place use-defined string literals in the global namespace." ON)
# option(JSON_ImplicitConversions            "Enable implicit conversions." ON)
# option(JSON_DisableEnumSerialization       "Disable default integer enum serialization." OFF)
# option(JSON_LegacyDiscardedValueComparison "Enable legacy discarded value comparison." OFF)
# option(JSON_Install                        "Install CMake targets during install step." ${MAIN_PROJECT})
# option(JSON_MultipleHeaders                "Use non-amalgamated version of the library." ON)
# option(JSON_SystemInclude                  "Include as system headers (skip for clang-tidy)." OFF)

# Add JSON using CMakeLists.txt in JSON Library
add_subdirectory(${JSON_LIBRARY_DIR} ${CMAKE_BINARY_DIR}/jsonLibrary)
set(JSON_LIBRARY_TO_LINK nlohmann_json)
