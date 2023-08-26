# Assign project directory, this needs aprg directory
set(APRG_BOOST_DIR ${APRG_DIR}/boost/)
print_variable(APRG_BOOST_DIR)

# Include print macros
include(${APRG_DIR}/AllCommonCMakeFiles/PrintMacros.cmake)

# Set boost flags for find package
if(WIN32)
    set(Boost_DEBUG ON)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    set(BOOST_ROOT ${APRG_BOOST_DIR}/localBoost/boost)
    set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
    set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)
elseif(UNIX)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(Boost_DEBUG ON)
    set(BOOST_ROOT /usr/include/boost)
    set(BOOST_INCLUDEDIR ${BOOST_ROOT})
    set(BOOST_LIBRARYDIR ${BOOST_ROOT})
endif()

print_variable(BOOST_ROOT)
print_variable(BOOST_INCLUDEDIR)
print_variable(BOOST_LIBRARYDIR)
find_package(
    Boost
    COMPONENTS system locale filesystem iostreams
    REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(WARNING "The cmake cannot find boost. Try checking: FindBoost.cmake to investigate further.")
endif()
