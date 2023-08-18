include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

PRINT_VARIABLE(BOOST_DIR)
#set boost flags
if(WIN32)
    #set directories for boost in APRG
    set(Boost_DEBUG                  ON)
    set(Boost_USE_STATIC_LIBS        ON)
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME     OFF)
    set(BOOST_ROOT                   ${BOOST_DIR}/boost)
    set(BOOST_INCLUDEDIR             ${BOOST_DIR}/)
    set(BOOST_LIBRARYDIR             ${BOOST_DIR}/boost/lib)
elseif(UNIX)
    #set directories for boost in linux
    set(Boost_DEBUG                  ON)
    set(BOOST_ROOT                   /usr/include/boost)
    set(BOOST_INCLUDEDIR             ${BOOST_ROOT})
    set(BOOST_LIBRARYDIR             ${BOOST_ROOT})
endif()

PRINT_VARIABLE(BOOST_ROOT)
PRINT_VARIABLE(BOOST_INCLUDEDIR)
PRINT_VARIABLE(BOOST_LIBRARYDIR)
find_package(Boost COMPONENTS system locale filesystem iostreams REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(WARNING "The cmake cannot find boost. Please set Boost_DEBUG to ON for more info. Try checking: FindBoost.cmake to investigate further.")
endif()

