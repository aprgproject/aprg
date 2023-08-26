# Assign project directory
set(GTEST_DIR ${APRG_DIR}/gtest/gtest/)

find_package(Threads)
if (CMAKE_USE_PTHREADS_INIT)
    # The pthreads library is available and allowed.
    set(gtest_disable_pthread OFF)
else()
    set(gtest_disable_pthread ON)
endif()

