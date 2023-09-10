# Assign common cmake static analyzer variables

if(APRG_ENABLE_STATIC_ANALYZERS)
    if(NOT APRG_STATIC_ANALYZERS_TYPE)
        set(APRG_STATIC_ANALYZERS_TYPE "ReportWithoutClazy")
    endif()
	
    find_program(CPPCHECK_PROGRAM "cppcheck")
    print_variable(CPPCHECK_PROGRAM)
    if(CPPCHECK_PROGRAM)
        set(CMAKE_C_CPPCHECK ${CPPCHECK_PROGRAM} --enable=all --inline-suppr
                             --suppressions-list=${APRG_DIR}/cppcheck-suppressions.txt)
        set(CMAKE_CXX_CPPCHECK ${CPPCHECK_PROGRAM} --enable=all --inline-suppr
                               --suppressions-list=${APRG_DIR}/cppcheck-suppressions.txt)
        print_variable(CMAKE_C_CPPCHECK)
        print_variable(CMAKE_CXX_CPPCHECK)
    endif()

    find_program(CLANG_TIDY_PROGRAM "clang-tidy")
    print_variable(CLANG_TIDY_PROGRAM)
    if(CLANG_TIDY_PROGRAM)
        string(REPLACE "/" "\\/" CLANG_TIDY_HEADER_REGEX ${CMAKE_CURRENT_SOURCE_DIR})
        set(CLANG_TIDY_HEADER_REGEX "${CLANG_TIDY_HEADER_REGEX}.*")

        print_variable(CLANG_TIDY_HEADER_REGEX)

        # additional flags: --fix --warnings-as-errors=*;
        if(APRG_STATIC_ANALYZERS_TYPE STREQUAL "AutoFix")
            # auto fix
            set(CMAKE_C_CLANG_TIDY ${CLANG_TIDY_PROGRAM} --fix "--header-filter=${CLANG_TIDY_HEADER_REGEX}"
                                   "--config-file=${APRG_DIR}/Clang/ClangTidyFiles/autofix.clang-tidy")
            set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_PROGRAM} --fix "--header-filter=${CLANG_TIDY_HEADER_REGEX}"
                                     "--config-file=${APRG_DIR}/Clang/ClangTidyFiles/autofix.clang-tidy")
        else()
            # check only
            set(CMAKE_C_CLANG_TIDY ${CLANG_TIDY_PROGRAM} "--header-filter=${CLANG_TIDY_HEADER_REGEX}"
                                   "--config-file=${APRG_DIR}/Clang/ClangTidyFiles/report.clang-tidy")
            set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_PROGRAM} "--header-filter=${CLANG_TIDY_HEADER_REGEX}"
                                     "--config-file=${APRG_DIR}/Clang/ClangTidyFiles/report.clang-tidy")
        endif()

        print_variable(CMAKE_C_CLANG_TIDY)
        print_variable(CMAKE_CXX_CLANG_TIDY)
    endif()

    if(APRG_STATIC_ANALYZERS_TYPE STREQUAL "ReportWithClazy")
        find_program(CLAZY_PROGRAM "clazy")
        print_variable(CLAZY_PROGRAM)
        if(CLAZY_PROGRAM)
            print_variable(CMAKE_CXX_COMPILER)
            if(NOT CMAKE_CXX_COMPILER MATCHES ".*clazy.*")
                print_error("Clazy needs to be set as a compiler when cmake is invoked.")
            endif()
            # Based from: https://github.com/KDE/clazy#list-of-checks
            # There are many checks and they are divided in levels:
            # level0: Very stable checks, 99.99% safe, mostly no false-positives, very desirable
            # level1: The default level. Very similar to level 0, slightly more false-positives but very few.
            # level2: Also very few false-positives, but contains noisy checks which not everyone agree should be default.
            # manual: Checks here need to be enabled explicitly, as they can be very stable or very unstable
            # ME: Just stick to default
            # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Xclang -plugin-arg-clazy -Xclang level2")
            # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -plugin-arg-clazy -Xclang level2")
            # PRINT_VARIABLE(CMAKE_C_FLAGS)
            # PRINT_VARIABLE(CMAKE_CXX_FLAGS)
        endif()
    endif()

endif()
