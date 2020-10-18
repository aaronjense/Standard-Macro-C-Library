cmake_minimum_required (VERSION 3.10)

add_executable (squeue_tests squeue_tests.c)
target_sources (squeue_tests PRIVATE squeue_tests.c)

target_include_directories (
  squeue_tests PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                          $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

add_test(NAME squeue_tests COMMAND squeue_tests)
