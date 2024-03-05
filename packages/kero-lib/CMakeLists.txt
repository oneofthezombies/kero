set(SOURCES lib.cpp)
add_library(kero STATIC ${SOURCES})
target_include_directories(kero PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
