include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

print_variable(BOOST_DIR)
# set boost flags
if(WIN32)
    # set directories for boost in APRG
    set(Boost_DEBUG ON)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    set(BOOST_ROOT ${BOOST_DIR}/../boostLibrary/boost)
    set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
    set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)
elseif(UNIX)
    # set directories for boost in linux
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
    message(
        WARNING
            "The cmake cannot find boost. Please set Boost_DEBUG to ON for more info. Try checking: FindBoost.cmake to investigate further."
    )
endif()
