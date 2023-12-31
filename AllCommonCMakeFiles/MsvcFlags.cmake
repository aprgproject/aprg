set(APRG_COMPILER_COMMON_FLAGS "/nologo /EHsc /W4")
set(APRG_COMPILER_COMMON_C_FLAGS "/std:c17") # no C20 flag according to microsoft official website
set(APRG_COMPILER_COMMON_CPP_FLAGS "/std:c++20")
set(APRG_COMPILER_FLAGS_FOR_DEBUG_NO_FLAGS "")
set(APRG_COMPILER_FLAGS_FOR_DEBUG_WITH_DEBUG_INFO "/Zi")
set(APRG_COMPILER_FLAGS_FOR_DEBUG_SHOW_PREPROCESSING_RESULT "/EP")
set(APRG_COMPILER_FLAGS_FOR_RELEASE_NO_FLAGS "")
set(APRG_COMPILER_FLAGS_FOR_RELEASE_REMOVE_DUPLICATE_STRINGS "/GF")

# Default debug and release flags
set(APRG_COMPILER_FLAGS_FOR_DEBUG "${APRG_COMPILER_FLAGS_FOR_DEBUG_NO_FLAGS}")
set(APRG_COMPILER_FLAGS_FOR_RELEASE "${APRG_COMPILER_FLAGS_FOR_RELEASE_REMOVE_DUPLICATE_STRINGS}")

# Some notes
#
# Sources:
# -> https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options?view=msvc-170
# -> https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html
#
# MSVC Native tools:
#   CC = cl.exe
#       C and C++ Compiler - Can compile both C and C++ code depending on the flag.
#       By default, it compiles C++ code.
#   rc.exe => Resource Compiler.
#   LD = link.exe
#       C++ Linker.
#   AS = ml
#       Assembler
#   AR = lib
#
# Compiler: cl.exe
#   /nologo - Suppress Microsoft's logo.
#   /out:<file.exe> - Set output file name.
#   /EHsc
#   /Zi - Add debugging symbols to the executable.
#   /c - Doesn't link, generating *.obj for C and *.obj, *.o for C++.
#        Useful for compiling large code bases where each compilation unit can be compiled separately.
#   /W4 - Set the warning level to the highest.
#   /entry:<entrypoint> - Set the C/C++ runtime:
#       mainCRTStartup => calls main(), the entry point for console mode apps.
#       wmainCRTStartup => calls wmain(), as above but the Unicode version.
#       WinMainCRTStartup => calls WinMain(), the entry point for native Windows apps.
#       wWinMainCRTStartup => calls wWinMain(), as above but the Unicode version.
#       _DllMainCRTStartup => Calls DLLMain().
#   /subsystem:<type> - Set the subsystem - default is Console, can be:
#       /subsystem:console - For applications that run in the console (terminal emulator).
#       /subsystem:windows - Doesn't display the cmd.exe terminal when clicking the executable.
#   /TC -> Specify that the file is C source code.
#   /TP -> Specify that the file is C++ source code (default).
#   /MD, /MT, /LD => Run-time library - Indicates that object-code is a DLL.
#   /GF -> (Eliminate Duplicate Strings)
#       Enables the compiler to create a single copy of identical strings in the program image and in memory.
#       This optimization called string pooling can create smaller programs.
#   /E  - Copies preprocessor output to standard output.
#   /EHa - Enable C++ exception handling (with SEH exceptions).
#   /EHc - extern "C" defaults to nothrow.
#   /EHr - Always generate noexcept runtime termination checks.
#   /EHs - Enable C++ exception handling (no SEH exceptions).
#   /EP - Copies preprocessor output to standard output.
