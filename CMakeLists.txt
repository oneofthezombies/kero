cmake_minimum_required(VERSION 3.29)
project(kero VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(tree_sitter_kero STATIC
  src/tree-sitter-kero/src/parser.c
  src/tree-sitter-kero/bindings/c/tree-sitter-kero.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree-sitter-kero/src/tree_sitter/*.h
)
target_include_directories(tree_sitter_kero PUBLIC
  src/tree-sitter-kero/bindings/c
  src/tree-sitter-kero/src
)
target_compile_options(tree_sitter_kero PRIVATE -std=c17)
