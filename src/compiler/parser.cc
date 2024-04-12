#include "compiler/parser.h"

#include <string>

#include "tree-sitter-kero.h"

using namespace kero::compiler;

void kero::compiler::TSParserDeleter::operator()(
    TSParser *parser) const noexcept {
  ts_parser_delete(parser);
}

void kero::compiler::TSTreeDeleter::operator()(TSTree *tree) const noexcept {
  ts_tree_delete(tree);
}

kero::compiler::String::String(char *data) noexcept : data_{data} {}

kero::compiler::String::String(String &&other) noexcept
    : data_{std::exchange(other.data_, nullptr)} {}

kero::compiler::String::~String() noexcept {
  if (data_) {
    free(data_);
    data_ = nullptr;
  }
}

auto kero::compiler::String::operator=(String &&other) noexcept -> String & {
  if (this != &other) {
    data_ = std::exchange(other.data_, nullptr);
  }

  return *this;
}

auto kero::compiler::String::string_view() const noexcept -> std::string_view {
  return std::string_view{data_};
}

kero::compiler::Node::Node(TSNode &&node) noexcept : node_{std::move(node)} {}

auto kero::compiler::Node::string() const noexcept -> String {
  return String{ts_node_string(node_)};
}

kero::compiler::Tree::Tree(TSTreePtr &&tree) noexcept
    : tree_{std::move(tree)} {}

auto kero::compiler::Tree::empty() const noexcept -> bool { return !tree_; }

auto kero::compiler::Tree::take() noexcept -> TSTreePtr {
  return std::move(tree_);
}

auto kero::compiler::Tree::root_node() const noexcept -> std::optional<Node> {
  if (empty()) {
    return std::nullopt;
  }

  return Node{ts_tree_root_node(tree_.get())};
}

auto kero::compiler::Tree::null() noexcept -> Tree {
  return Tree{TSTreePtr{nullptr}};
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

auto kero::compiler::Parser::parse(const std::string_view source) const noexcept
    -> std::optional<Tree> {
  return parse_incremental(source, Tree::null());
}

auto kero::compiler::Parser::parse_incremental(const std::string_view source,
                                               Tree &&old_tree) const noexcept
    -> std::optional<Tree> {
  auto ts_old_tree = old_tree.take();
  auto tree = ts_parser_parse_string(parser_.get(), ts_old_tree.get(),
                                     source.data(), source.size());
  if (tree == nullptr) {
    return std::nullopt;
  }

  return Tree{TSTreePtr{tree}};
}
