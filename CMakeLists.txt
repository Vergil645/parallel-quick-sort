cmake_minimum_required(VERSION 3.25)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

project(parallel-quick-sort LANGUAGES C)

add_library(sort STATIC src/seq.c src/par.c)

add_executable(compare src/compare.c)
target_link_libraries(compare PRIVATE sort)

# ===== TESTING =====

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()