# Assign common cmake static analyzer variables

if(APRG_ENABLE_STATIC_ANALYZERS)

	get_filename_component(IMMEDIATE_DIRECTORY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	PRINT_VARIABLE(IMMEDIATE_DIRECTORY_NAME)
	
	find_program(CPPCHECK_PROGRAM "cppcheck")
	PRINT_VARIABLE(CPPCHECK_PROGRAM)
	if(CPPCHECK_PROGRAM)
		set(CMAKE_C_CPPCHECK ${CPPCHECK_PROGRAM} --enable=all --suppress=missingIncludeSystem)
		set(CMAKE_CXX_CPPCHECK ${CPPCHECK_PROGRAM} --enable=all --suppress=missingIncludeSystem)
		PRINT_VARIABLE(CMAKE_C_CPPCHECK)
		PRINT_VARIABLE(CMAKE_CXX_CPPCHECK)
	endif()
	
	find_program(CLANG_TIDY_PROGRAM "clang-tidy")
	PRINT_VARIABLE(CLANG_TIDY_PROGRAM)
	if(CLANG_TIDY_PROGRAM)
		set(CMAKE_C_CLANG_TIDY ${CLANG_TIDY_PROGRAM} -checks=*;-header-filter="^.*\/${IMMEDIATE_DIRECTORY_NAME}\/.*") # -warnings-as-errors=*;
		set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_PROGRAM} -checks=*;-header-filter="^.*\/${IMMEDIATE_DIRECTORY_NAME}\/.*") # -warnings-as-errors=*;
		PRINT_VARIABLE(CMAKE_C_CLANG_TIDY)
		PRINT_VARIABLE(CMAKE_CXX_CLANG_TIDY)
	endif()
	
	find_program(CLAZY_PROGRAM "clazy")
	PRINT_VARIABLE(CLAZY_PROGRAM)
	if(CLAZY_PROGRAM)
		#CMAKE_CXX_COMPILER=${CLAZY_PROGRAM} # Clazy needs to be set as a compiler when cmake is invoked.
		PRINT_VARIABLE(CMAKE_CXX_COMPILER)
	endif()
	
endif()
