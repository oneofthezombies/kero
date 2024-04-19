find_path(CPP_TREE_SITTER_INCLUDE_DIR cpp_tree_sitter/api.h)
find_library(CPP_TREE_SITTER_LIBRARY NAMES cpp_tree_sitter)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  CppTreeSitter REQUIRED_VARS CPP_TREE_SITTER_INCLUDE_DIR
                              CPP_TREE_SITTER_LIBRARY)

if(CppTreeSitter_FOUND)
  set(CPP_TREE_SITTER_INCLUDE_DIRS ${CPP_TREE_SITTER_INCLUDE_DIR})
  set(CPP_TREE_SITTER_LIBRARIES ${CPP_TREE_SITTER_LIBRARY})
endif()

mark_as_advanced(CPP_TREE_SITTER_INCLUDE_DIR CPP_TREE_SITTER_LIBRARY)
