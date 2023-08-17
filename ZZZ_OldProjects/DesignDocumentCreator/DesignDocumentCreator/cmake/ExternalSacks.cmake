

# Assign Sack Directory
set(EXTERNAL_SACK_DIRECTORY ${DD_CREATOR_DIR}/externalSacks)

set(EXTERNAL_SACK_DIRECTORIES
${DD_CREATOR_DIR}/externalSacks
${DD_CREATOR_DIR}/externalSacks/MCU/Definitions
${DD_CREATOR_DIR}/externalSacks/MCU/Messages
${DD_CREATOR_DIR}/externalSacks/MCU/ServiceInterface
${DD_CREATOR_DIR}/externalSacks/COMMON/Definitions
${DD_CREATOR_DIR}/externalSacks/COMMON/Messages
${DD_CREATOR_DIR}/externalSacks/COMMON/ServiceInterface)

PRINT_STATUS("Looking for EXTERNAL_SACK_DIRECTORY C/C++ files in: [${EXTERNAL_SACK_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(EXTERNAL_SACKS ${EXTERNAL_SACK_DIRECTORY})
