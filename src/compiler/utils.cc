#include "utils.h"

#include <sstream>

using namespace kero::compiler;

auto kero::compiler::NodeToString(const ts::Node &node) noexcept
    -> std::string {
  std::stringstream ss;
  ss << node;
  return ss.str();
}
