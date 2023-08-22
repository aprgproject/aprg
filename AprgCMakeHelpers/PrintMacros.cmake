# Printing Macros

macro(print_variable variable)
    message(STATUS "VARIABLE: [${variable}] contains: [${${variable}}]")
endmacro()

macro(print_status message)
    message(STATUS "STATUS: [${message}]")
endmacro()

macro(print_warning message)
    message(WARNING "WARNING: [${message}]")
endmacro()

macro(print_error message)
    message(FATAL_ERROR "FATAL_ERROR: [${message}]")
endmacro()
