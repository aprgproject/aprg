# Assign macros, common flags, definitions and other common steps

# Macros
include(${APRG_DIR}/AllCommonCMakeFiles/PrintMacros.cmake)
include(${APRG_DIR}/AllCommonCMakeFiles/FileAndDirectoryMacros.cmake)

# Options needs to be first because its value is needed on other cmake
include(${APRG_DIR}/AllCommonCMakeFiles/CommonCMakeOptions.cmake)

# The rest of the common steps
include(${APRG_DIR}/AllCommonCMakeFiles/CommonCMakeVariables.cmake)
include(${APRG_DIR}/AllCommonCMakeFiles/CommonCompilerFlags.cmake)
include(${APRG_DIR}/AllCommonCMakeFiles/CommonDefinitions.cmake)
include(${APRG_DIR}/AllCommonCMakeFiles/CommonDependencies.cmake)
