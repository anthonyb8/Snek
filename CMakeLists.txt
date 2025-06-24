# General
cmake_minimum_required(VERSION 3.14)
project(clox VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(libs/cvec)

# Library
add_library(cloxLib 
    # Bytes 
    src/bytecode/chunk.c 
    src/bytecode/memory.c     
    src/bytecode/debug.c     
    src/bytecode/value.c     
    
    # Scanner
    src/scanner/scanner.c

    # Compiler 
    src/compiler/compiler.c     

    # VM 
    src/vm/vm.c
    
)

target_include_directories(cloxLib PUBLIC include/ src/ )
target_link_libraries(cloxLib PRIVATE cvec)

# target_include_directories(cloxLib PUBLIC 
#   src/
# )

# Binary
add_executable(clox src/main.c)

target_link_libraries(clox PRIVATE cloxLib cvec)

# Testing
enable_testing()
find_package(CMocka REQUIRED)

add_executable(cloxTests 
  tests/test_main.c
  tests/test_memory.c
  tests/test_chunk.c
)
target_link_libraries(cloxTests PRIVATE
                cmocka::cmocka
                cloxLib
                cvec
            )
target_include_directories(cloxTests PRIVATE 
                include/ 
                src/
            )
add_test(NAME cloxTests COMMAND cloxTests)

# Compiled output file
set_target_properties(clox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
