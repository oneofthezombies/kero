cmake_minimum_required(VERSION 3.28)
project(kero VERSION 0.1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/.local)
set(TREE_SITTER_KERO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/tree-sitter-kero)

# dependencies
# ------------

find_package(cpp_tree_sitter REQUIRED)
find_package(LLVM REQUIRED CONFIG)
find_package(GTest REQUIRED)

execute_process(
  COMMAND llvm-config --cxxflags
  OUTPUT_VARIABLE LLVM_CXXFLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(
  COMMAND llvm-config --ldflags
  OUTPUT_VARIABLE LLVM_LDFLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(
  COMMAND llvm-config --system-libs
  OUTPUT_VARIABLE LLVM_SYSTEM_LIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(
  COMMAND llvm-config --libs core
  OUTPUT_VARIABLE LLVM_LIBS_CORE
  OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 ${LLVM_CXXFLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LLVM_LDFLAGS}")

# tree_sitter_kero
# ----------------

add_library(tree_sitter_kero STATIC ${TREE_SITTER_KERO_PATH}/src/parser.c)
target_compile_options(tree_sitter_kero PRIVATE -std=c17)
target_include_directories(
  tree_sitter_kero PUBLIC $<BUILD_INTERFACE:${TREE_SITTER_KERO_PATH}/bindings/c>
                          $<INSTALL_INTERFACE:include>)
target_include_directories(tree_sitter_kero
                           PRIVATE ${TREE_SITTER_KERO_PATH}/src)

# kero_compiler
# -------------

file(GLOB_RECURSE KERO_COMPILER_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/compiler/*.cc)
list(FILTER KERO_COMPILER_SOURCES EXCLUDE REGEX ".*_test\\.cc$")

add_library(kero_compiler STATIC ${KERO_COMPILER_SOURCES})
target_include_directories(kero_compiler PUBLIC src)
target_include_directories(kero_compiler PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(
  kero_compiler tree_sitter_kero cpp_tree_sitter::cpp_tree_sitter
  ${LLVM_LIBS_CORE} ${LLVM_SYSTEM_LIBS})

# kero_compiler_test
# ------------------

file(GLOB_RECURSE KERO_COMPILER_TEST_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/compiler/*_test.cc)

add_executable(kero_compiler_test ${KERO_COMPILER_TEST_SOURCES})
target_include_directories(kero_compiler_test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(kero_compiler_test PRIVATE GTest::GTest GTest::Main
                                                 kero_compiler)

# # install # -------

# install( TARGETS tree_sitter_kero EXPORT kero-targets LIBRARY DESTINATION lib
# ARCHIVE DESTINATION lib RUNTIME DESTINATION bin INCLUDES DESTINATION include)

# install(FILES ${TREE_SITTER_KERO_PATH}/bindings/c/tree-sitter-kero.h
# DESTINATION include)

# install( EXPORT kero-targets FILE kero-config.cmake NAMESPACE kero::
# DESTINATION lib/cmake/kero)
