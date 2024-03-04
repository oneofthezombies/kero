cmake_minimum_required(VERSION 3.28)
project(kero)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

find_program(LLVM_CONFIG "llvm-config")
if(NOT LLVM_CONFIG)
  message(FATAL_ERROR "llvm-config not found")
endif()

execute_process(
  COMMAND ${LLVM_CONFIG} --cxxflags
  OUTPUT_VARIABLE LLVM_CXX_FLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
  COMMAND ${LLVM_CONFIG} --ldflags
  OUTPUT_VARIABLE LLVM_LD_FLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
  COMMAND ${LLVM_CONFIG} --system-libs
  OUTPUT_VARIABLE LLVM_SYSTEM_LIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
  COMMAND ${LLVM_CONFIG} --libs core orcjit native
  OUTPUT_VARIABLE LLVM_LIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
  COMMAND ${LLVM_CONFIG} --includedir
  OUTPUT_VARIABLE LLVM_INCLUDE_DIRS
  OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} ${LLVM_LD_FLAGS} ${LLVM_SYSTEM_LIBS} ${LLVM_LIBS}"
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/llvm-project/llvm/examples/Kaleidoscope/include
)
include_directories(${LLVM_INCLUDE_DIRS})
link_libraries(${LLVM_LIBS})
link_libraries(${LLVM_SYSTEM_LIBS})

find_package(PkgConfig)
pkg_check_modules(ZSTD REQUIRED libzstd)
include_directories(${ZSTD_INCLUDE_DIRS})
link_directories(${ZSTD_LIBRARY_DIRS})
add_definitions(${ZSTD_CFLAGS_OTHER})

add_subdirectory(kero-lib)
add_subdirectory(kero-exe)
