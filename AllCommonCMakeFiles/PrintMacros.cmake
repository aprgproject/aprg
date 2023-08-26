# Printing Macros

# Macro: print_variable
# -> Prints the contents of a given CMake variable.
# -> Usage: print_variable(variable_name)
macro(print_variable variable)
    message(STATUS "VARIABLE: [${variable}] contains: [${${variable}}]")
endmacro()

# Macro: print_status
# -> Prints a status message to the CMake output.
# -> Usage: print_status(status_message)
macro(print_status message)
    message(STATUS "STATUS: [${message}]")
endmacro()

# Macro: print_warning
# -> Prints a warning message to the CMake output.
# -> Usage: print_warning(warning_message)
macro(print_warning message)
    message(WARNING "WARNING: [${message}]")
endmacro()

# Macro: print_error
# -> Prints an error message and terminates CMake execution.
# -> Usage: print_error(error_message)
macro(print_error message)
    message(FATAL_ERROR "FATAL_ERROR: [${message}]")
endmacro()
