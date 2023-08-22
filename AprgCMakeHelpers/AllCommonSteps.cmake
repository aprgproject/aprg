# Assign macros, common flags, definitions and other common steps

# Macros
include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)

# Options needs to be first because its value is needed on other cmake
include(${APRG_DIR}/AprgCMakeHelpers/CommonCMakeOptions.cmake)

# The rest of the common steps
include(${APRG_DIR}/AprgCMakeHelpers/CommonCMakeVariables.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonCompilerFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDependencies.cmake)
