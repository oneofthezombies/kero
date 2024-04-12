#include "compiler/parser.h"

#include "tree-sitter-kero.h"

using namespace kero::compiler;

void kero::compiler::TSParserDeleter::operator()(
    TSParser *parser) const noexcept {
  ts_parser_delete(parser);
}

void kero::compiler::TSTreeDeleter::operator()(TSTree *tree) const noexcept {
  ts_tree_delete(tree);
}

auto kero::compiler::Parser::Builder::set_timeout_micros(
    const size_t timeout_micros) noexcept -> Builder & {
  timeout_micros_ = timeout_micros;
  return *this;
}

std::optional<Parser> kero::compiler::Parser::Builder::build() const noexcept {
  auto parser = TSParserPtr{ts_parser_new()};
  if (!ts_parser_set_language(parser.get(), tree_sitter_kero())) {
    return std::nullopt;
  }

  ts_parser_set_timeout_micros(parser.get(), timeout_micros_);
  auto cancellation_flag = std::make_unique<size_t>(0);
  ts_parser_set_cancellation_flag(parser.get(), cancellation_flag.get());
  return Parser{std::move(parser), std::move(cancellation_flag)};
}

kero::compiler::Parser::Parser(
    TSParserPtr &&parser, std::unique_ptr<size_t> &&cancellation_flag) noexcept
    : parser_{std::move(parser)},
      cancellation_flag_{std::move(cancellation_flag)} {}

kero::compiler::Parser::~Parser() noexcept {}

auto kero::compiler::Parser::parse(const std::string_view source,
                                   TSTreePtr &&old_tree) const noexcept
    -> TSTreePtr {
  auto tree = ts_parser_parse_string(parser_.get(), old_tree.get(),
                                     source.data(), source.size());
  return TSTreePtr{tree};
}
