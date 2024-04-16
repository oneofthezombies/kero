#ifndef KERO_COMPILER_UTILS_H
#define KERO_COMPILER_UTILS_H

#include <string>

#include "cpp_tree_sitter/api.h"

namespace kero::compiler {

[[nodiscard]] auto NodeToString(const ts::Node &node) noexcept -> std::string;

} // namespace kero::compiler

#endif // KERO_COMPILER_UTILS_H
