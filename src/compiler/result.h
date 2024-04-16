#ifndef KERO_COMPILER_RESULT_H
#define KERO_COMPILER_RESULT_H

#include <cstdint>

namespace kero::compiler {

enum class Result : int32_t {
  kSuccess = 0,

  // CodeGenerator
  // --------
  kSymbolNotFound = 100,
  kVisitorAlreadyRegistered,
};

} // namespace kero::compiler

#endif // KERO_COMPILER_RESULT_H
