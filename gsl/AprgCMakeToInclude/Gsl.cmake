# Assign project directory, this needs aprg directory
set(GSL_DIR ${APRG_DIR}/gsl/gsl/)

if(WIN32)
    # Use CMakeLists.txt of GSL
    add_subdirectory(${GSL_DIR} ${CMAKE_BINARY_DIR}/gsl)
    set(GSL_LIBRARIES_TO_LINK gsl gslcblas)
elseif(UNIX)
    find_package(GSL REQUIRED)
    set(GSL_LIBRARIES_TO_LINK GSL::gsl GSL::gslcblas)
endif()
