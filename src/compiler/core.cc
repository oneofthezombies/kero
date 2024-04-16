#include "core.h"

#include "cpp_tree_sitter/api.h"
#include "tree-sitter-kero.h"

using namespace kero::compiler;

kero::compiler::Error::Error(const ErrorCode code) noexcept : code{code} {}

kero::compiler::Error::Error(const ErrorCode code,
                             std::string &&message) noexcept
    : code{code}, message{std::move(message)} {}

auto kero::compiler::operator<<(std::ostream &os, const Error &error)
    -> std::ostream & {
  os << "Error{";
  os << "code: ";
  os << static_cast<int32_t>(error.code);
  os << ", ";
  os << "message: ";
  os << error.message;
  os << "}";
  return os;
}

auto kero::compiler::Language() -> ts::Language {
  return ts::Language::FromRaw(tree_sitter_kero());
}
