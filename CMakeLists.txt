# General
cmake_minimum_required(VERSION 3.14)
project(snek VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(libs/cvec)

# Library
add_library(snekLib 
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

target_include_directories(snekLib PUBLIC include/ src/ )
target_link_libraries(snekLib PRIVATE cvec)

# target_include_directories(snekLib PUBLIC 
#   src/
# )

# Binary
add_executable(snek src/main.c)

target_link_libraries(snek PRIVATE snekLib cvec)

# Testing
enable_testing()
find_package(CMocka REQUIRED)

add_executable(snekTests 
  tests/test_main.c
  tests/test_memory.c
  tests/test_chunk.c
)
target_link_libraries(snekTests PRIVATE
                cmocka::cmocka
                snekLib
                cvec
            )
target_include_directories(snekTests PRIVATE 
                include/ 
                src/
            )
add_test(NAME snekTests COMMAND snekTests)

# Compiled output file
set_target_properties(snek PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
