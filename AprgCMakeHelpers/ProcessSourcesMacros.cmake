# Printing Macros

macro(APRG_PROCESS_SOURCES APRG_SOURCES_TO_PROCESS APRG_INCLUDES_DIRECTORIES_TO_PROCESS)

    PRINT_VARIABLE(APRG_ENABLE_STATIC_ANALYZERS)
	if (APRG_ENABLE_STATIC_ANALYZERS)
	
	    PRINT_STATUS("Static analyzer flag is on, checking available sanitizers...")
		
		foreach(INCLUDES_DIRECTORY ${APRG_INCLUDES_DIRECTORIES_TO_PROCESS})
		    list(APPEND INCLUDES_DIRECTORIES_WITH_I "-I${INCLUDES_DIRECTORY}")
        endforeach()
		PRINT_VARIABLE(INCLUDES_DIRECTORIES_WITH_I)
		
		get_filename_component(IMMEDIATE_DIRECTORY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
		PRINT_VARIABLE(IMMEDIATE_DIRECTORY_NAME)
		
		find_program(CPPCHECK cppcheck)
		PRINT_VARIABLE(CPPCHECK)
		if(CPPCHECK)
		    PRINT_STATUS("Adding cppcheck_analysis as custom target")
		    add_custom_target(
			    cppcheck_analysis
		        COMMAND ${CPPCHECK} --enable=all ${APRG_SOURCES_TO_PROCESS}
		        COMMENT "Running cppcheck..."
		    )
		endif()
		
		find_program(CLANG_TIDY "clang-tidy")
		PRINT_VARIABLE(CLANG_TIDY)
		if(CLANG_TIDY)
		    PRINT_STATUS("Adding clang_tidy_analysis as custom target")
		    add_custom_target(
		        clang_tidy_analysis
		        COMMAND ${CLANG_TIDY} -checks=* -p ${CMAKE_BINARY_DIR} -header-filter="^.*\/${IMMEDIATE_DIRECTORY_NAME}\/.*" ${APRG_SOURCES_TO_PROCESS} -extra-arg=-std=c++17 -- ${INCLUDES_DIRECTORIES_WITH_I} ${COMMON_DEFINITIONS}
		        COMMENT "Running clang-tidy..."
		    )
		endif()
				
		find_program(CLAZY "clazy")
		PRINT_VARIABLE(CLAZY)
		if(CLAZY)
		    PRINT_STATUS("Adding clazy_analysis as custom target")
			add_custom_target(
		        clazy_analysis
		        COMMAND ${CLAZY} -std=c++17 ${APRG_SOURCES_TO_PROCESS} ${INCLUDES_DIRECTORIES_WITH_I} ${COMMON_DEFINITIONS}
		        COMMENT "Running clazy..."
		    )
		else()
		    message(STATUS "clazy not found, skipping static analysis")
		endif()
		
    endif()
	
	
	
    PRINT_VARIABLE(APRG_ENABLE_BEAUTIFIER)
	if (APRG_ENABLE_BEAUTIFIER)
	
		find_program(CLANG_FORMAT "clang-format")
		PRINT_VARIABLE(CLANG_FORMAT)
		if(CLANG_FORMAT)
		    PRINT_STATUS("Adding clang_format as custom target")
		    add_custom_target(
		        clang_format
		        COMMAND ${CLANG_FORMAT} -i -style=file ${APRG_SOURCES_TO_PROCESS}
		        COMMENT "Running Clang Format..."
		    )
		endif()
		
    endif()
	
	
endmacro()

