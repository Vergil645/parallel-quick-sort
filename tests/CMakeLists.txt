set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

project(parallel-quick-sort_tests LANGUAGES C)

add_executable(test_seq src/test_seq.c)
target_link_libraries(test_seq PRIVATE sort)

add_executable(test_par src/test_par.c)
target_link_libraries(test_par PRIVATE sort)

# ===== UNIT TESTS =====

add_test(NAME test_seq COMMAND test_seq)
add_test(NAME test_par COMMAND test_par)
