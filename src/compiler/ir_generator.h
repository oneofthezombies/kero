#ifndef KERO_COMPILER_IR_GENERATOR_H
#define KERO_COMPILER_IR_GENERATOR_H

#include "compiler/ir_visitor.h"

namespace kero::compiler {

class IrGenerator : public NonCopyAndMovable {
public:
  explicit IrGenerator(const IrVisitor &ir_visitor) noexcept;

  auto Generate(const std::string_view source, ts::Tree &&tree) noexcept
      -> IrVisitResult;

private:
  const IrVisitor &ir_visitor_;
  const LlvmContext llvm_context_;
  const LlvmModule module_;
  const LlvmIrBuilder builder_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_IR_GENERATOR_H
