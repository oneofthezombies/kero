#include "code_generator.h"

using namespace kero::compiler;

kero::compiler::CodeGenerator::CodeGenerator() noexcept
    : context_(std::make_unique<llvm::LLVMContext>()),
      module_(std::make_unique<llvm::Module>("kero", *context_)),
      builder_(std::make_unique<llvm::IRBuilder<>>(*context_)) {}
