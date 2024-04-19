cmake_minimum_required(VERSION 3.29)
project(kero VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(tree_sitter_kero_path ${CMAKE_CURRENT_SOURCE_DIR}/src/tree-sitter-kero)

add_library(tree_sitter_kero STATIC ${tree_sitter_kero_path}/src/parser.c)
target_compile_options(tree_sitter_kero PRIVATE -std=c17)
target_include_directories(
  tree_sitter_kero PUBLIC $<BUILD_INTERFACE:${tree_sitter_kero_path}/bindings/c>
                          $<INSTALL_INTERFACE:include>)
target_include_directories(tree_sitter_kero PRIVATE ${tree_sitter_path}/src)

install(
  TARGETS tree_sitter_kero
  EXPORT kero-targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)

install(FILES ${tree_sitter_kero_path}/bindings/c/tree-sitter-kero.h
        DESTINATION include)

install(
  EXPORT kero-targets
  FILE kero-config.cmake
  NAMESPACE kero::
  DESTINATION lib/cmake/kero)
