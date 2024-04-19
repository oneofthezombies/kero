find_path(TREE_SITTER_INCLUDE_DIR tree_sitter)
find_library(TREE_SITTER_LIBRARY NAMES tree_sitter)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  TreeSitter REQUIRED_VARS TREE_SITTER_INCLUDE_DIR TREE_SITTER_LIBRARY)

if(TreeSitter_FOUND)
  set(TREE_SITTER_INCLUDE_DIRS ${TREE_SITTER_INCLUDE_DIR})
  set(TREE_SITTER_LIBRARIES ${TREE_SITTER_LIBRARY})
endif()

mark_as_advanced(TREE_SITTER_INCLUDE_DIR TREE_SITTER_LIBRARY)
